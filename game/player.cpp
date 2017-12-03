#include "player.h"
#include <iostream>
#include <cmath>
using namespace irr;
using namespace KEYBOARD;
using namespace std;
/*drawline rotate irrlicht
* Init : ..
*/
Player::Player(IrrlichtDevice* device, scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, Physics* physics, PLAYER_TYPE type){
    this->cannon = new Cannon(smgr,driver,position,physics);
    if(type == HUMAN){
        core::vector3df offset =  core::vector3df(
                0,
                this->cannon->getBoundingBox().MaxEdge.Y+0.6f,
                -2.f);

        core::vector3df rotation = core::vector3df(0,0,0);
        this->cannon->setCamera(offset,rotation,smgr,this->cannon->getCannon());
    }
    this->type = type;
    this->smgr = smgr;
    this->initKeyboard(device);
    this->driver = driver;
    this->physics = physics;
    this->castle = new Castle(this->smgr,this->physics, device, this->driver, position);
    this->cannon->setPosition(this->castle->calculateAbsoluteCenter() + core::vector3df(0,0,this->castle->getSideSize('l').X));
}
scene::IAnimatedMeshSceneNode* Player::getNode() {
    return this->cannon->getCannon();
}
void Player::initKeyboard(IrrlichtDevice* device){
    device->setEventReceiver(&this->keyboard);
}
void Player::loop(HUD::HUD* hud){
    Key* key = this->keyboard.IsKeyDown();

    ACTION_KEYBOARD action = key == 0 ? ACTION_NULL : key->action ;

    this->cannon->moveCannon(action);

    switch(action){
        case SHOOT:
                hud->animatePower();
        break;
        default:
            if(this->keyboard.getLastKey()->action == SHOOT){
                this->cannon->shoot(hud->getPower());
                this->keyboard.resetLastKey();
            }

        break;
    };
}
core::vector3df Player::getCannonRange(){
return this->cannon->getRange();
}
