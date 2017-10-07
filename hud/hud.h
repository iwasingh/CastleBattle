#include <irrlicht.h>
#include <iostream>
using namespace irr;

namespace HUD{

    enum{
    POWER_TEXT,
    POWER_BAR
    };

    const f32 SPEED_HIGH = 1.0098f;
    const f32 SPEED_LOW = 0.975f;

    class HUD{
        private:
            gui::IGUISkin* skin;
            IrrlichtDevice* device;
            gui::IGUIFont* font; // global application HUD font
            gui::IGUIStaticText* powertext;
            gui::IGUIImage* power;
            core::rect<s32> power_rect;
            video::IVideoDriver* driver;
            f32 velocity = SPEED_LOW;

            void initHUD();

        public:
            gui::IGUIEnvironment* env;
            HUD(IrrlichtDevice* device, video::IVideoDriver* video);
            void animatePower();


    };
};
