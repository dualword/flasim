#ifndef GLOBALS_HPP
#define GLOBALS_HPP

namespace irr
{
    class IrrlichtDevice;

    namespace scene
    {
        class ISceneManager;
    }
    namespace video
    {
        class IVideoDriver;
    }
}


class Globals
{
public:
    static class irr::IrrlichtDevice* getDevice();
    static class irr::scene::ISceneManager* getSceneManager();
    static class irr::video::IVideoDriver* getVideoDriver();

    static void shutdown();

private:
    Globals();
    ~Globals();
    static Globals* instance;

    class irr::IrrlichtDevice* dev;
    class irr::scene::ISceneManager* sman;
    class irr::video::IVideoDriver* drv;
};
#endif // GLOBALS_HPP
