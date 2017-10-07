/** Example 001 HelloWorld

This Tutorial shows how to set up the IDE for using the Irrlicht Engine and how
to write a simple HelloWorld program with it. The program will show how to use
the basics of the VideoDriver, the GUIEnvironment, and the SceneManager.
Microsoft Visual Studio is used as an IDE, but you will also be able to
understand everything if you are using a different one or even another
operating system than windows.

You have to include the header file <irrlicht.h> in order to use the engine. The
header file can be found in the Irrlicht Engine SDK directory \c include. To let
the compiler find this header file, the directory where it is located has to be
specified. This is different for every IDE and compiler you use. Let's explain
shortly how to do this in Microsoft Visual Studio:

- If you use Version 6.0, select the Menu Extras -> Options.
  Select the directories tab, and select the 'Include' Item in the combo box.
  Add the \c include directory of the irrlicht engine folder to the list of
  directories. Now the compiler will find the Irrlicht.h header file. We also
  need the irrlicht.lib to be found, so stay in that dialog, select 'Libraries'
  in the combo box and add the \c lib/VisualStudio directory.
  \image html "vc6optionsdir.jpg"
  \image latex "vc6optionsdir.jpg"
  \image html "vc6include.jpg"
  \image latex "vc6include.jpg"

- If your IDE is Visual Studio .NET, select Tools -> Options.
  Select the projects entry and then select VC++ directories. Select 'show
  directories for include files' in the combo box, and add the \c include
  directory of the irrlicht engine folder to the list of directories. Now the
  compiler will find the Irrlicht.h header file. We also need the irrlicht.lib
  to be found, so stay in that dialog, select 'show directories for Library
  files' and add the \c lib/VisualStudio directory.
  \image html "vcnetinclude.jpg"
  \image latex "vcnetinclude.jpg"

That's it. With your IDE set up like this, you will now be able to develop
applications with the Irrlicht Engine.

Lets start!

After we have set up the IDE, the compiler will know where to find the Irrlicht
Engine header files so we can include it now in our code.
*/
#include <irrlicht.h>
#include "enviroment/Terrain.h"
#include "enviroment/Sky.h"
#include "hud/hud.h"
#include "game/player.h"
/*
In the Irrlicht Engine, everything can be found in the namespace 'irr'. So if
you want to use a class of the engine, you have to write irr:: before the name
of the class. For example to use the IrrlichtDevice write: irr::IrrlichtDevice.
To get rid of the irr:: in front of the name of every class, we tell the
compiler that we use that namespace from now on, and we will not have to write
irr:: anymore.
*/
using namespace irr;

/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look at them, you can
read a detailed description of them in the documentation by clicking on the top
menu item 'Namespace List' or by using this link:
http://irrlicht.sourceforge.net/docu/namespaces.html
Like the irr namespace, we do not want these 5 sub namespaces now, to keep this
example simple. Hence, we tell the compiler again that we do not want always to
write their names.
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
/*
@TODO
Main Game class with all 3 main irrlicht classes(device,video,scene) to optimize code inside main()

*/
int main() {

    IrrlichtDevice* device = createDevice(EDT_OPENGL,dimension2d<u32>(800,600),16, false,false,false,0);
    device->getCursorControl()->setVisible(false);
    IVideoDriver* driver = device->getVideoDriver();
    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
    ISceneManager* smgr = device->getSceneManager();

    core::stringw pathTexture[2] = {"media/terrain/grass_green_old.jpg","media/terrain/grass_green_thin.jpg"};
    Terrain* terrain = new Terrain(smgr,driver,pathTexture,vector3df(250.f,0.0001f, 250.f));
    Sky* sky = new Sky(smgr,driver,"media/terrain/sky.jpg",1000.0f);
    HUD::HUD* hud = new HUD::HUD(device,driver);

    Player* player = new Player(smgr,driver,terrain->getCenter(), Player::HUMAN);
    Player* ai = new Player(smgr,driver,terrain->getCenter()-core::vector3df(0,0,-10.f),Player::AI);

    terrain->collisionResponseAnimator(smgr,player->getNode());


//    terrain->addCollisionNode(smgr,);
//    scene::ISceneCollisionManager* csmgr = smgr->getSceneCollisionManager();
    smgr->setAmbientLight(video::SColor(0,255,255,204));
    int lastFPS = -1;
    while(device->run() && device) {

        if(device->isWindowActive()){

            driver->beginScene(true, true, video::SColor(255,200,200,200));
            smgr->drawAll();
            hud->env->drawAll();
            driver->endScene();
            int fps = driver->getFPS();
            if(lastFPS != fps)
            {
                stringw str =L"Castle Battle [";
                str += driver->getName();
                str += "] FPS:";
                str += fps;
                device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
        } else
            device->yield();
    }
}

/*
That's it. Compile and run.
    //cube->setPosition(vector3df(25,-10,50)); // z forward(if positive) and back, x left-right, y up down
//    //cube->setMaterialFlag(video::EMF_LIGHTING, false);
    /*
        The Octree optimizes the scene a little bit, trying to draw only geometry which is currently visible.
        An alternative to the Octree would be a irr::scene::IMeshSceneNode, which would always draw the complete geometry of the mesh, without optimization.
    */

//    IAnimatedMesh* map_mesh = smgr->getMesh("./media/Second.obj");
//    ISceneNode* map_node = 0;
//
//    if(map_mesh) map_node = smgr->addOctreeSceneNode(map_mesh->getMesh(0), 0, -1, 1024);
//    if(map_node) map_node->setPosition(core::vector3df(0,-5,0));
//
//    map_node->setMaterialTexture(0,driver->getTexture("./media/FirstMap.png"));
//    //ILightSceneNode* light = smgr->addLightSceneNode(0, core::vector3df(400,800,-1400),video::SColor(0,255,255,204),2000.0f);
//    smgr->setAmbientLight(video::SColor(0,255,255,204));
