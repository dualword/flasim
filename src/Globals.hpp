#ifndef GLOBALS_HPP
#define GLOBALS_HPP

namespace cAudio
{
    class IAudioManager;
}

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
    namespace gui
    {
    class IGUIFont;
    }
}

//! Globally used stuff (mostly irrlicht-related) packed in a singleton
class Globals
{
public:
    static class irr::IrrlichtDevice* getDevice();
    static class irr::scene::ISceneManager* getSceneManager();
    static class irr::video::IVideoDriver* getVideoDriver();
    static cAudio::IAudioManager* getAudioManager();
    static class Dispatcher* getDispatcher();
    static class irr::gui::IGUIFont *getFont();

    static void shutdown();

private:
    Globals();
    ~Globals();
    static Globals* instance;

    class irr::IrrlichtDevice* dev;
    class irr::scene::ISceneManager* sman;
    class irr::video::IVideoDriver* drv;
    class cAudio::IAudioManager *audioManager;
    class Dispatcher *dispatcher;
    class irr::gui::IGUIFont *font;
};
#endif // GLOBALS_HPP
