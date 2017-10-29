#include "game.h"


Game* Game::getInstance(){
        static Game* instance = nullptr;
        if(instance == nullptr){
                instance= new Game();
        }
        return instance;
}