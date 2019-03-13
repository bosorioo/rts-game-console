#ifndef _COLOR_MAN_H
#define _COLOR_MAN_H

/**
* \file color_manager.h
* \brief Gerenciador de pares de cores da ncurses
*
* Esse módulo disponibiliza uma única função que retorna
* o identificar de um par de cores da biblioteca ncurses.
* Essa função gerencia quando um novo par de cores deve
* ser iniciado e caso o mesmo par seja necessário novamente,
* apenas retorna o identificador do par já iniciado.
*/

/*******************
* \brief Obtém o identificador de um par de cores da ncurses.
* \param c1 Valor que define uma cor (ncurses) para os caracteres
*        que serão impressos na tela, por exemplo, COLOR_WHITE.
* \param c2 Valor que define uma cor para o plano de fundo.
*
* A função inicializa (pela função do ncurses) o
* par de cores para alterar as cores do terminal. Caso o par de
* cores já estiver inicializado, apenas retorna o identificador
* do par.
* \return O número identificar de um par de cores para ser usado
* por outras funções do ncurses.
*******************/
int Color_GetId(short c1, short c2);

#endif // _COLOR_MAN_H
