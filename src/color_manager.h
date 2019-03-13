#ifndef _COLOR_MAN_H
#define _COLOR_MAN_H

/**
* \file color_manager.h
* \brief Gerenciador de pares de cores da ncurses
*
* Esse m�dulo disponibiliza uma �nica fun��o que retorna
* o identificar de um par de cores da biblioteca ncurses.
* Essa fun��o gerencia quando um novo par de cores deve
* ser iniciado e caso o mesmo par seja necess�rio novamente,
* apenas retorna o identificador do par j� iniciado.
*/

/*******************
* \brief Obt�m o identificador de um par de cores da ncurses.
* \param c1 Valor que define uma cor (ncurses) para os caracteres
*        que ser�o impressos na tela, por exemplo, COLOR_WHITE.
* \param c2 Valor que define uma cor para o plano de fundo.
*
* A fun��o inicializa (pela fun��o do ncurses) o
* par de cores para alterar as cores do terminal. Caso o par de
* cores j� estiver inicializado, apenas retorna o identificador
* do par.
* \return O n�mero identificar de um par de cores para ser usado
* por outras fun��es do ncurses.
*******************/
int Color_GetId(short c1, short c2);

#endif // _COLOR_MAN_H
