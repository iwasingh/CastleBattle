#ifndef HUD_H
#define HUD_H
#include <irrlicht.h>
#include <iostream>
using namespace irr;

namespace HUD{

    enum{
    POWER_TEXT,
    POWER_BAR,
    INFO_PLAYER
    };

    const f32 SPEED_HIGH = 1.0098f;
    const f32 SPEED_LOW = 0.975f;
    const s32 MAX_HEIGHT = 237;
    class HUD{
        private:
            gui::IGUISkin* skin;
            IrrlichtDevice* device;
            gui::IGUIFont* font; // global application HUD font
            gui::IGUIStaticText* playerName;
            gui::IGUIStaticText* powertext;
            gui::IGUIImage* power;
            core::rect<s32> power_rect;
            video::IVideoDriver* driver;
            f32 velocity = SPEED_LOW;
            f32 powerRatio;
            void initHUD();

        public:
            gui::IGUIEnvironment* env;
            HUD(IrrlichtDevice* device, video::IVideoDriver* video);
            void animatePower();
            f32 getPower();
            void setPlayerName(core::stringw name);
            void youWin();



    };
};
#endif
