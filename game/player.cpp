#include "player.h"
#include <iostream>
#include <cmath>
using namespace irr;
using namespace KEYBOARD;
using namespace std;
/*drawline rotate irrlicht
* Init : ..
*/
Player::Player(IrrlichtDevice* device, scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, Physics* physics, Keyboard* keyboard, PLAYER_TYPE type, PLAYER_POSITION side){
    this->type = type;
    this->smgr = smgr;
    this->driver = driver;
    this->physics = physics;
    this->keyboard = keyboard;
    this->camera = 0;
    this->side = side;
    this->castle = new Castle(this->smgr,this->physics, device, this->driver, position);
    position = this->castle->calculateAbsoluteCenter() + core::vector3df(0,0,this->castle->getSideSize('l').X);
    this->cannon = new Cannon(device, smgr,driver,position,physics);

}
scene::IAnimatedMeshSceneNode* Player::getNode() {
    return this->cannon->getCannon();
}
bool Player::loop(HUD::HUD* hud){
    if(stop) return false;
    Key* key = this->keyboard->IsKeyDown();
    ACTION_KEYBOARD action = key == 0 ? ACTION_NULL : key->action;
    if(!this->cannon->moveCannon(action)) return false;

    switch(action){
        case SHOOT:
                hud->animatePower();
        break;
        default:
            if(this->keyboard->getLastKey()->action == SHOOT){
                this->cannon->shoot(hud->getPower());

                this->keyboard->resetLastKey();
            }

        break;
    };
    return true;
}
core::vector3df Player::getCannonRange(){
return this->cannon->getRange();
}
void Player::focusCamera(){
    if(this->type == HUMAN && !this->cannon->getCamera()){
        core::vector3df offset;
        switch(this->side){
            case STRAIGHT:
                 offset =  core::vector3df(
                0,
                this->cannon->getBoundingBox().MaxEdge.Y+0.6f,
                -2.f);
            break;
            case OPPOSITE:
                offset =  core::vector3df(
                0,
                this->cannon->getBoundingBox().MaxEdge.Y+0.6f,
                -2.f);
        };
        core::vector3df rotation = this->cannon->getCannon()->getRotation();
        this->cannon->setCamera(offset,rotation,smgr,this->cannon->getCannon());
        this->stop = false;
    }
}
void Player::setCannon(){
    switch(this->side){

        case OPPOSITE:
            core::vector3df position = this->castle->calculateAbsoluteCenter() - core::vector3df(0,0,this->castle->getSideSize('l').X);
            this->cannon->setRotation(core::vector3df(0,180,0));
            this->cannon->setPosition(position);
            break;
    }
}
