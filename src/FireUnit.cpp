#include "FireUnit.hpp"

#include <iostream>
#include <cAudio.h>

#include "Globals.hpp"
#include "Dispatcher.hpp"
#include "TurretCamAnimator.hpp"

using namespace std;
using namespace irr;
using namespace irr::core;

FireUnit::FireUnit()
    : aziTurnCoeffSmooth(0.f)
    , elevTurnCoeffSmooth(0.f)
    , fireCount(0)
    , fireBtnPressed(false)
    , stripsRemaining(5)
    , reloading(false)
{
    turretAzimuth = Globals::getSceneManager()->addEmptySceneNode();
    turretElevation = Globals::getSceneManager()->addMeshSceneNode(Globals::getSceneManager()->getMesh("../res/guns.obj"), turretAzimuth);
    cam = Globals::getSceneManager()->addCameraSceneNode(turretElevation);

    turretCamAnimator = new TurretCamAnimator(turretElevation);
    cam->setNearValue(0.01f);
    cam->setFarValue(4000.f);
    cam->addAnimator(turretCamAnimator);

    crosshair = Globals::getVideoDriver()->getTexture("../res/crosshair.png");

    mflashR = Globals::getSceneManager()->addBillboardSceneNode(turretElevation, dimension2df(1.f, 1.f), vector3df(.14f, 1.5f, 1.89f));
    mflashL = Globals::getSceneManager()->addBillboardSceneNode(turretElevation, dimension2df(1.f, 1.f), vector3df(-.14f, 1.5f, 1.89f));
    mflashR->setMaterialTexture(0, Globals::getVideoDriver()->getTexture("../res/mflash.png"));
    mflashR->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    mflashR->setMaterialFlag(video::EMF_LIGHTING, false);
    mflashL->setMaterialTexture(0, Globals::getVideoDriver()->getTexture("../res/mflash.png"));
    mflashL->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    mflashL->setMaterialFlag(video::EMF_LIGHTING, false);
    mflashL->setVisible(false);
    mflashR->setVisible(false);

    fireSound = Globals::getAudioManager()->create("fireSound", "../res/gunburst.wav", false);
    screenSize = Globals::getVideoDriver()->getScreenSize();
}

FireUnit::~FireUnit()
{
    cam->removeAnimator(turretCamAnimator);
    delete turretCamAnimator;
}

bool FireUnit::OnEvent(const SEvent& e)
{
    if (e.EventType == irr::EET_JOYSTICK_INPUT_EVENT)
    {
        f32 aziTurnCoeff = 0.f, elevTurnCoeff = 0.f;
        const f32 DEAD_ZONE = 0.0100000f;

        elevTurnCoeff =
            (f32)e.JoystickEvent.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
        if (fabs(elevTurnCoeff) < DEAD_ZONE)
            elevTurnCoeff = 0.f;


        aziTurnCoeff =
            (f32)e.JoystickEvent.Axis[SEvent::SJoystickEvent::AXIS_X] / -32767.f;
        if (fabs(aziTurnCoeff) < DEAD_ZONE)
            aziTurnCoeff = 0.f;

        if (e.JoystickEvent.IsButtonPressed(0))
        {
            if (!fireBtnPressed)
            {
                if (!reloading && stripsRemaining > 0 && fireCount == 0)
                {
                    fireSound->play2d();
                    fireCount = 16;
                    stripsRemaining--;
                }
                fireBtnPressed = true;
            }
        }
        else
        {
            fireBtnPressed = false;
        }

        if (e.JoystickEvent.IsButtonPressed(2))
        {
            if (!reloading)
            {
                reloadUntil = Globals::getDevice()->getTimer()->getRealTime() + 15000;
                reloading = true;
            }
        }
        else
        {
            // sec trigger released
        }

        aziTurnCoeffSmooth = aziTurnCoeffSmooth * .95f + aziTurnCoeff * .05f;
        elevTurnCoeffSmooth = elevTurnCoeffSmooth * .95f + elevTurnCoeff * .05f;

        vector3df rot = turretAzimuth->getRotation();
        rot.Y -= 1.f * aziTurnCoeffSmooth;
        if (rot.Y > 360.f)
            rot.Y -= 360.f;

        if (rot.Y < 0.f)
            rot.Y += 360.f;

        turretAzimuth->setRotation(rot);

        rot = turretElevation->getRotation();
        rot.X += 1.f * elevTurnCoeffSmooth;
        if (rot.X > 5.f)
            rot.X = 5.f;

        if (rot.X < -85.f)
            rot.X = -85.f;
        turretElevation->setRotation(rot);

        return true;
    }

    return false;
}

u32 FireUnit::getRoundsRemaining() const
{
    return stripsRemaining * 16 + fireCount;
}

bool FireUnit::isReloading() const
{
    return reloading;
}


void FireUnit::draw()
{
    auto drv = Globals::getVideoDriver();
    auto& res = drv->getScreenSize();
    if (screenSize != res)
    {
        screenSize = res;
        cam->setAspectRatio(static_cast<f32>(res.Width) / static_cast<f32>(res.Height));
    }

    drv->draw2DImage(crosshair, position2di(res.Width / 2 - 128, res.Height / 2 - 128), recti(0, 0, 256, 256), nullptr, video::SColor(255,255,255,255), true );

    video::SMaterial matA;
    matA.AmbientColor = video::SColor(255, 255, 0, 0);
    matA.DiffuseColor = video::SColor(255, 255, 0, 0);
    matA.ColorMaterial = video::ECM_NONE;
    matA.AntiAliasing = video::EAAM_FULL_BASIC;
    matA.Lighting = false;
    matA.Thickness = 1.5f;
    matA.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
    drv->setMaterial(matA);

    if (fireCount > 0)
    {
        shotline.start = cam->getAbsolutePosition();
        shotline.end = cam->getTarget() - shotline.start;
        shotline.end.normalize();
        shotline.end *= 4000.f;
        Globals::getDispatcher()->evalShot(shotline);

        mflashL->setVisible(fireCount % 4 == 2);
        mflashR->setVisible(fireCount % 4 == 0);
        fireCount--;
    }
    else
    {
        mflashL->setVisible(false);
        mflashR->setVisible(false);
    }

    if (reloading)
    {
        if (Globals::getDevice()->getTimer()->getRealTime() > reloadUntil)
        {
            reloading = false;
            stripsRemaining = 5;
        }
    }
}
