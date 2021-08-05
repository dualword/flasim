#include "Dispatcher.hpp"
#include "Globals.hpp"
#include "Aircraft.hpp"

using namespace irr;
using namespace irr::core;

Dispatcher::Dispatcher()
    : active(false)
    , aircraftsRemaining(0)
    , points(0)
{

}

Dispatcher::~Dispatcher()
{
    aircrafts.clear();
}

void Dispatcher::start()
{
    lastDispatchMS = Globals::getDevice()->getTimer()->getRealTime() - 40000;
    active = true;
    aircraftsRemaining = 5;
    points = 0;
}

void Dispatcher::execute()
{
    u32 curTime = Globals::getDevice()->getTimer()->getRealTime();

    if (active && (curTime - lastDispatchMS) > 45000)
    {
        if (aircraftsRemaining > 0)
        {
            dispatchAircraft();
            aircraftsRemaining--;
            lastDispatchMS = curTime;
        }
        else
        {
            stop();
        }
    }

    // loopdidoo & cleanup
    auto a = aircrafts.begin();
    while (a < aircrafts.end())
    {
        (*a)->update(curTime);
        if ((*a)->isTerminated())
        {
            a = aircrafts.erase(a);
        }
        else
            ++a;
    }
}

void Dispatcher::stop()
{
    aircrafts.clear();
    active = false;
}

const Dispatcher::Aircrafts &Dispatcher::getAircrafts() const
{
    return aircrafts;
}

bool Dispatcher::evalShot(const core::line3df& l)
{
    bool ret = false;
    for (auto& a : aircrafts)
    {
        if (a->isGood() && a->evalShot(l))
        {
            points += 1000 + a->getPosition().getDistanceFrom(vector3df(0.f, 0.f, 0.f));
            ret = true;
        }
    }

    return ret;
}

u32 Dispatcher::getAircraftsRemaining() const
{
    return aircraftsRemaining;
}

u32 Dispatcher::getPoints() const
{
    return points;
}

void Dispatcher::dispatchAircraft()
{
    IRandomizer *rand = Globals::getDevice()->getRandomizer();
    // rand dir vector around 0/0
    vector2df dVec(1.f, 0.f);
    dVec.rotateBy(rand->frand() * 360.f, vector2df(0.f, 0.f));
    dVec.normalize();
    vector2df nVec(dVec.Y, -dVec.X);
    f32 d = rand->frand() * 500.f;
    f32 alt = 50.f + rand->frand() * 500.f;

    // start/end 2km off our pos, displaced by d * nVec to the side
    vector2df start = dVec * -2000.f + nVec * d;
    vector2df end = dVec * 2000.f + nVec * d;

    line3df l;
    l.start = vector3df(start.X, alt, start.Y);
    l.end = vector3df(end.X, alt, end.Y);
    aircrafts.push_back(std::make_unique<Aircraft>(l, 30000 + static_cast<u32>(rand->frand() * 15000.f)));
}
