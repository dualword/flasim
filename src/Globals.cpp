#include "Globals.hpp"

#include "Dispatcher.hpp"
#include <irrlicht.h>
#include <cAudio/cAudio.h>

using namespace irr;

Globals* Globals::instance = nullptr;

Globals::Globals()
{
    dev = createDevice(video::EDT_OPENGL, core::dimension2du(1280, 800), 32, false, false, true);
    drv = dev->getVideoDriver();
    sman = dev->getSceneManager();
    dispatcher = new Dispatcher();
    audioManager = cAudio::createAudioManager(true);
}

Globals::~Globals()
{
    dev->drop();
    audioManager->shutDown();
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

cAudio::IAudioManager* Globals::getAudioManager()
{
    if (!instance)
        instance = new Globals();

    return instance->audioManager;
}

Dispatcher* Globals::getDispatcher()
{
    if (!instance)
        instance = new Globals();

    return instance->dispatcher;
}
