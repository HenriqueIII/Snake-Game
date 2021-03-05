#ifndef MOUSE_H
#define MOUSE_H

#include "utils/Point.h"

class Mouse{
    // Posição do rato
    Point pos;
    // Número de vidas
    unsigned lives;
    enum {MOUSE_ENERGY=10, MOUSE_LIVES=20};
    // Define uma nova posição e notifica a arena.
    void newPosition();
public:
    Mouse(unsigned l=MOUSE_LIVES);
    int kill();
    void show() const;
    void hide() const;
    int noMore() const;
    void setLives(int l=MOUSE_LIVES);
};
#endif