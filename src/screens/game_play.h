#ifndef _GAME_PLAY_H
#define _GAME_PLAY_H

/**
* \file game_play.h
* \brief Tela do jogo principal
*
* Esse módulo define as funções de desenho/atualização do jogo
*/

/**
* \brief Função que libera e termina a tela do jogo principal.
*/
void GamePlay_Exit();

/**
* \brief Função que desenha o conteúdo do jogo na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void GamePlay_Draw(Screen* s);

/**
* \brief Função que atualiza a tela a partir de informações do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a última
*        atualização.
*/
void GamePlay_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicialização de um controlador de telas para desenhar/atualizar
*        a tela do jogo.
* \param s Ponteiro para o controlador de telas Screen.
*/
void InitScreen_GamePlay(Screen* s);


/**
* \brief Define a engine que será utilizada.
* \param engine Parâmetro para a engine.
*
* Essa função serve para mudar a engine para uma
* carregada a partir de um arquivo salvado anteriormente.
* A função não faz nada se o ponteiro for nulo.
*/
void GamePlay_SetEngine(Engine* engine);

/**
* \brief Modifica os ponteiros do controlador de tela para os do game play.
* \param s Ponteiro para a screen.
*
* A função simplesmente altera os ponteiros para as funções
* de desenhar/atualizar, sem inicializar a engine como acontece
* em InitScreen_GamePlay. Serve para fazer transições entre telas
* e voltar sem que essa tenha que começar do zero.
*/
void ResumeScreen_GamePlay(Screen* s);


#endif
