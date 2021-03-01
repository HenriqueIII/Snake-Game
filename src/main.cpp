#include <iostream>
//#include "Game.h"
#include "utils/Display.h"
#include "utils/Point.h"
#include "utils/Random.h"
#include "Obstacle.h"
#include "Arena.h"
#include "Status.h"
#include "Mouse.h"
#include "utils/DeltaTime.h"
int main(){
    Mouse mice;
    ARENA->show();
    STATUS->show();
    DeltaTime delta(0.4F);
    kbd.setMode(Keyboard::VIEW);
    while(kbd.get()==KEY_NONE){
        delta.start();
        mice.show();
        delta.wait();
        mice.hide();
        mice.kill();
    }
    return 0;
}