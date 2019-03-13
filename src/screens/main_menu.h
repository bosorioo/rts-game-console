#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

/**
* \file main_menu.h
* \brief Tela do menu principal
*
* Esse m�dulo define as fun��es de desenho/atualiza��o do jogo
*/

/**
* \brief Fun��o que libera e termina a tela do menu principal.
*/
void MainMenu_Exit();

/**
* \brief Fun��o que desenha o conte�do do menu principal na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void MainMenu_Draw(Screen* s);

/**
* \brief Fun��o que atualiza a tela a partir de informa��es do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a �ltima
*        atualiza��o.
*/
void MainMenu_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicializa��o de um controlador de telas para desenhar/atualizar
*        a tela do menu principal.
* \param s Ponteiro para o controlador de telas Screen.
*/
void InitScreen_MainMenu(Screen* s);

#endif
