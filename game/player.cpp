#include "player.h"
#include <iostream>
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
    this->initKeyboard(device);

    this->barrel = this->cannon->getMesh()->getMeshBuffer(0);
    this->wagon = this->cannon->getMesh()->getMeshBuffer(1);
    this->cannon->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)scene::EDS_BBOX_BUFFERS);
    this->driver = driver;
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
void Player::inclinate(ACTION_KEYBOARD action){
    core::aabbox3df box = this->barrel->getBoundingBox();
    core::aabbox3df lower = this->wagon->getBoundingBox();
    irr::core::matrix4 m;

    core::line3df cannonline = core::line3df(this->barrel->getPosition(1),this->barrel->getPosition(this->barrel->getVertexCount()-1));
    this->driver->setTransform(video::ETS_WORLD, this->cannon->getAbsoluteTransformation());

    this->driver->draw3DLine(cannonline.start,cannonline.end, video::SColor(0,255,0,0));
    box.MaxEdge.rotateYZBy()
    for(unsigned int i = 0; i < this->barrel->getVertexCount(); i++){

        switch(action){

            case INCLINATE_UP:

                this->barrel->getPosition(i).rotateYZBy(
                    -0.5f * INCLINATE_FACTOR,
                    core::vector3df(0,0,0)
                );// up and down
//                    box.MaxEdge.rotateXZBy(2.f, core::vector3df(0,0,0));
//                    box.MinEdge.rotateYZBy(2.f, core::vector3df(0,0,0));


                cannonline = core::line3df(this->barrel->getPosition(1),this->barrel->getPosition(this->barrel->getVertexCount()-1));
                box = this->barrel->getBoundingBox();

                f32 angle = cannonline.getVector().dotProduct(box.MaxEdge);
                std::cout<<angle<<std::endl;

//                std::cout
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().X
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().Y
//                <<" "<<this->barrel->getPosition(0).getHorizontalAngle().Z
//                <<std::endl;
//                std::cout
//                <<" "<<box.MaxEdge.X
//                <<" "<<box.MaxEdge.Y
//                <<" "<<box.MaxEdge.Z
//                <<std::endl;

//                std::cout
//                <<" "<<cannonline.getVector().getHorizontalAngle().X
//                <<" "<<cannonline.getVector().getHorizontalAngle().Y
//                <<" "<<cannonline.getVector().getHorizontalAngle().Z
//                <<std::endl;

            break;
        }
//        cannonUpper->getPosition(i).rotateXZBy(-5.f,core::vector3df(0,0,0)); //left right, should be minimal
    }





    this->barrel->recalculateBoundingBox();

}
