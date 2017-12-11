#include <irrlicht.h>
#include "physics.h"
#include <hud.h>
#include "player.h"
#include "keyboard.h"
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
        Keyboard keyboard; //for now all players have same keymap
        void initKeyboard();
    public:
        bool stop;
        GameManager(scene::ISceneManager* smgr, video::IVideoDriver* driver, IrrlichtDevice* device, core::vector3df worldPosition, Physics* physics);
        void initGamePlay();
        bool loop();
        void winner();

};
