#include "FireUnit.hpp"

#include "Globals.hpp"
#include "TurretCamAnimator.hpp"

using namespace irr;
using namespace irr::core;

FireUnit::FireUnit()
    : aziTurnCoeffSmooth(0.f)
    , elevTurnCoeffSmooth(0.f)
{
    turretAzimuth = Globals::getSceneManager()->addEmptySceneNode();
    turretElevation = Globals::getSceneManager()->addMeshSceneNode(Globals::getSceneManager()->getMesh("../res/guns.obj"), turretAzimuth);
    cam = Globals::getSceneManager()->addCameraSceneNode(turretElevation);

    turretCamAnimator = new TurretCamAnimator(turretElevation);
    cam->setNearValue(0.01f);
    cam->setFarValue(4000.f);
    cam->addAnimator(turretCamAnimator);

    auto jet = Globals::getSceneManager()->addMeshSceneNode(Globals::getSceneManager()->getMesh("../res/SU35S.obj"));
    jet->setPosition(vector3df(25.f, 0.f, 0.f));
    auto a = Globals::getSceneManager()->createFlyStraightAnimator(vector3df(100.f, 100.f, -1000.f),
                                                          vector3df(100.f, 100.f, 1000.f),
                                                          16000,
                                                          true,
                                                          false);
    jet->addAnimator(a);
    a->drop();

    crosshair = Globals::getVideoDriver()->getTexture("../res/crosshair.png");

    auto b = Globals::getSceneManager()->addBillboardSceneNode(turretElevation, dimension2df(1.f, 1.f), vector3df(.14f, 1.5f, 1.89f));
    b->setMaterialTexture(0, Globals::getVideoDriver()->getTexture("../res/mflash.png"));
    b->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
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

        if (e.JoystickEvent.IsButtonPressed(1))
        {
            // fire trigger pressed
        }
        else
        {
            // fire trigger released
        }

        if (e.JoystickEvent.IsButtonPressed(2))
        {
            // sec trigger pressed
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


void FireUnit::draw()
{
    auto& res = Globals::getVideoDriver()->getScreenSize();

    Globals::getVideoDriver()->draw2DImage(crosshair, position2di(res.Width / 2 - 128, res.Height / 2 - 128), recti(0, 0, 256, 256), nullptr, video::SColor(255,255,255,255), true );
}
