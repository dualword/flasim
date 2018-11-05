#include <irrlicht.h>

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

