#include "ball.h"
#include <iostream>
using namespace irr;

Ball::Ball(scene::ISceneManager* smgr,  video::IVideoDriver* driver, Physics* physics, core::vector3df position){
    this->irrBall = smgr->addSphereSceneNode(this->radius,32,0,-1,position);
    this->irrBall->setMaterialFlag(video::EMF_LIGHTING, false);
    this->irrBall->setMaterialTexture(0,driver->getTexture("media/cannon/cannonballtex.png"));
    this->btBall = physics->createCannonBall(this->irrBall,position, radius);
    this->btBall->activate(true);
//    this->irrBall->setDebugDataVisible(scene::EDS_FULL);
    this->smgr = smgr;
}

//}
void Ball::setCamera(scene::ICameraSceneNode* camera){
    camera->setPosition(this->irrBall->getAbsolutePosition());

    core::vector3df offset = this->cameraStartPosition = camera->getAbsolutePosition();
    this->camera = new Camera(offset,camera->getRotation(),this->smgr,0);


}
void Ball::moveCamera(){
    core::vector3df diff = core::vector3df(
            this->irrBall->getAbsolutePosition() + CAMERA_OFFSET_BALL);
    this->camera->camera->setPosition(diff);
    this->camera->camera->setTarget(this->irrBall->getAbsolutePosition());
    this->irrBall->updateAbsolutePosition();
    this->camera->camera->updateAbsolutePosition();


 //this->camera->camera->setTarget(core::vector3df(0,0,0));

}
