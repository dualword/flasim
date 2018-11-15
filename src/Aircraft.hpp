#include <irrlicht.h>

namespace cAudio
{
class IAudioSource;
}

class Aircraft
{
public:
    Aircraft(const irr::core::line3df &flightLine, irr::u32 flightTimeMillis);
    ~Aircraft();

    bool evalShot(const irr::core::line3df&);
    bool isGood() const;
    bool isTerminated() const;
    void update(irr::u32 curMS);
    irr::core::vector3df getPosition() const;

private:
    Aircraft();
    irr::scene::IMeshSceneNode *model;
    irr::scene::ISceneNodeAnimator *a;
    bool healthy;
    class cAudio::IAudioSource* flybySound;
    irr::u32 flightDuration, flightStarted;
};
