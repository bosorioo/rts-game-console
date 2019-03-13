#ifndef _GAME_PLAY_H
#define _GAME_PLAY_H

/**
* \file game_play.h
* \brief Tela do jogo principal
*
* Esse m�dulo define as fun��es de desenho/atualiza��o do jogo
*/

/**
* \brief Fun��o que libera e termina a tela do jogo principal.
*/
void GamePlay_Exit();

/**
* \brief Fun��o que desenha o conte�do do jogo na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void GamePlay_Draw(Screen* s);

/**
* \brief Fun��o que atualiza a tela a partir de informa��es do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a �ltima
*        atualiza��o.
*/
void GamePlay_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicializa��o de um controlador de telas para desenhar/atualizar
*        a tela do jogo.
* \param s Ponteiro para o controlador de telas Screen.
*/
void InitScreen_GamePlay(Screen* s);


/**
* \brief Define a engine que ser� utilizada.
* \param engine Par�metro para a engine.
*
* Essa fun��o serve para mudar a engine para uma
* carregada a partir de um arquivo salvado anteriormente.
* A fun��o n�o faz nada se o ponteiro for nulo.
*/
void GamePlay_SetEngine(Engine* engine);

/**
* \brief Modifica os ponteiros do controlador de tela para os do game play.
* \param s Ponteiro para a screen.
*
* A fun��o simplesmente altera os ponteiros para as fun��es
* de desenhar/atualizar, sem inicializar a engine como acontece
* em InitScreen_GamePlay. Serve para fazer transi��es entre telas
* e voltar sem que essa tenha que come�ar do zero.
*/
void ResumeScreen_GamePlay(Screen* s);


#endif
