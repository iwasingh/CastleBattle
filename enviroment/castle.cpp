#include "castle.h"
#include <irrlicht.h>
#include "helper/bullethelper.h"
#include <iostream>
#include <vector>
using namespace irr;
using namespace core;
using namespace std;
Castle::Castle(scene::ISceneManager* smgr, IrrlichtDevice* device, video::IVideoDriver* driver, core::vector3df center){
    this->smgr = smgr;
    this->driver = driver;
    this->device = device;
    this->nodes.reserve(100);
    this->position = center;
    this->buildCastle(this->position);
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
        core::vector3df ext;
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

                                    this->node = this->smgr->addCubeSceneNode(1,0,-1);
                                    this->node->setPosition(core::vector3df(
                                    center.X + offsets[0] +scale.X/2, scale.Y/2 , center.Z ));
                                    this->node->setScale(scale);
                                    offsets[0] += (width+BLOCKS_OFFSET);
                                    this->node->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)scene::EDS_BBOX_BUFFERS);
                                    this->nodes.push_back(this->node);
                                    break;
                            case 'l':
                                    this->node = this->smgr->addCubeSceneNode(1,0,-1);
                                    this->node->setRotation(core::vector3df(0,90,0));
                                    this->node->setPosition(core::vector3df(
                                    center.X+scale.X/2, scale.Y/2 , scale.X/2+center.Z+offsets[1]));
                                    this->node->setScale(scale);
                                    offsets[1] += (width+BLOCKS_OFFSET);
                                    this->node->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)scene::EDS_BBOX_BUFFERS);
                                    this->nodes.push_back(this->node);

                            break;
                            case 'b':
                                    this->node = this->smgr->addCubeSceneNode(1,0,-1);
                                    this->node->setRotation(core::vector3df(0,0,0));
                                    this->node->setPosition(core::vector3df(
                                    center.X+scale.X/2+offsets[2], scale.Y/2,
                                    center.Z+distance+getMeshSize(nodes.at(nodes.size()-1))[0]+BLOCKS_OFFSET*5
                                    ));
                                    this->node->setScale(scale);
                                    offsets[2] += (width+BLOCKS_OFFSET);
                                    this->node->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)scene::EDS_BBOX_BUFFERS);
                                    this->nodes.push_back(this->node);
                            break;
                            case 'r':
                                    this->node = this->smgr->addCubeSceneNode(1,0,-1);
                                    this->node->setRotation(core::vector3df(0,90,0));
                                    this->node->setPosition(core::vector3df(
                                    center.X+distance-getMeshSize(this->node)[2], scale.Y/2 , scale.X/2+center.Z+offsets[3]));
                                    this->node->setScale(scale);
                                    offsets[3] += (width+BLOCKS_OFFSET);
                                    this->node->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)scene::EDS_BBOX_BUFFERS);
                                    this->nodes.push_back(this->node);
                            break;
                            default:break;
                        }

                    }

                    //..
                    // You can add your own sections and tags to read in here
                    //..
                }
                break;

                //we found the end of an element(side)
                case irr::io::EXN_ELEMENT_END:
                    if(currentSection.equals_ignore_case(xml->getNodeName())) {position = ""; currentSection = ""; };
                break;
            }
        }

        // don't forget to delete the xml reader
        xml->drop();

        return true;

}
