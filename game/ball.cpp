#include "ball.h"
using namespace irr;

Ball::Ball(scene::ISceneManager* smgr,  video::IVideoDriver* driver, Physics* physics, core::vector3df position){
    this->irrBall = smgr->addSphereSceneNode(this->radius,32,0,-1,position);
    this->irrBall->setMaterialFlag(video::EMF_LIGHTING, false);
    this->irrBall->setMaterialTexture(0,driver->getTexture("media/cannon/cannonballtex.png"));
    this->btBall = physics->createCannonBall(this->irrBall,position, radius);
    this->irrBall->setDebugDataVisible(scene::EDS_FULL);

}
