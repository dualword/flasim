//flasim-mod https://github.com/dualword/flasim
#include <irrlicht.h>
#include <SFML/Audio.hpp>

//! Sends an aircraft along a line in a given time. Handles hits and smoke - that all
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
    sf::SoundBuffer buf;
    sf::Sound flybySound;
    irr::u32 flightDuration, flightStarted;
};
