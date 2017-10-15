#include "player.h"
#include <iostream>
#include <math.h>

using namespace KEYBOARD;

Player::Player(IrrlichtDevice* device, scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, PLAYER_TYPE type){
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
        this->camera = smgr->addCameraSceneNode(0,
            core::vector3df(
                this->cannon->getPosition().X,
                this->cannon->getPosition().Y+this->cannon->getBoundingBox().MaxEdge.Y+0.6f,
                this->cannon->getPosition().Z-2.f));
        this->camera->setTarget(this->cannon->getAbsolutePosition());
        this->camera->bindTargetAndRotation(true);
        this->camera->setRotation(core::vector3df(0,0,0));
        this->camera->setFarValue(3000.f);
    }
    this->smgr = smgr;
    this->initKeyboard(device);

    this->barrel = this->cannon->getMesh()->getMeshBuffer(0);
    this->wagon = this->cannon->getMesh()->getMeshBuffer(1);
    this->cannon->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)scene::EDS_BBOX_BUFFERS);
    this->driver = driver;
    this->angle = this->refreshAngle();
}
scene::IAnimatedMeshSceneNode* Player::getNode() {
    return this->cannon;
}
void Player::initKeyboard(IrrlichtDevice* device){
    device->setEventReceiver(&this->keyboard);
}
void Player::loop(){
    Key* key = this->keyboard.IsKeyDown();
    ACTION_KEYBOARD action = key == 0 ? ACTION_NULL : key->action ;
    this->inclinate(action);
}
f32 Player::refreshAngle(){

//  std::cout<<acos(vec2.dotProduct(vec1) * core::reciprocal_squareroot(lenght)) * core::RADTODEG64<<std::endl;
    core::aabbox3df box2 = this->barrel->getBoundingBox();
    core::aabbox3df lower = this->wagon->getBoundingBox();
//    core::vector3df vec1 = box2.MaxEdge.normalize();
    core::line3df cannonline = core::line3df(this->barrel->getPosition(1),this->barrel->getPosition(this->barrel->getVertexCount()-1));
    core::vector3df vec1 = cannonline.getVector().normalize();
    core::vector3df vec2 = lower.MaxEdge.normalize();
    f32 length = vec1.getLengthSQ() * vec2.getLengthSQ();
    return acos(vec2.dotProduct(vec1) * core::reciprocal_squareroot(length)) * core::RADTODEG64;


}
core::matrix4 Player::getInclinateValues(ACTION_KEYBOARD key){

    irr::core::matrix4 m;
    f32 velocity = 1;
    std::cout<<this->refreshAngle()<<std::endl;
    switch(key){
     case INCLINATE_UP:
                if(this->refreshAngle() > MAX_ANGLE_TOP)
                    velocity = 0;
                else {
                    this->angle = this->refreshAngle();
                    velocity = 1;
                }

                m.setRotationDegrees(core::vector3df(-INCLINATE_FACTOR * velocity,0,0));

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

            return m;
        break;
    }

}
void Player::inclinate(ACTION_KEYBOARD action){


//    core::line3df cannonline = core::line3df(this->barrel->getPosition(1),this->barrel->getPosition(this->barrel->getVertexCount()-1));

//    vec1 = cannonline.getVector().normalize();
//    f32 lenght = vec1.getLengthSQ() * vec2.getLengthSQ();
////  std::cout<<acos(vec2.dotProduct(vec1) * core::reciprocal_squareroot(lenght)) * core::RADTODEG64<<std::endl;
//    cannonline = core::line3df(this->barrel->getPosition(1),this->barrel->getPosition(this->barrel->getVertexCount()-1));
//    box = this->barrel->getBoundingBox();
//    f32 angle = cannonline.getVector().dotProduct(box.MaxEdge);
//    std::cout<<angle<<std::endl;

//    this->driver->setTransform(video::ETS_WORLD, this->cannon->getAbsoluteTransformation());
//    this->driver->draw3DLine(cannonline.start,cannonline.end, video::SColor(0,255,0,0));
// for optimization i will some instruction inside the switch that could go outside.In the switch it will not make useless calls
    switch(action){

            case INCLINATE_UP:
                  this->smgr->getMeshManipulator()->transform(this->barrel, this->getInclinateValues(INCLINATE_UP));
            break;

            case INCLINATE_DOWN:
                  this->smgr->getMeshManipulator()->transform(this->barrel, this->getInclinateValues(INCLINATE_DOWN));
            break;
    }

    this->barrel->recalculateBoundingBox();

}



//                std::cout
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().X
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().Y
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().Z
