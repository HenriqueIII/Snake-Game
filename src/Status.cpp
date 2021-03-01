#include "Status.h"

Status * Status::instance = NULL;

void Status::puts(int x, const char * s){
    // Posiciona o cursor
    dsp.setCursor(x,STATUS_Y);
    // Imprime a vermelho
    dsp.setForeground(Display::BRED);
    // Escreve string s na posição do cursor
    dsp.puts(s);
}
void Status::show(const char * msg){
    puts(MSG_X,msg);
}
void Status::hide(){
    // Reserva o espaço
    char tmp[DIM_MSG];
    // Prenche com espaços
    memset(tmp,' ',DIM_MSG-1);
    // Coloca terminador de string
    tmp[DIM_MSG-1] = '\0';
    show(tmp);
}
void Status::putu(int x, unsigned u){
    // Reserva o espaço
    char tmp[DIM_MSG];
    // Convert inteiro base 10 em string
    Common::strcpy(tmp,Common::itoa(u));
    // Mostra a string tmp na coluna x
    puts(x, tmp);
}
void Status::showScore() const{
    putu(SCORE_X, points);
}
Status::Status(){
    points=0;
    assert(instance==NULL);
    instance=this;
}
void Status::show(){
    puts(STATUS_X,"Score: ");
    showScore();
}
void Status::addScore(int p){
    points += p;
    showScore();
}
void Status::showAndWait(const char * msg){
    show(msg);
    kbd.setMode(kbd.WAIT);
    kbd.get();
    hide();
}
Status * Status::getInstance(){
    assert(instance);
    return instance;
}