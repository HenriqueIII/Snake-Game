#ifndef GAME_H
#define GAME_H

#include <Person.h>
#include <Monsters.h>
#include <cstring>

class Game{
    enum ExitType {GAME_OVER, MONSTERS_DEAD, PERSON_DEAD};
    Monsters monsters;
    Person person;
    ExitType play();
public:
    Game(int n=10);
    ~Game();
    void run();
};

#endif