#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "utils/Point.h"
#include "utils/Display.h"
//#include "Arena.h"

class Obstacle{
public:
    enum ObstacleType{VERTICAL,HORIZONTAL};
private:
    // Ponto origem da fila.
    Point base;
    // Comprimento da fila.
    int len;
    // Tipo de obstáculo
    ObstacleType type;
    // Mostra no ecrã uma fila de caracteres c.
    void print(char c) const;
    //Notifica a arena sobre a posição do obstáculo.
    void setPosition(const Point & p);
public:
/*  Constrói o obstáculo afetando os atributos e 
    marcando na arena as posições que nela ocupa        */
    Obstacle(Point o, ObstacleType t=VERTICAL, int len=1);
/*  Oculta o obstáculo e informa a arena que as posições
    que ocupava estão livres                            */
    ~Obstacle();
    void show() const;
    void hide() const;
};
#endif