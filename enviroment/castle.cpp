#include "castle.h"
#include <irrlicht.h>
#include "helper/bullethelper.h"
#include <iostream>
#include <vector>
using namespace irr;
using namespace core;
using namespace std;
Castle::Castle(scene::ISceneManager* smgr, Physics* physics, IrrlichtDevice* device, video::IVideoDriver* driver, core::vector3df center){
    this->smgr = smgr;
    this->driver = driver;
    this->device = device;
    this->physics = physics;
    this->nodes.reserve(100);
    this->position = center;
    this->COLOR_DARK = randomColor();
    this->COLOR_LIGHT = randomColor();
    if(this->buildCastle(this->position)) this->addToPhysicsWorld();
}

bool Castle::buildCastle(core::vector3df center){

        irr::io::IXMLReader* xml = this->device->getFileSystem()->createXMLReader("media/castle/castle.xml");  //create xml reader
        if (!xml)
            return false;

        const stringw sideTag(L"side"); //we'll be looking for this tag in the xml
        core::stringw currentSection; //keep track of our current section
        const stringw blockTag(L"block"); //constant for blocktag
        core::stringc position, lastposition;
        float width, height, distance;
        core::vector3d<f32> * edges = new core::vector3d<f32>[8];
        f32 offsets[4]={0,0,0,0};
        u32 reading = -1 ;
        core::vector3df pos;
        core::aabbox3d<f32> box;
        core::matrix4 transformer;
        //while there is more to read
        while (xml->read())
        {
            //check the node type
            switch (xml->getNodeType())
            {
                //we found a new element
                case irr::io::EXN_ELEMENT:
                {
                    //we currently are in the empty or mygame section and find the side tag so we set our current block
                    if (currentSection.empty() && sideTag.equals_ignore_case(xml->getNodeName()))
                    {
                        currentSection = sideTag;
                        position = xml->getAttributeValueSafe(L"position");
                        distance = xml->getAttributeValueAsFloat(L"distance");
                        reading++;
                        // maybe a switch case is better
                        if(reading == 1) offsets[reading] = BLOCKS_OFFSET+getMeshSize(nodes.front())[0]/2;
                        if(reading == 2) offsets[reading] = BLOCKS_OFFSET+getMeshSize(nodes.back())[0]/2;
                        if(reading == 3) offsets[reading] = BLOCKS_OFFSET+getMeshSize(nodes.front())[0]/2;

                    } else if (currentSection.equals_ignore_case(sideTag) && blockTag.equals_ignore_case(xml->getNodeName())){
                        //read in the key
                         core::vector3df scale = core::vector3df(1.f,1.f,1.f);
                        width = xml->getAttributeValueAsFloat(L"width");
                        height = xml->getAttributeValueAsFloat(L"height");
                        scale = core::vector3df(width,height,1);

                        switch(position[0]){
                            case 'f':
                                    pos = core::vector3df(
                                    center.X + offsets[0] +scale.X/2, scale.Y/2 , center.Z );
                                    this->createBlock(pos,scale, core::vector3df(0,0,0));
                                    offsets[0] += (width+BLOCKS_OFFSET);
                                    break;
                            case 'l':
                                    pos = core::vector3df(
                                    center.X+scale.X/2, scale.Y/2 , scale.X/2+center.Z+offsets[1]);
                                    this->createBlock(pos,scale,core::vector3df(0,90,0));
                                    offsets[1] += (width+BLOCKS_OFFSET);
                            break;
                            case 'b':
                                    pos = core::vector3df(
                                    center.X+scale.X/2+offsets[2], scale.Y/2,
                                    center.Z+distance+getMeshSize(nodes.at(nodes.size()-1))[0]+BLOCKS_OFFSET*5
                                    );
                                    this->createBlock(pos,scale,core::vector3df(0,0,0));
                                    offsets[2] += (width+BLOCKS_OFFSET);



                            break;
                            case 'r':
                                    pos = core::vector3df(
                                    center.X+distance-getMeshSize(this->node)[2], scale.Y/2 , scale.X/2+center.Z+offsets[3]);
                                    this->createBlock(pos,scale,core::vector3df(0,90,0));
                                    offsets[3] += (width+BLOCKS_OFFSET);


                            break;
                            default:break;
                        }

                    }

                }
                break;

                // found the end of an element(side)
                case irr::io::EXN_ELEMENT_END:
                    if(currentSection.equals_ignore_case(xml->getNodeName())) {position = ""; currentSection = ""; };
                break;
            }
        }

        // delete the xml reader
        xml->drop();

        return true;

}
//useless?
void Castle::addToPhysicsWorld(){

    for(vector<scene::IMeshSceneNode *>::iterator it = this->nodes.begin();it != nodes.end(); ++it){
    }
}
void Castle::createBlock(core::vector3df position, core::vector3df scale, core::vector3df rotation){
      this->node = this->smgr->addCubeSceneNode(1,0,-1);
      this->node->setPosition(position);
      this->node->setScale(scale);
      this->node->setMaterialFlag(video::EMF_LIGHTING,false);
      this->smgr->getMeshManipulator()->setVertexColors(this->node->getMesh(),this->COLOR_DARK);
      this->node->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)scene::EDS_BBOX_BUFFERS); // debug mask
      if(this->node){ // need an assert here.
        this->nodes.push_back(this->node);
        this->physics->createCastleBlock(this->node,rotation,scale,position);
      }
}