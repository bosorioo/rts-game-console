#ifndef _LOAD_GAME_H
#define _LOAD_GAME_H

/**
* \file load_game.h
* \brief Tela de "carregar jogo"
*
* Esse m�dulo define as fun��es de desenho/atualiza��o do jogo
*/

/**
* \brief Fun��o que desenha o conte�do do "carregar jogo" na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void LoadGame_Draw(Screen* s);

/**
* \brief Fun��o que atualiza a tela a partir de informa��es do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a �ltima
*        atualiza��o.
*/
void LoadGame_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicializa��o de um controlador de telas para desenhar/atualizar
*        a tela de carregar jogo.
* \param s Ponteiro para o controlador de telas Screen.
*/
void InitScreen_LoadGame(Screen* s);

#endif
