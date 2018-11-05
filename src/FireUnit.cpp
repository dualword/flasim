#include "FireUnit.hpp"

#include "Globals.hpp"
#include "TurretCamAnimator.hpp"

using namespace irr;
using namespace irr::core;

FireUnit::FireUnit()
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

        vector3df rot = turretAzimuth->getRotation();
        rot.Y -= 1.f * aziTurnCoeff;
        if (rot.Y > 360.f)
            rot.Y -= 360.f;

        if (rot.Y < 0.f)
            rot.Y += 360.f;

        turretAzimuth->setRotation(rot);

        rot = turretElevation->getRotation();
        rot.X += 1.f * elevTurnCoeff;
        if (rot.X > 5.f)
            rot.X = 5.f;

        if (rot.X < -85.f)
            rot.X = -85.f;
        turretElevation->setRotation(rot);

        return true;
    }

    return false;
}
