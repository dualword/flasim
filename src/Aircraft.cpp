#include "Aircraft.hpp"

#include <iostream>

#include "Globals.hpp"



using namespace irr;
using namespace irr::core;

Aircraft::Aircraft()
{
    model = Globals::getSceneManager()->addMeshSceneNode(Globals::getSceneManager()->getMesh("../res/SU35S.obj"));
    model->setPosition(vector3df(25.f, 0.f, 0.f));
    a = Globals::getSceneManager()->createFlyStraightAnimator(vector3df(100.f, 100.f, -1000.f),
                                                          vector3df(100.f, 100.f, 1000.f),
                                                          32000,
                                                          false,
                                                          false);

    model->addAnimator(a);
    std::cout << "Aircraft" << std::endl;
}

Aircraft::~Aircraft()
{
    Globals::getSceneManager()->addToDeletionQueue(model);
    std::cout << "~Aircraft" << std::endl;
}

bool Aircraft::isGood() const
{
    return healthy;
}

bool Aircraft::isTerminated() const
{
    return a->hasFinished();
}

bool Aircraft::evalShot(const irr::core::line3df &shotline)
{
    bool hit = model->getTransformedBoundingBox().intersectsWithLine(shotline);
    if (hit)
    {
        if (healthy)
        {
            // got hit for the first time: do smokey?
            auto pman = Globals::getSceneManager()->addParticleSystemSceneNode(true, model);
            pman->getEmitter()->setDirection(vector3df(0.f, 0.f, 0.f));
        }

        healthy = false;
    }
    return hit;
}
