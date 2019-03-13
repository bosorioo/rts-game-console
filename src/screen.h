#ifndef _SCREEN_H
#define _SCREEN_H

#include "display.h"

/**
* \file screen.h
* \brief Controlador de telas (menu principal, tela de instruções etc).
*
* Define a estrutura Screen, que possui ponteiros para funções
* específicas que a cada certo intervalo de tempo, chama essas
* funções que são responsáveis por fazer os cálculo necessários
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
* Caso a alocação falhe, é retornada NULL. A screen
* é iniciada com ponteiros de atualização/renderização
* iguais a nulos.
*/
Screen* Screen_New();

/**
* \brief Libera os recursos utilizadas por uma Screen
* \param s Ponteiro para a Screen que deve ser liberada.
*
* A função não faz nada caso o ponteiro seja nulo. A função
* assume que caso o ponteiro não seja nulo, o mesmo aponte
* para uma Screen válida.
*/
void Screen_Delete(Screen* s);

/**
* \brief Sinaliza para o controlador que o jogo deve ser encerrado
* \param s Ponteiro para a screen que deve ser liberada.
*
* A função não faz nada caso o ponteiro seja nulo. A função
* assume que caso o ponteiro não seja nulo, o mesmo aponte
* para uma Screen válida. A função simplesmente altera o campo
* "running" da Screen. No próximo loop principal do programa,
* tudo será encerrado e liberado.
*/
void Screen_Stop(Screen* s);

/**
* \brief Verifica se a Screen foi encerrada
* \param s Ponteiro para a screen que deve ser verificada
* \return Retorna 1 caso a Screen ainda esteja executando ou
*         0 se ela foi encerrada.
*
* A função retorna 0 caso o ponteiro seja nulo. A função
* assume que caso o ponteiro não seja nulo, o mesmo aponte
* para uma Screen válida.
*/
int Screen_IsRunning(Screen* s);

#endif // _SCREEN_H
