#include "Snake.h"
#include "utils/Keyboard.h"
#include "Arena.h"
#include "Status.h"
#include "Game.h"

void Snake::Vertebra::hide(){
    // Oculta a vertebra
    dsp.putc(pos.getX(), pos.getY(), ' ');
    // Notifica a arena
    ARENA->reset(pos);
}
void Snake::Vertebra::show(){
    // Mostra a vertebra
    dsp.putc(pos.getX(),pos.getY(),'#');
}
void Snake::Vertebra::show(Point p){
    ARENA->set(pos=p, Arena::SNAKE);
    show();
}
Snake::VertebraList::~VertebraList(){
    while(!isEmpty()){
        sentinel.ptNext->data->hide();
        delete sentinel.ptNext->data;
        delete sentinel.ptNext;
    }
}
void Snake::VertebraList::insertHead(Vertebra * vv){
    new VertebraNode(vv,sentinel.ptNext);
}
Snake::Vertebra * Snake::VertebraList::removeEnd(){
    Vertebra * aux = sentinel.ptPrev->data;
    delete sentinel.ptPrev;
    return aux;
}
bool Snake::VertebraList::isEmpty(){
    return sentinel.ptNext == &sentinel;
}
void Snake::VertebraList::show(){
    for (VertebraNode * curr = sentinel.ptNext; curr != &sentinel; curr=curr->ptNext)
        curr->data->show();
}
/*  Mata o rato e incementa toGrow função da energia
devolvida pelo rato e incrementa a pontuação        */
void Snake::eat(){
    toGrow += GAME->getMouse()->kill();
    STATUS->addScore(1);
}
/*  Situa a cabeça de Snake num ponto aleatório livre
    da arena e marca na arena esse ponto como ocupado   */
void Snake::setHead(){
    ARENA->set(head = Point(Display::MAX_X/2, (Display::MAX_Y-1)/2), Arena::SNAKE);
}
/*  Oculta do ecrã a cabeça da cobra, liberta o ponto
    do ecrã que ela ocupava e situa-a no novo ponto     */
void Snake::changeHead(const Point & newHead){
    ARENA->reset(head);
    ARENA->set(head=newHead, Arena::SNAKE);
}
/*  Afecta dir com a nova direcção caso não seja oposta */
void Snake::changeDirection(DirValue d){
    // (DirValue (x+2) % MAX) corresponde à direcção oposta
    // a x, segundo os valores atribuidos na enumeração
    if( dir == NONE || d != DirValue((dir+2)%MAX))
        dir = d;
}
void Snake::hideHead() const{
    dsp.putc(head.getX(), head.getY(), ' ');
}
void Snake::showHead() const{
    dsp.putc(head.getX(), head.getY(), 'O');
}
void Snake::kill(){
    dead=TRUE;
}
void Snake::advance(Point newHead){
    Vertebra * v;
    Point oldHead = head;
    changeHead(newHead);
    showHead();
    // Remover e esconder a última vértebra
    if(!toGrow){
        v = tail.removeEnd();
        v->hide();
    }else{  // Em crescimento não remove a última vértebra
        v = new Vertebra;
        --toGrow;
    }
    // Inserir a primeira vertebra
    tail.insertHead(v);
    v->show(oldHead);
} 
Snake::Snake(){
    setHead();
    dir = NONE;
    toGrow = SNAKE_INIT_SIZE;
    dead = false;
}
Snake::~Snake(){
    hideHead();
}
bool Snake::isDead() const{
    return dead;
}
void Snake::show(){
    showHead();
    tail.show();
}
void Snake::move(){
    // Vetor de pontos correspondentes aos deslocamentos
    // unitarios nas quatro possiveis direções
    static Point vector[] = {Point(0,-1), Point(-1,0), Point(0,1), Point(1,0)};
    switch (kbd.get()){
        case KEY_UP:
            changeDirection(UP);
            break;
        case KEY_DOWN:
            changeDirection(DOWN);
            break;
        case KEY_LEFT:
            changeDirection(LEFT);
            break;
        case KEY_RIGHT:
            changeDirection(RIGHT);
            break;
    }

    if(dir==NONE)
        return;

    Point newHead = head.add(vector[dir]);

    switch (ARENA->get(newHead)){
    case Arena::MOUSE:
        eat();
        break;
    case Arena::SNAKE:
    case Arena::OBSTACLE:
        kill();
        return;
    }
    advance(newHead);
}