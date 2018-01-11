#include <irrlicht.h>
#include <iostream>
#include <Application.h>
using namespace irr;
enum{
  GUI_ID_PLAYER1_NAME,
  GUI_ID_PLAYER2_NAME,
  GUI_ID_START_BUTTON
};
class LauncherEventReceiver : public IEventReceiver{
 private:
  public:
    bool stateElement[4];
    virtual bool OnEvent(const SEvent& event);
    ~LauncherEventReceiver();
};
class Launcher{
  private:
    gui::IGUIEnvironment* gui;
    IrrlichtDevice* device;
    video::IVideoDriver* video;
    gui::IGUIButton* start;
  public:
    gui::IGUIEditBox* players[2];
    LauncherEventReceiver* listener;
    void clear();
    Launcher(gui::IGUIEnvironment* env, IrrlichtDevice* device);
    ~Launcher();
    Launcher();

};
