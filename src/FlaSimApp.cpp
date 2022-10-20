//flasim-mod https://github.com/dualword/flasim
#include "FlaSimApp.hpp"

#include <iostream>

#include "Globals.hpp"
#include "Dispatcher.hpp"

using namespace std;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

FlaSimApp::FlaSimApp()
 : fireUnit()
{
    dev = Globals::getDevice();
    drv = Globals::getVideoDriver();
    sman = Globals::getSceneManager();

    sman->addSkyBoxSceneNode(drv->getTexture("../res/skytop.jpg"),
                             drv->getTexture("../res/skybottom.jpg"),
                             drv->getTexture("../res/sky3.jpg"),
                             drv->getTexture("../res/sky1.jpg"),
                             drv->getTexture("../res/sky0.jpg"),
                             drv->getTexture("../res/sky2.jpg")
                             );
    auto t = sman->addTerrainSceneNode("../res/heightmap.png");
    t->setScale(vector3df(1.f, .1f, 1.f));
    auto move = t->getTerrainCenter();
    move.Y += 10.f;
    t->setPosition(-move);
    t->setMaterialFlag(EMF_FOG_ENABLE, true);
    t->setMaterialTexture(0, drv->getTexture("../res/detailmap.png"));
    drv->setFog(video::SColor(0, 99, 122, 193), EFT_FOG_EXP, 100.f, 300.f);

    scene::ILightSceneNode *sun = sman->addLightSceneNode();
    sun->setLightType(ELT_DIRECTIONAL);
    sun->setRotation(vector3df(45.f, 0.f, 0.f));
    dev->setEventReceiver(this);
    core::array<SJoystickInfo> joystickInfo;
    if (dev->activateJoysticks(joystickInfo))
    {
        cout << "Joystick support is enabled and " << joystickInfo.size() << " joystick(s) are present." << endl;
    }
}

FlaSimApp::~FlaSimApp()
{

}

void FlaSimApp::execute()
{
    while (dev->run())
    {
        Globals::getDispatcher()->execute();
        drv->beginScene(true, true, SColor(255, 128, 128, 128));
        sman->drawAll();
        drawScreenSpace();
        fireUnit.draw();
        drv->endScene();
    }
}

bool FlaSimApp::OnEvent(const irr::SEvent &e)
{
    if (e.EventType == EET_KEY_INPUT_EVENT && e.KeyInput.PressedDown)
    {
        if (e.KeyInput.Key == KEY_F12)
        {
            dev->closeDevice();
            return true;
        }
        if (e.KeyInput.Key == KEY_F9)
        {
            Globals::getDispatcher()->start();
            return true;
        }
        if (e.KeyInput.Key == KEY_F10)
        {
            Globals::getDispatcher()->stop();
            return true;
        }
        if (e.KeyInput.Key == KEY_KEY_T)
        {
            saveScreenshot();
            return true;
        }
    }

    // if we reach here, relay event to the fireunit
    return fireUnit.OnEvent(e);
}

void FlaSimApp::drawScreenSpace()
{
    video::SMaterial matA;
    matA.AmbientColor = video::SColor(255, 255, 0, 0);
    matA.DiffuseColor = video::SColor(255, 255, 0, 0);
    matA.ColorMaterial = video::ECM_NONE;
    matA.AntiAliasing = video::EAAM_FULL_BASIC;
    matA.Lighting = false;
    matA.Thickness = 1.5f;
    matA.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
    drv->setMaterial(matA);

    drv->setTransform(video::ETS_WORLD, core::IdentityMatrix);

    drv->draw3DLine(vector3df(0.f, 0.f, 0.f), vector3df(1.f, 0.f, 0.f), video::SColor(255, 255, 0, 0));
    drv->draw3DLine(vector3df(0.f, 0.f, 0.f), vector3df(0.f, 1.f, 0.f), video::SColor(255, 0, 255, 0));
    drv->draw3DLine(vector3df(0.f, 0.f, 0.f), vector3df(0.f, 0.f, 1.f), video::SColor(255, 0, 0, 255));

    std::string fps = std::to_string(drv->getFPS());
    core::stringw info = L"FPS: ";
    info.append(fps.c_str());
    info += L"\nRNDS REMAIN: ";
    if (fireUnit.isReloading())
        info += L"[RELOADING]";
    else
        info += fireUnit.getRoundsRemaining();
    info += L"\nAIRCFT REMAIN: "; info += Globals::getDispatcher()->getAircraftsRemaining();
    info += L"\nPOINTS: "; info += Globals::getDispatcher()->getPoints();
    Globals::getFont()->draw(info.c_str(), core::recti(10, 10, 100, 200), video::SColor(255, 255, 255, 255));
}

void FlaSimApp::saveScreenshot()
{
    video::IImage* scrn = nullptr;
    core::stringc fname = "";
    fname += dev->getTimer()->getRealTime();
    io::path filename = fname.c_str();
    filename += ".png";

    scrn = drv->createScreenShot();
    drv->writeImageToFile(scrn, filename);
    scrn->drop();
}
