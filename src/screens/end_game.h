#ifndef _END_GAME_H
#define _END_GAME_H

/**
* \file end_game.h
* \brief Tela de "fim de jogo"
*
* Esse módulo define as funções de desenho/atualização do jogo
*/

/**
* \brief Função que desenha o conteúdo do "fim de jogo" na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void EndGame_Draw(Screen* s);

/**
* \brief Função que atualiza a tela a partir de informações do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a última
*        atualização.
*/
void EndGame_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicialização de um controlador de telas para desenhar/atualizar
*        a tela de fim de jogo.
* \param s Ponteiro para o controlador de telas Screen.
* \param finish Inteiro dizendo se quem ganhou foi CPU ou o Jogador.
*/
void InitScreen_EndGame(Screen* s, int finish);

/**
* \brief Função que libera e termina a tela de fim de jogo.
*/
void EndGame_Exit();

#endif
