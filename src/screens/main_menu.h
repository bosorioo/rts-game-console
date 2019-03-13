#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

/**
* \file main_menu.h
* \brief Tela do menu principal
*
* Esse módulo define as funções de desenho/atualização do jogo
*/

/**
* \brief Função que libera e termina a tela do menu principal.
*/
void MainMenu_Exit();

/**
* \brief Função que desenha o conteúdo do menu principal na tela.
* \param s Ponteiro para o controlador de telas Screen.
*/
void MainMenu_Draw(Screen* s);

/**
* \brief Função que atualiza a tela a partir de informações do tempo
* \param s Ponteiro para o controlador de telas Screen.
* \param total_time Quantos segundos se passaram desde que o programa
*        foi executado.
* \param delta_time Quanto tempo se passou em segundos desde a última
*        atualização.
*/
void MainMenu_Update(Screen* s, float total_time, float delta_time);

/**
* \brief Inicialização de um controlador de telas para desenhar/atualizar
*        a tela do menu principal.
* \param s Ponteiro para o controlador de telas Screen.
*/
void InitScreen_MainMenu(Screen* s);

#endif
