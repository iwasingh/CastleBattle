#include "player.h"
#include <iostream>
#include <math.h>
using namespace irr;
using namespace KEYBOARD;
using namespace std;
/*
* Each point in the curve can be rotated about the y-axis by an angle θ using the following:

x′=xcos⁡θ−zsin⁡θ
y′=y
z′=xsinθ+zcosθ
*/
void Player::shoot(f32 power){
    if(this->btBall) return;
    f32 angle = this->refreshAngle() * core::DEGTORAD64;
    core::vector3d<f32> * edges = new core::vector3d<f32>[8];
    core::aabbox3d<f32> boundingbox = this->barrel->getBoundingBox();
    boundingbox.getEdges(edges);

    core::vector3d<f32> * edges2 = new core::vector3d<f32>[8]; //no use?
    core::aabbox3d<f32> boundingbox2 = this->cannon->getBoundingBox();
    boundingbox2.getEdges(edges2);

    f32 height = edges[0].Y + sin(angle) * this->initBarrelVector.getLength();
    core::vector3df absolute = this->cannon->getAbsolutePosition();
    f32 left_right_angle = this->cannon->getRotation().Y * core::DEGTORAD64;
    core::vector3df adj = this->initBarrelVector;
    adj = adj.normalize();
    core::matrix4 m;
    m.setRotationDegrees(this->cannon->getRotation());
    m.rotateVect(adj);
    core::vector3df position = core::vector3df(
        absolute.X + adj.X,
        height,
        (absolute.Z + edges[2].Z)
        );
    this->btBall = new Ball(this->smgr,this->driver,this->physics,position);
    f32 shoot_power = power * CANNON_POWER;
    /*
    @TODO recalculation of the shoot vector based on the xyz barrel. This will improve shoot, but noew it works anyway
    */
    core::vector3df shoot = core::vector3df(
        adj.X,
        sin(angle),
        cos(angle)).normalize();

    this->btBall->btBall->setLinearVelocity(toBulletVector(shoot*shoot_power));
    if(this->type == HUMAN)
        this->btBall->setCamera(this->camera->getCamera());
    this->btBall->irrBall->updateAbsolutePosition();
}
/*drawline rotate irrlicht
* Init : ..
*/
Player::Player(IrrlichtDevice* device, scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, Physics* physics, PLAYER_TYPE type){
    this->cannon = smgr->addAnimatedMeshSceneNode(
    smgr->getMesh("media/cannon/cannon.obj"),
    0,
    type,
    position
    );
    this->cannon->setMaterialFlag(video::EMF_LIGHTING, false);
    this->cannon->setMaterialTexture(0,driver->getTexture("media/cannon/cannon_tex.png"));
    this->cannon->setMaterialTexture(1,driver->getTexture("media/cannon/cannonwagon_tex.png"));
    if(type == HUMAN){
        core::vector3df offset =  core::vector3df(
                0,
                this->cannon->getBoundingBox().MaxEdge.Y+0.6f,
                -2.f);

        core::vector3df rotation = core::vector3df(0,0,0);
        this->camera = new Camera(offset,rotation,smgr,cannon);


    }
    this->type = type;
    this->smgr = smgr;
    this->initKeyboard(device);
    this->barrel = this->cannon->getMesh()->getMeshBuffer(0);
    this->wagon = this->cannon->getMesh()->getMeshBuffer(1);
    this->cannon->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)scene::EDS_BBOX_BUFFERS);
   //this->cannon->setDebugDataVisible(scene::EDS_BBOX);

    this->driver = driver;
    this->angle = this->refreshAngle();
    this->btBall = 0;
    this->physics = physics;
    this->rotation = core::vector3df(0,this->cannon->getBoundingBox().getCenter().Y,1); //@deprecated
    this->initAngles();
}
scene::IAnimatedMeshSceneNode* Player::getNode() {
    return this->cannon;
}
void Player::initKeyboard(IrrlichtDevice* device){
    device->setEventReceiver(&this->keyboard);
}
void Player::loop(HUD::HUD* hud){
    Key* key = this->keyboard.IsKeyDown();
    ACTION_KEYBOARD action = key == 0 ? ACTION_NULL : key->action ;
    this->moveCannon(action);
     if(this->btBall && this->type == HUMAN)
                this->btBall->moveCamera();
    switch(action){
        case SHOOT:
                hud->animatePower();
        break;
        default:
            if(this->keyboard.getLastKey()->action == SHOOT){
                this->shoot(hud->getPower());
            }

        break;
    };
}
void Player::initAngles(){
    core::aabbox3df box2 = this->barrel->getBoundingBox();
    core::aabbox3df lower = this->wagon->getBoundingBox();
    core::vector3df med = this->barrel->getBoundingBox().getCenter();
    core::vector3df init = this->barrel->getBoundingBox().MinEdge;
    core::vector3df last;
    init.X = med.X;
    last = init;
    last.Z = this->barrel->getBoundingBox().MaxEdge.Z;
    last.Y+=last.Y;
    this->initBarrelVector = core::line3df(init,last).getVector();
    this->plane = core::vector3df(last.X,init.Y,last.Z) - init;
}
f32 Player::refreshAngle(){



     // cout<<cannonline.getVector().X<< " "<< cannonline.getVector().Y<< " "<<cannonline.getVector().Z<<"     init "<<endl;

//        video::SMaterial material;
//material.Lighting = false;
//        driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);
//
//this->driver->draw3DLine(this->cannon->getAbsolutePosition(),core::vector3df(this->cannon->getAbsolutePosition().X,this->cannon->getAbsolutePosition().Y,this->cannon->getAbsolutePosition().Z + this->barrel->getBoundingBox().getCenter().Z)
//);
    core::vector3df vec1 = this->initBarrelVector;
    core::vector3df vec2 = this->plane;
    vec1 = vec1.normalize();
    vec2 = vec2.normalize();
    f32 length = vec1.getLengthSQ() * vec2.getLengthSQ();
    f32 angle = acos(vec2.dotProduct(vec1) * core::reciprocal_squareroot(length)) * core::RADTODEG64;
    return angle;
}
core::matrix4 Player::getInclinateValues(ACTION_KEYBOARD key){

    irr::core::matrix4 m;
    f32 velocity = 1;
    core::vector3df asd;
    switch(key){
     case INCLINATE_UP:
                if(this->refreshAngle() > MAX_ANGLE_TOP)
                    velocity = 0;
                else {
                    this->angle = this->refreshAngle();
                    velocity = 1;
                }

        m.setRotationDegrees(core::vector3df(-INCLINATE_FACTOR * velocity,0,0));
        m.rotateVect(this->initBarrelVector);

            return m;
        break;
     case INCLINATE_DOWN:
            if(this->refreshAngle() < MAX_ANGLE_BOTTOM)
                    velocity = 0;
            else {
                    this->angle = this->refreshAngle();
                    velocity = 1;
                }
            m.setRotationDegrees(core::vector3df(INCLINATE_FACTOR * velocity,0,0));
            m.rotateVect(this->initBarrelVector);
            return m;
        break;
     case INCLINATE_LEFT:
            if(this->cannon->getRotation().Y > MAX_ANGLE_LEFT)
                velocity = 1;
            else velocity = 0;

            this->cannon->setRotation(core::vector3df(0,this->cannon->getRotation().Y+(-INCLINATE_FACTOR * velocity),0));
            this->cannon->updateAbsolutePosition();
     break;
     case INCLINATE_RIGHT:
                     if(this->cannon->getRotation().Y < MAX_ANGLE_RIGHT)
                velocity = 1;
            else velocity = 0;
            this->cannon->setRotation(core::vector3df(0,this->cannon->getRotation().Y+(INCLINATE_FACTOR * velocity),0));
                        this->cannon->updateAbsolutePosition();


     break;
    }

}
void Player::moveCannon(ACTION_KEYBOARD action){

// for optimization i will some instruction inside the switch that could go outside.In the switch it will not make useless calls
    switch(action){

            case INCLINATE_UP:
                  this->smgr->getMeshManipulator()->transform(this->barrel, this->getInclinateValues(INCLINATE_UP));

            break;

            case INCLINATE_DOWN:
                  this->smgr->getMeshManipulator()->transform(this->barrel, this->getInclinateValues(INCLINATE_DOWN));
            break;

            case INCLINATE_LEFT:
                    this->getInclinateValues(INCLINATE_LEFT);
                  //this->smgr->getMeshManipulator()->transform(this->cannon->getMesh(), this->getInclinateValues(INCLINATE_LEFT));
            break;

            case INCLINATE_RIGHT:
                    this->getInclinateValues(INCLINATE_RIGHT);
            break;
    }

    this->barrel->recalculateBoundingBox();


}



//                std::cout
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().X
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().Y
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().Z
