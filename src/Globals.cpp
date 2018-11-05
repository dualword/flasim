#include "Globals.hpp"

#include <irrlicht.h>

using namespace irr;

Globals* Globals::instance = nullptr;

Globals::Globals()
{
    dev = createDevice(video::EDT_OPENGL, core::dimension2du(1280, 800), 32, false, false, true);
    drv = dev->getVideoDriver();
    sman = dev->getSceneManager();
}

Globals::~Globals()
{
    dev->drop();
    instance = nullptr;
}

void Globals::shutdown()
{
    if (instance)
        delete instance;
}

IrrlichtDevice* Globals::getDevice()
{
    if (!instance)
        instance = new Globals();

    return instance->dev;
}

video::IVideoDriver* Globals::getVideoDriver()
{
    if (!instance)
        instance = new Globals();

    return instance->drv;
}

scene::ISceneManager* Globals::getSceneManager()
{
    if (!instance)
        instance = new Globals();

    return instance->sman;
}
