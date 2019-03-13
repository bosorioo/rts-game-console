#ifndef _LOAD_GAME_H
#define _LOAD_GAME_H

/**
* \file load_game.h
* \brief Tela de "carregar jogo"
*
* Esse módulo define as funções de desenho/atualização do jogo
*/

/**
* \brief Função que desenha o conteúdo do "carregar jogo" na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void LoadGame_Draw(Screen* s);

/**
* \brief Função que atualiza a tela a partir de informações do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a última
*        atualização.
*/
void LoadGame_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicialização de um controlador de telas para desenhar/atualizar
*        a tela de carregar jogo.
* \param s Ponteiro para o controlador de telas Screen.
*/
void InitScreen_LoadGame(Screen* s);

#endif
