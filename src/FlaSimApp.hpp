#include "FireUnit.hpp"

//! Main app class
class FlaSimApp : public irr::IEventReceiver
{
public:
    FlaSimApp();
    ~FlaSimApp();

    void execute();

    bool OnEvent(const irr::SEvent& e);

private:
    void drawScreenSpace();
    void saveScreenshot();

    irr::IrrlichtDevice *dev;
    irr::scene::ISceneManager *sman;
    irr::video::IVideoDriver *drv;
    irr::gui::IGUIEnvironment *gui;



    FireUnit fireUnit;
};
