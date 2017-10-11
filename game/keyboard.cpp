#include "keyboard.h"
#include <iostream>
using namespace KEYBOARD;
Key::Key(ACTION_KEYBOARD action, EKEY_CODE k){
    this->action = action;
    this->key = k;
};

Keyboard::Keyboard(){
    for(u32 i = 0; i < KEY_KEY_CODES_COUNT; i++){
        this->keyDown[i] = false;
    }
    this->mapKeyboard();
}
bool Keyboard::OnEvent(const SEvent& event) {
    if(event.EventType == EET_KEY_INPUT_EVENT)
        this->keyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
}
Key* Keyboard::IsKeyDown(){

   for(std::vector<Key>::const_iterator it = this->mapKeys.begin(); it != this->mapKeys.end(); ++it){
          if(this->keyDown[it->key]) return new Key(it->action,it->key);
    }
    return 0; // null


//    if(this->keyDown[keyCode]) return keyCode;
//    else (EKEY_CODE)0x0;

};
void Keyboard::mapKeyboard( const Key*keys){

//        if(keys == 0) this->mapKeys.push_back(Key(INCLINATE_UP, KEY_KEY_W));

            std::cout<<keys->action;
            this->mapKeys.clear();
            this->mapKeys.assign(keys,keys + sizeof(keys) / sizeof(keys[0]));

};

