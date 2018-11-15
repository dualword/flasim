#include "Dispatcher.hpp"
#include "Globals.hpp"
#include "Aircraft.hpp"

using namespace irr;
using namespace irr::core;

Dispatcher::Dispatcher()
    : active(false)
{

}

Dispatcher::~Dispatcher()
{
    aircrafts.clear();
}

void Dispatcher::start()
{
    lastDispatchMS = Globals::getDevice()->getTimer()->getRealTime();
    active = true;
}

void Dispatcher::execute()
{
    u32 curTime = Globals::getDevice()->getTimer()->getRealTime();

    if (active && (curTime - lastDispatchMS) > 10000)
    {
        dispatchAircraft();
        lastDispatchMS = curTime;
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
    active = false;
}

const Dispatcher::Aircrafts &Dispatcher::getAircrafts() const
{
    return aircrafts;
}

bool Dispatcher::evalShot(const core::line3df& l)
{
    bool ret = false;
    for (auto a : aircrafts)
    {
        if (a->evalShot(l))
        {
            ret = true;
        }
    }

    return ret;
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
    aircrafts.push_back(std::make_shared<Aircraft>(l, 30000 + static_cast<u32>(rand->frand() * 30000.f)));
}
