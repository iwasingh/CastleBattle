#include "gamemanager.h";
using namespace irr;
GameManager::GameManager(scene::ISceneManager* smgr, video::IVideoDriver* driver, IrrlichtDevice* device, core::vector3df worldPosition, Physics* physics){
    this->smgr = smgr;
    this->device = device;
    this->driver = driver;
    this->physics = physics;
    this->worldPosition = worldPosition;
    this->turn = true;
    initGamePlay();
}

void GameManager::initGamePlay(){
    //for now all the players will have the same HUD
    this->hud = new HUD::HUD(device,driver);
    this->players[0] = new Player(this->device,this->smgr,this->driver,this->worldPosition,this->physics,Player::HUMAN);
    this->players[1] = new Player(this->device,this->smgr,this->driver,core::vector3df(this->worldPosition.X, 0, this->players[0]->getCannonRange().Z),this->physics,Player::HUMAN);

}
void GameManager::loop(){
    this->hud->env->drawAll();
    if(!this->players) return;
    if(turn)
        this->players[0]->loop(hud);
    else this->players[1]->loop(hud);
}
