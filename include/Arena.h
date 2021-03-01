#ifndef ARENA_H
#define ARENA_H

#include "utils/Random.h"
#include <cassert>
#include "Obstacle.h"
#include "utils/Display.h"

class Arena{
public:
    enum ActorType{NONE, MOUSE, SNAKE, OBSTACLE};
private:
    // Matriz posicional dos atores na arena
    ActorType board[Display::MAX_X+1][Display::MAX_Y+1];
    // Numero de Obstáculos
    enum {MAX_OBST = 4};
    // Contentor de Obstáculos
    Obstacle * obst[MAX_OBST];
    // Constrói a borda
    void makeBorder();
    // Apontador para singleton
    static Arena * instance;
public:
    // Inicia a arena com a borda
    Arena();
    // Destrói os obstáculos da cercadura
    ~Arena();
    // Afetar board[o.x][o.y] com o ActorType NONE
    // que significa não existir ator nesse ponto.
    void reset(Point o);
    // Afetar board[o.x][o.y] com o ActorType t
    // Aborta se as coordenadas não pertencerem à arena
    void set(Point o, ActorType t);
    // Retorna o tipo de ator que se encontra na posição o
    ActorType get(Point o) const;
    // Retorna um ponto aleatório que esteja livre
    Point freePlace() const;
    // Mostra os obstáculos
    void show() const;  
    static Arena * getInstance();
};

// Macro para abreviar chamadas as funções de arena.
#define ARENA Arena::getInstance()

#endif