#ifndef _SAVE_GAME_H
#define _SAVE_GAME_H

/**
* \file save_game.h
* \brief Tela de "salvar jogo"
*
* Esse módulo define as funções de desenho/atualização do jogo
*/

/**
* \brief Função que desenha o conteúdo do "salvar jogo" na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void SaveGame_Draw(Screen* s);

/**
* \brief Função que atualiza a tela a partir de informações do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a última
*        atualização.
*/
void SaveGame_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicialização de um controlador de telas para desenhar/atualizar
*        a tela de como jogar.
* \param s Ponteiro para o controlador de telas Screen.
* \param e Ponteiro para a engine que será salvado em arquivo.
*/
void InitScreen_SaveGame(Screen* s, Engine* e);

#endif
