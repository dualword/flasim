#include "FlaSimApp.hpp"

#include <iostream>

#include "Globals.hpp"

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
        drv->beginScene(true, true, SColor(255, 128, 128, 128));
        sman->drawAll();
        drawScreenSpace();
        drv->endScene();
    }
}

bool FlaSimApp::OnEvent(const irr::SEvent &e)
{
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
}
