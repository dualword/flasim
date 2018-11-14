#include <irrlicht.h>

class Aircraft
{
public:
    Aircraft();
    ~Aircraft();

    bool evalShot(const irr::core::line3df&);
    bool isGood() const;
    bool isTerminated() const;

private:
    irr::scene::IMeshSceneNode *model;
    irr::scene::ISceneNodeAnimator *a;
    bool healthy;

};
