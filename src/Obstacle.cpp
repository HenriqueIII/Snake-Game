#include "Obstacle.h"
#include "Arena.h"

void Obstacle::print(char c) const{
    Point o = base;
    for (int i=0; i<len; ++i){
        dsp.putc(o.getX(), o.getY(), c, Display::WHITE);
        if (type == VERTICAL)
            o.setY(o.getY()+1);
        else
            o.setX(o.getX()+1);
    }
}
inline void Obstacle::setPosition(const Point & p){
    ARENA->set(p, Arena::OBSTACLE);
}
Obstacle::Obstacle(Point o, ObstacleType t, int l){
    base = o;
    len = l;
    type = t;
    for (int i=0; i < len; ++i){
        setPosition(o);
        if(t==VERTICAL)
            o.setY(o.getY()+1);
        else
            o.setX(o.getX()+1);
    }
}
Obstacle::~Obstacle(){
    Point o = base;
    for (int i=0; i < len; ++i){
        // Oculta o ponto
        dsp.putc(o.getX(),o.getY(),' ');
        // Notifica a arena (posição livre)
        ARENA->reset(o);
        if(type==VERTICAL)
            o.setY(o.getY()+1);
        else
            o.setX(o.getX()+1);
    }
}
void Obstacle::show() const{
    print('X');
}
void Obstacle::hide() const{
    print(' ');
}