
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<irrlicht.h>
#include <vector>

using namespace irr;
namespace KEYBOARD{

 enum ACTION_KEYBOARD{
                INCLINATE_UP = 1,
                INCLINATE_DOWN,
                INCLINATE_LEFT,
                INCLINATE_RIGHT,
                MOVE_LEFT,
                MOVE_RIGHT,
                MOVE_UP,
                MOVE_DOWN,
                SHOOT,
                ACTION_NULL
            };

    class Key{
        private:
        public:
          ACTION_KEYBOARD action;
            EKEY_CODE key;
            Key(ACTION_KEYBOARD act, EKEY_CODE k);
            Key getKey();
    };
//     const Key KEYBOARD_TEMPLATE[] ={
//         Key(INCLINATE_UP, KEY_KEY_W),
//         Key(INCLINATE_DOWN, KEY_KEY_S),
//         Key(INCLINATE_RIGHT, KEY_KEY_D),
//         Key(INCLINATE_LEFT, KEY_KEY_A)
//    };

//     const Key * KEYBOARD_DEFAULT = new Key[4];
     const std::vector<Key> KEYBOARD_DEFAULT {
        Key(INCLINATE_UP, KEY_KEY_W),
        Key(INCLINATE_DOWN, KEY_KEY_S),
        Key(INCLINATE_RIGHT, KEY_KEY_D),
        Key(INCLINATE_LEFT, KEY_KEY_A),
        Key(SHOOT, KEY_SPACE)
     };
    class Keyboard : public IEventReceiver{

    private:
        bool keyDown[KEY_KEY_CODES_COUNT];
        std::vector<Key> mapKeys;
        Key* lastkey;
    public:
        Keyboard();
        void mapKeyboard(const std::vector<Key> keys = KEYBOARD_DEFAULT);
        virtual bool OnEvent(const SEvent& event);
        Key* getLastKey();
        Key* IsKeyDown();

};
}
#endif

