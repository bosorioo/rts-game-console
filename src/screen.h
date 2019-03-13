#ifndef _SCREEN_H
#define _SCREEN_H

#include "display.h"

/**
* \file screen.h
* \brief Controlador de telas (menu principal, tela de instru��es etc).
*
* Define a estrutura Screen, que possui ponteiros para fun��es
* espec�ficas que a cada certo intervalo de tempo, chama essas
* fun��es que s�o respons�veis por fazer os c�lculo necess�rios
* pelo programa e redesenhar o Display.
*/

/**
* \brief Estrutura que atua como "controlador de tela".
*/
struct Screen
{
    void (*onRender)(struct Screen* s);
    void (*onUpdate)(struct Screen* s, float total_time, float delta_time);
    void (*onKeyInput)(struct Screen* s, int key, const char* keyString);
    char (*onExit)(struct Screen* s);

    Display* display;
    int running;
};

typedef struct Screen Screen;

/**
* \brief Aloca e inicializa uma nova Screen
* \return O ponteiro para a estrutura iniciada
*
* Caso a aloca��o falhe, � retornada NULL. A screen
* � iniciada com ponteiros de atualiza��o/renderiza��o
* iguais a nulos.
*/
Screen* Screen_New();

/**
* \brief Libera os recursos utilizadas por uma Screen
* \param s Ponteiro para a Screen que deve ser liberada.
*
* A fun��o n�o faz nada caso o ponteiro seja nulo. A fun��o
* assume que caso o ponteiro n�o seja nulo, o mesmo aponte
* para uma Screen v�lida.
*/
void Screen_Delete(Screen* s);

/**
* \brief Sinaliza para o controlador que o jogo deve ser encerrado
* \param s Ponteiro para a screen que deve ser liberada.
*
* A fun��o n�o faz nada caso o ponteiro seja nulo. A fun��o
* assume que caso o ponteiro n�o seja nulo, o mesmo aponte
* para uma Screen v�lida. A fun��o simplesmente altera o campo
* "running" da Screen. No pr�ximo loop principal do programa,
* tudo ser� encerrado e liberado.
*/
void Screen_Stop(Screen* s);

/**
* \brief Verifica se a Screen foi encerrada
* \param s Ponteiro para a screen que deve ser verificada
* \return Retorna 1 caso a Screen ainda esteja executando ou
*         0 se ela foi encerrada.
*
* A fun��o retorna 0 caso o ponteiro seja nulo. A fun��o
* assume que caso o ponteiro n�o seja nulo, o mesmo aponte
* para uma Screen v�lida.
*/
int Screen_IsRunning(Screen* s);

#endif // _SCREEN_H
