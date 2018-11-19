#include <irrlicht.h>

//! Super simple scene node animator that makes the camera look along the cannon
class TurretCamAnimator : public irr::scene::ISceneNodeAnimator
{
public:
    TurretCamAnimator(irr::scene::ISceneNode* _parent);
    ~TurretCamAnimator();

    void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
    irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* , irr::scene::ISceneManager* ){return nullptr;}

private:
    TurretCamAnimator();
    irr::scene::ISceneNode *parent;
};

