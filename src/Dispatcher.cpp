#include "Dispatcher.hpp"
#include "Globals.hpp"
#include "Aircraft.hpp"

using namespace irr;

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
        auto a = std::make_shared<Aircraft>();
        aircrafts.push_back(a);
        lastDispatchMS = curTime;
    }

    //cleanup
    auto a = aircrafts.begin();
    while (a < aircrafts.end())
    {
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
