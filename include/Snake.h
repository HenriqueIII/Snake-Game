#ifndef SNAKE_H
#define SNAKE_H

#include "utils/Point.h"

class Snake{
    // Declaração nested privada, que fica exclusivamente
    // reconhecida dentro da classe Snake.
    class Vertebra{
        Point pos;
    public:
        // Ocultar a vertebra e desmarcar a posição na arena.
        void hide();
        // Mostra a vertebra no ponto pos figurada com '#'.
        void show();
        // Mostra a vertebra no ponto p figurada com '#' e
        // marca a posição no array bidimensional.
        void show(Point p);
    }; // Fim da classe Vertebra

    // Declaração nested privada de uma lista duplamente
    // ligada de apontadores para vertebras
    class VertebraList{
        struct VertebraNode{
            Vertebra * data;
            VertebraNode * ptNext, * ptPrev;
            VertebraNode(Vertebra * vv, VertebraNode * next){
                data = vv;
                ptNext = next;
                ptPrev = next->ptPrev;
                ptNext->ptPrev = ptPrev->ptNext = this;

            }
            VertebraNode(){
                ptNext = ptPrev = this;
            }
            ~VertebraNode(){
                ptPrev->ptNext = ptNext;
                ptNext->ptPrev = ptPrev;
            }
        };
        VertebraNode sentinel;
    public:
        ~VertebraList();
        // Inserir a vértebra no inicio da lista
        void insertHead(Vertebra * vv);
        // Remover a ultima vertebra da lista
        Vertebra * removeEnd();
        // Testa se a lista está vazia.
        inline bool isEmpty();
        // Mostrar todas as vértebras da lista
        void show();
    };
    // Direção de movimento, NONE significa sem direcção
    // e MAX é o número total de direções
    enum DirValue {NONE=-1, UP=0, LEFT, DOWN, RIGHT, MAX};
    // Numero de vertebras inicial da cobra
    enum {SNAKE_INIT_SIZE=2};
    // Cabeça da cobra
    Point head;
    // Cauda da cobra
    VertebraList tail;
    // Dircção em que se move
    DirValue dir;
    // Número de vertebras que falta crescer
    int toGrow;
    // Assinala se a cobra esta morta
    bool dead;

    /*  Mata o rato e incementa toGrow função da energia
        devolvida pelo rato e incrementa a pontuação        */
    inline void eat();
    /*  Situa a cabeça de Snake num ponto aleatório livre
        da arena e marca na arena esse ponto como ocupado   */
    inline void setHead();
    /*  Oculta do ecrã a cabeça da cobra, liberta o ponto
        do ecrã que ela ocupava e situa-a no novo ponto     */
    inline void changeHead(const Point & newHead);
    /*  Afecta dir com a nova direcção caso não seja oposta */
    inline void changeDirection(DirValue d);
    inline void hideHead() const;
    inline void showHead() const;
    inline void kill();
    inline void advance(Point delta);
public:
    inline Snake();
    inline ~Snake();
    inline bool isDead() const;
    inline void show();
    void move();
};
#endif