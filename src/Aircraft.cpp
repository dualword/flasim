#include "Aircraft.hpp"

#include <iostream>
#include <cAudio.h>
#include "Globals.hpp"




using namespace irr;
using namespace irr::core;

Aircraft::Aircraft(const line3df &flightLine, u32 flightTimeMillis)
    : flightDuration(flightTimeMillis)
    , flightStarted(Globals::getDevice()->getTimer()->getRealTime())
{
    model = Globals::getSceneManager()->addMeshSceneNode(Globals::getSceneManager()->getMesh("../res/SU35S.obj"));
    model->setPosition(vector3df(25.f, 0.f, 0.f));
    a = Globals::getSceneManager()->createFlyStraightAnimator(flightLine.start,
                                                              flightLine.end,
                                                              flightTimeMillis,
                                                              false,
                                                              false);

    auto dvec = (flightLine.end - flightLine.start).normalize();
    f64 rotBy = vector2df(dvec.X, dvec.Z).getAngleTrig();
    model->setRotation(vector3df(0.f, -rotBy, 0.f));

    model->addAnimator(a);
    flybySound = Globals::getAudioManager()->create("flybySound", "../res/flyby.wav", false);
    //std::cout << "Aircraft from " << flightTimeMillis << ' ' << flightLine.start.Y << " to " << flightLine.end.X << ' ' << flightLine.end.Y << " at " << flightLine.start.Z << std::endl;
}

Aircraft::~Aircraft()
{
    a->drop();
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
            pman->getEmitter()->setMinStartSize(dimension2df(80.f, 80.f));
            pman->getEmitter()->setMaxStartSize(dimension2df(120.f, 120.f));
            pman->getEmitter()->setDirection(vector3df(0.f, 0.f, 0.f));
            pman->setMaterialTexture(0, Globals::getVideoDriver()->getTexture("../res/smoke.png"));
            pman->setMaterialTexture(1, Globals::getVideoDriver()->getTexture("../res/smoke1.png"));
            pman->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
            pman->setMaterialFlag(video::EMF_LIGHTING, false);
        }

        healthy = false;
    }
    return hit;
}

void Aircraft::update(u32 curMS)
{
    if (!flybySound->isPlaying())
    {

        u32 curTime = curMS;
        curTime -= flightStarted;
        if (curTime > flightDuration / 2 - 4000 && curTime < flightDuration / 2)
        {
            auto p = model->getAbsolutePosition();
            flybySound->play3d(cAudio::cVector3(p.X, p.Y, p.Z));
            //std::cout << "PLAY!" << std::endl;
           // flybySound->play2d();
        }
    }
    else
    {
        auto p = model->getAbsolutePosition();
        flybySound->move(cAudio::cVector3(p.X, p.Y, p.Z));
    }
}

vector3df Aircraft::getPosition() const
{
    return model->getAbsolutePosition();
}
