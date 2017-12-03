#include <irrlicht.h>
#include "physics.h"
#include <hud/hud.h>
#include <game/player.h>
using namespace irr;

class GameManager{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        IrrlichtDevice* device;
        Physics* physics;
        Player* players[2];
        bool turn; //true -> first player, false second player
        core::vector3df worldPosition;
        HUD::HUD* hud;

    public:
        GameManager(scene::ISceneManager* smgr, video::IVideoDriver* driver, IrrlichtDevice* device, core::vector3df worldPosition, Physics* physics);
        void initGamePlay();
        void loop();
};
