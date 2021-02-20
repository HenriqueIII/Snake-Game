#include <Game.h>
#include <Keyboard.h>

Game::Game(int n){
    Point p;
    // Inicia o gerador pseudo-aleatório
    Random::init();
    for (int i=0; i < n; ++i){
        // Afecta p com um valor aleatorio gerado por
        // random() que não seja igual à posição da pessoa
        // nem a de nenhum dos monstros já criado.
        do p = Random::get(Point(0,0),Point(79, 23));
        while (p.isEqual(person.getPos()) || monsters.detectCollisions(p));
        // Cria um monstro na posição p atrás obtida e insere
        // em monsters o apontador para o monstro criado.
        monsters.insert(new Monster(p));
    }
}
Game::~Game(){
    dsp.~Display();
}

void Game::run(){
    // Mensagem final função de ExitType
    const char * msg[] = {"Game Over", "Game Over ** WIN", "Game Over ** OH!!"};
    // Mostra o personagem
    person.show();
    // Mostra os monstros
    monsters.show();
    // Guarda a condição terminal.
    ExitType e = play();
    // Colocar '*' na posição da pessoa.
    if (e == PERSON_DEAD)
        dsp.putc(person.getPos().getX(), person.getPos().getY(), '*');
    // Mostrar a mensagem a meio da última linha do ecrã
    dsp.setCursor((dsp.MAX_X - strlen(msg[e]))/2, dsp.MAX_Y);
    dsp.puts(msg[e]);
    // Esperar a actuação de Enter
    while (kbd.get() != 10);
}
Game::ExitType Game::play(){
    Point p;
    while(1){
        // Retorna PERSON_DEAD se um monstro colide com pessoa.
        if (monsters.detectCollisions(person.getPos()))
            return Game::PERSON_DEAD;
        // Remove os monstros que colidiram entre si
        // e caso nenhum subsista retorna MONSTERS_DEAD
        if (monsters.allDead())
            return Game::MONSTERS_DEAD;
        switch (kbd.get()){
            case 27:
                return Game::GAME_OVER;
        // Caso seja uma tecla de direcção
        // afecta p com o deslocamento correspondente
            case KEY_UP:
                p = Point(0,-1);
                break;
            case KEY_DOWN:
                p = Point(0,1);
                break;
            case KEY_LEFT:
                p = Point(-1,0);
                break;
            case KEY_RIGHT:
                p = Point(1,0);
                break;
            case KEY_PPAGE:
                p = Point(1,-1);
                break;
            case KEY_NPAGE:
                p = Point(1,1);
                break;
            case KEY_END:
                p = Point(-1,1);
                break;
            case KEY_HOME:
                p = Point(-1,-1);
                break;
        // Se a tecla é KEY_INS, promove um salto aleatório
        // da pessoa e move os monstros na sua direcção.
            case KEY_IC:
                person.jump();
                monsters.move(person.getPos());
        // Reinicia novo ciclo
            default:
                continue;        
        }
        // Caso p seja um deslocamento valido para a pessoa
        // mover a pessoa e os monstros na direcção da pessoa
        if (person.drag(p))
            monsters.move(person.getPos());
    }
}