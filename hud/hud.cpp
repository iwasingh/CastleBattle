#include <irrlicht.h>
#include <iostream>
#include "hud.h"
using namespace irr;
namespace HUD{
    void HUD::initHUD(){
                this->font = this->env->getFont("./media/font/myfont.xml");
                if(this->font)
                    this->skin->setFont(this->font);
                /*ADD TEXTS*/
                this->powertext = this->env->addStaticText(L"Power", core::rect<s32>(5,600-32,150,600),false,false,0,POWER_TEXT);

                /*ADD IMAGE-BASED elements*/
                video::ITexture* image = this->driver->getTexture("media/power.png");
                core::rect<s32> pos = this->powertext->getAbsoluteClippingRect();
                core::rect<s32> pos_power = core::rect<s32>(
                    core::position2di(((pos.UpperLeftCorner.X+pos.LowerRightCorner.X)/4),pos.UpperLeftCorner.Y-image->getSize().Height+150),
                    core::position2di(((pos.UpperLeftCorner.X+pos.LowerRightCorner.X)/4)+50,pos.LowerRightCorner.Y-45));
                this->power_rect = pos_power;
                pos_power.UpperLeftCorner.Y = pos_power.LowerRightCorner.Y-1;
                this->power = this->env->addImage(pos_power,0,POWER_BAR);
                this->power->setImage(image);
                this->power->setScaleImage(true);
    }
    HUD::HUD(IrrlichtDevice* device, video::IVideoDriver* video){
                this->device = device;
                this->env = device->getGUIEnvironment();
                this->skin = this->env->getSkin();
                this->driver = video;
                this->initHUD();

    }
    void HUD::animatePower(){
                core::rect<s32> pos = this->power->getAbsoluteClippingRect();
                core::rect<s32> power_pos = pos;

                if(this->velocity > 0){
                power_pos.UpperLeftCorner.Y = power_pos.UpperLeftCorner.Y * this->velocity;
                if(power_pos.UpperLeftCorner.Y >= this->power_rect.LowerRightCorner.Y) this->velocity = SPEED_LOW;
                }
                else
                     power_pos.UpperLeftCorner.Y = power_pos.UpperLeftCorner.Y * this->velocity;
                if(power_pos.UpperLeftCorner.Y <= this->power_rect.UpperLeftCorner.Y) this->velocity =  SPEED_HIGH;

                this->power->setRelativePosition(power_pos);

//                core::line2di dynamicline = core::line2di(
//                core::vector2di(power_pos.UpperLeftCorner),
//                core::vector2di(power_rect.LowerRightCorner));
//
//                core::line2di fulline= core::line2di(
//                core::vector2di(power_rect.UpperLeftCorner),
//                core::vector2di(power_rect.LowerRightCorner));
//                s32 percentage = (s32)(((f32)dynamicline.getLength()/(f32)fulline.getLength())*100);
//                core::stringw percent ="";
//                percent+=percentage;
//                percent+=" %";
//                this->powertext->setText(percent.c_str());

        }
}




