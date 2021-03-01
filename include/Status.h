#ifndef STATUS_H
#define STATUS_H

#include <cassert> 
#include <cstring>  // memset

#include "utils/Display.h"
#include "utils/Keyboard.h"
#include "utils/Common.h"

class Status{
    static Status * instance;
    // Pontuação
    unsigned points;
    enum{
        STATUS_Y = Display::MAX_Y,      // Coordenada Y
        STATUS_X = Display::MIN_X+2,    // Coordenada X
        SCORE_X = STATUS_X+8,           // Coordenada X da pontuação
        DIM_MSG = 20,                   // Dimensão máxima das mensagens
        MSG_X = Display::MAX_X - DIM_MSG
    };
    // Mostra a mensagem s na coordenada (x,STATUS_Y)
    static void puts(int x, const char * s);
    // Mostra a mensagem msg na coordenada (MSG_X,STATUS_Y)
    static void show(const char * msg);
    // Oculta a mensagem
    static void hide();
    // Mostra um valor numérico u na coordenada (x,STATUS_Y)
    static void putu(int x, unsigned u);
    // Mostra em (SCORE_X,STATUS_Y) a pontuação corrente.
    void showScore() const;
public:
    // Inicia com a pontuação a zero e implementa sólitário
    Status();
    // Mostra "Score:" e a pontuação
    void show();
    // Adiciona p ao score corrente e mostra o novo score
    void addScore(int p);
    // Mostra a mensagem enquanto não for premida uma tecla
    static void showAndWait(const char * msg);
    static Status * getInstance();
};

#define STATUS Status::getInstance()

#endif