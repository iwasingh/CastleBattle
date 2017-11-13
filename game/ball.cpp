#include "ball.h"
#include <iostream>
using namespace irr;

Ball::Ball(scene::ISceneManager* smgr,  video::IVideoDriver* driver, Physics* physics, core::vector3df position){
    this->irrBall = smgr->addSphereSceneNode(this->radius,32,0,-1,position);
    this->irrBall->setMaterialFlag(video::EMF_LIGHTING, false);
    this->irrBall->setMaterialTexture(0,driver->getTexture("media/cannon/cannonballtex.png"));
    this->btBall = physics->createCannonBall(this->irrBall,position, radius);
//    this->irrBall->setDebugDataVisible(scene::EDS_FULL);
    this->smgr = smgr;
}

//}
void Ball::setCamera(scene::ICameraSceneNode* camera){
    camera->setPosition(this->irrBall->getAbsolutePosition());
    core::vector3df offset = this->cameraStartPosition = camera->getAbsolutePosition();
    core::vector3df rotation = core::vector3df(0,0,0);
    this->camera = new Camera(offset,rotation,this->smgr,0);

}
void Ball::moveCamera(){
        core::vector3df diff = core::vector3df(
            this->irrBall->getAbsolutePosition().X,
            this->irrBall->getAbsolutePosition().Y + 0.2f,
            this->irrBall->getAbsolutePosition().Z - 2.5f);
            this->camera->camera->setPosition(diff);
            this->camera->camera->setTarget(this->irrBall->getAbsolutePosition());
       //this->camera->camera->setTarget(core::vector3df(0,0,0));

}
