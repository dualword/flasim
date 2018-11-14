#ifndef FIREUNIT_HPP
#define FIREUNIT_HPP

#include <irrlicht.h>

class FireUnit : public irr::IEventReceiver
{
public:
    FireUnit();
    ~FireUnit();

    bool OnEvent(const irr::SEvent&);
    void draw();

private:
    irr::scene::ICameraSceneNode *cam;
    irr::scene::ISceneNode *turretElevation, *turretAzimuth;
    irr::scene::ISceneNodeAnimator *turretCamAnimator;
    irr::f32 aziTurnCoeffSmooth, elevTurnCoeffSmooth;
    irr::video::ITexture *crosshair;
};

#endif // FIREUNIT_HPP
