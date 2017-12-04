#include "gamemanager.h";
using namespace irr;
using namespace std;
GameManager::GameManager(scene::ISceneManager* smgr, video::IVideoDriver* driver, IrrlichtDevice* device, core::vector3df worldPosition, Physics* physics){
    this->smgr = smgr;
    this->device = device;
    this->driver = driver;
    this->physics = physics;
    this->worldPosition = worldPosition;
    this->turn = true;
    initGamePlay();
    initKeyboard();
}

void GameManager::initGamePlay(){
    //for now all the players will have the same HUD
    this->hud = new HUD::HUD(device,driver);
    this->players[0] = new Player(
        this->device,
        this->smgr,
        this->driver,
        this->worldPosition,
        this->physics,
        &this->keyboard,
        HUMAN);
    this->players[1] = new Player(
        this->device,
        this->smgr,
        this->driver,
        core::vector3df(this->worldPosition.X, 0, this->players[0]->getCannonRange().Z),
        this->physics,
        &this->keyboard,
        HUMAN,
        OPPOSITE);
        this->players[1]->setCannon();
        this->turn = true;
        this->players[0]->focusCamera();

}
void GameManager::initKeyboard(){
    this->device->setEventReceiver(&this->keyboard);
}
void GameManager::loop(){
    this->hud->env->drawAll();
    if(!this->players) return;
    if(turn){
        if(!this->players[0]->loop(hud)){
            turn = false;
            this->players[1]->focusCamera();
        }
    }
    else {
        this->players[1]->loop(hud);
        }
}
