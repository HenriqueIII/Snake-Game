#include "Mouse.h"
#include "Arena.h"

void Mouse::newPosition(){
    ARENA->set(pos = ARENA->freePlace(), Arena::MOUSE);
}
Mouse::Mouse(unsigned l){
    lives=l;
    newPosition();
}
int Mouse::kill(){
    if (--lives){
        ARENA->reset(pos);
        newPosition();
        show();
    }
    return MOUSE_ENERGY; // Energia passada à cobra
}
void Mouse::show() const{
    dsp.putc(pos.getX(), pos.getY(), '@');
}
void Mouse::hide() const{
    dsp.putc(pos.getX(), pos.getY(), ' ');
}
int Mouse::noMore() const{
    return lives == 0;
}
void Mouse::setLives(int l){
    lives = l;
}