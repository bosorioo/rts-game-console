#ifndef _END_GAME_H
#define _END_GAME_H

/**
* \file end_game.h
* \brief Tela de "fim de jogo"
*
* Esse m�dulo define as fun��es de desenho/atualiza��o do jogo
*/

/**
* \brief Fun��o que desenha o conte�do do "fim de jogo" na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void EndGame_Draw(Screen* s);

/**
* \brief Fun��o que atualiza a tela a partir de informa��es do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a �ltima
*        atualiza��o.
*/
void EndGame_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicializa��o de um controlador de telas para desenhar/atualizar
*        a tela de fim de jogo.
* \param s Ponteiro para o controlador de telas Screen.
* \param finish Inteiro dizendo se quem ganhou foi CPU ou o Jogador.
*/
void InitScreen_EndGame(Screen* s, int finish);

/**
* \brief Fun��o que libera e termina a tela de fim de jogo.
*/
void EndGame_Exit();

#endif
