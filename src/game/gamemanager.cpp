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
    this->stop = false;
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
        HUMAN,
        STRAIGHT);
    this->players[0]->name = L"Player 1";
    this->players[1] = new Player(
        this->device,
        this->smgr,
        this->driver,
        core::vector3df(this->worldPosition.X, 0, this->players[0]->getCannonRange().Z),
        this->physics,
        &this->keyboard,
        HUMAN,
        OPPOSITE);
        this->players[1]->name = L"Player 2";
        this->players[1]->setCannon();
        this->turn = true;
        this->players[0]->focusCamera();

        this->hud->env->drawAll();
        this->hud->setPlayerName(this->players[0]->name);


}
void GameManager::initKeyboard(){
    this->device->setEventReceiver(&this->keyboard);
}
void GameManager::winner(){
}
bool GameManager::loop(){
    this->hud->env->drawAll();
    if(stop) return true;
    if(this->turn){
        if(!this->players[0]->loop(hud)){
            this->turn = false;
            this->players[1]->reset();
            this->players[1]->focusCamera();
            hud->setPlayerName(this->players[1]->name);

        }
        if(this->players[1]->checkTarget()){ stop = true; return true; }

    }
    else {
        if(!this->players[1]->loop(hud)){
            this->turn = true;
            this->players[0]->reset();
            this->players[0]->focusCamera();
            hud->setPlayerName(this->players[0]->name);
        }
        if(this->players[0]->checkTarget()){ stop = true; return true; }


    }


}