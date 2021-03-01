#include "Arena.h"

Arena * Arena::instance = new Arena;

void Arena::makeBorder(){
    obst[0] = new Obstacle(Point(0,0),Obstacle::VERTICAL,dsp.MAX_Y);
    obst[1] = new Obstacle(Point(dsp.MAX_X,0),Obstacle::VERTICAL,dsp.MAX_Y);
    obst[2] = new Obstacle(Point(1,0), Obstacle::HORIZONTAL, dsp.MAX_X-1);
    obst[3] = new Obstacle(Point(1,dsp.MAX_Y-1), Obstacle::HORIZONTAL, dsp.MAX_X-1); 
}
Arena::Arena(){
    // Impedir múltiplas instâncias
    assert(instance==NULL);
    // Afetar apontador para singleton
    instance = this;
    for (int x = 0; x < dsp.MAX_X; ++x)
        for (int y = 0; y < dsp.MAX_Y; ++y)
            // Iniciar como vazia a matriz posicional dos atores
            board[x][y]=NONE;
    // Construir os obstáculos
    makeBorder();
    // Iniciar o gerador pseudo-aleatório
    Random::init();
}
Arena::~Arena(){
    for (int i=0; i<MAX_OBST; ++i)
        delete obst[i];
}
void Arena::reset(Point o){
    set(o,NONE);
}
void Arena::set(Point o, ActorType t){
    assert(o.getX() < dsp.MAX_X+1 && o.getY() < dsp.MAX_Y+1);
    board[o.getX()][o.getY()] = t;
}
Arena::ActorType Arena::get(Point o) const{
    return board[o.getX()][o.getY()];
}
/*  Retorna um ponto aleatório interior à arena onde
    ainda não se situe nenhum ator.    */
Point Arena::freePlace() const{
    Point r;
    do{
        r = Point(Random::get(dsp.MAX_X),Random::get(dsp.MAX_Y-1));    
    }while(get(r)!=NONE);
    return r;
}
void Arena::show() const{
    for (int i=0;i<MAX_OBST;++i)
        obst[i]->show();
}
Arena * Arena::getInstance(){
    assert(instance);
    return instance;
}