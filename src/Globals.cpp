//flasim-mod https://github.com/dualword/flasim
#include "Globals.hpp"

#include "Dispatcher.hpp"
#include <irrlicht.h>

using namespace irr;

Globals* Globals::instance = nullptr;

Globals::Globals()
{
    dev = createDevice(video::EDT_OPENGL, core::dimension2du(1366, 768), 32, false, false, true);
    dev->setResizable(true);
    drv = dev->getVideoDriver();
    sman = dev->getSceneManager();
    dispatcher = new Dispatcher();
    font = dev->getGUIEnvironment()->getFont("../res/fontlucida.png");
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

Dispatcher* Globals::getDispatcher()
{
    if (!instance)
        instance = new Globals();

    return instance->dispatcher;
}

gui::IGUIFont *Globals::getFont()
{
    if (!instance)
        instance = new Globals();

    return instance->font;
}
