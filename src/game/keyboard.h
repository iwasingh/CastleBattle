#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<irrlicht.h>
#include <vector>

using namespace irr;
/** Keyboard namespace with all things related to Keyboard, Key, and keyboard mapping */
namespace KEYBOARD{

 enum ACTION_KEYBOARD{ /*!< ACTION_KEYBOARD Enum. All type action possible */
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
    /** Key is a class that describe a irrlicht EKEY_CODE and what ACTION_KEYBOARD is referring */
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
//Maybe templates could be a bettere solution, but this is plain!
//     const Key * KEYBOARD_DEFAULT = new Key[4];
    /** Default Keybaord mapping. */
     const std::vector<Key> KEYBOARD_DEFAULT {
        Key(INCLINATE_UP, KEY_KEY_W),
        Key(INCLINATE_DOWN, KEY_KEY_S),
        Key(INCLINATE_RIGHT, KEY_KEY_D),
        Key(INCLINATE_LEFT, KEY_KEY_A),
        Key(SHOOT, KEY_SPACE)
     };
    /** Keyboard class will handle keyboard events */
    class Keyboard : public IEventReceiver{

    private:
        /** Array of keys */
        bool keyDown[KEY_KEY_CODES_COUNT];
        /** Map key with the ACTION_KEYBOARD specified in the Keyboard vector */
        std::vector<Key> mapKeys;
        /** Last key pressed */
        Key* lastkey;
    public:
        Keyboard();
        void mapKeyboard(const std::vector<Key> keys = KEYBOARD_DEFAULT);
        virtual bool OnEvent(const SEvent& event);
        Key* getLastKey();
        Key* IsKeyDown();
        void resetLastKey();

};
}
#endif
