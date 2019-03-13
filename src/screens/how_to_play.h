#ifndef _HOW_TO_PLAY_H
#define _HOW_TO_PLAY_H

/**
* \file how_to_play.h
* \brief Tela de "como jogar"
*
* Esse m�dulo define as fun��es de desenho/atualiza��o do jogo
*/

/**
* \brief Fun��o que desenha o conte�do do "como jogar" na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void HowToPlay_Draw(Screen* s);

/**
* \brief Fun��o que atualiza a tela a partir de informa��es do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a �ltima
*        atualiza��o.
*/
void HowToPlay_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicializa��o de um controlador de telas para desenhar/atualizar
*        a tela de como jogar.
* \param s Ponteiro para o controlador de telas Screen.
*/
void InitScreen_HowToPlay(Screen* s);

#endif
