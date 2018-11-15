#ifndef FIREUNIT_HPP
#define FIREUNIT_HPP

#include <irrlicht.h>

namespace cAudio
{
class IAudioSource;
}

class FireUnit : public irr::IEventReceiver
{
public:
    FireUnit();
    ~FireUnit();

    bool OnEvent(const irr::SEvent&);
    irr::u32 getRoundsRemaining() const;
    bool isReloading() const;
    void draw();

private:
    irr::scene::ICameraSceneNode *cam;
    irr::scene::ISceneNode *turretElevation, *turretAzimuth;
    irr::scene::ISceneNodeAnimator *turretCamAnimator;
    irr::f32 aziTurnCoeffSmooth, elevTurnCoeffSmooth;
    irr::video::ITexture *crosshair;

    irr::core::line3df shotline;
    irr::scene::IBillboardSceneNode *mflashL, *mflashR;
    irr::u32 fireCount;
    bool fireBtnPressed;
    irr::u32 stripsRemaining;
    bool reloading;
    irr::u32 reloadUntil;

    class cAudio::IAudioSource* fireSound;
};

#endif // FIREUNIT_HPP
