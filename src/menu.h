#ifndef _MENU_H
#define _MENU_H
#include "display.h"

/**
* \file menu.h
* \brief Cria��o de menus que possuem op��es para interagir com o usu�rio
*
* Esse m�dulo define a estrutura Menu que cria menus com op��es
* de maneira gen�rica. Todas as fun��es cujo primeiro par�metro
* � um ponteiro para Menu funcionam da mesma forma: se o ponteiro
* for nulo, a fun��o n�o faz nada, e caso contr�rio � assumido
* que o mesmo aponta para uma estrutura Menu v�lida.
*/

/**
* \brief Estrutura que guarda informa��es sobre uma op��o dentro de um menu.
*/
struct MenuOption
{
    char* option; /**< String da op��o. */
    struct MenuOption* next; /**< Ponteiro para o prox. elemento da lista. */
};

/**
* \brief Estrutura que define um menu.
*/
typedef struct
{
    char* title; /**< T�tulo do menu. */
    struct MenuOption* options; /**< Lista encadeada das op��es */
    int options_count; /**< Qntd. de op��es que o menu tem */
    int selected_option; /**< �ndice da op��o que est� selecionada */
    int click; /**< �ndice da op��o que o usu�rio escolheu  */
    int width; /**< Largura necess�ria para se criar o menu */
} Menu;

/**
* \brief Aloca mem�ria para um novo menu.
* \param title String do t�tulo do menu.
* \return Ponteiro para o novo menu alocado.
*
* A fun��o aloca mem�ria para um Menu e inicializa ele sem op�es.
* Caso a aloca��o falhe, a fun��o retorna NULO. A fun��o tamb�m
* cria uma string que � uma c�pia do valor do par�metro \a title
* para dar um t�tulo ao menu. Caso a string seja nula, o menu fica
* sem t�tulo.
*/
Menu* Menu_New(char* title);

/**
* \brief Libera os recursos de um menu.
* \param m Ponteiro para o menu que ser� liberado.
*
* Libera todos a mem�ria utilizada pelo menu e pelas
* op��es adicionadas a ele.
*/
void Menu_Delete(Menu* m);

/**
* \brief Adiciona uma nova op��o ao menu.
* \param m Ponteiro para o menu.
* \param option String da op��o.
*
* A fun��o aloca uma nova op��o e adiciona � lista encadeada de
* op��es do menu. Se a string for maior que a atual largura do menu,
* atualiza a largura para que o desenho da caixa fique correto.
* Cada op��o faz uma aloca��o de string e apenas copia o valor
* do par�metro \a option para a string que foi alocada.
*/
void Menu_AddOption(Menu* m, char* option);

/**
* \brief Desenha um menu em um Display em uma dada coordenada.
* \param m Ponteiro para o menu que ser� desenhado.
* \param d Ponteiro para o display onde ser� desenhado.
* \param row Linha onde ser� desenhado.
* \param col Coluna onde ser� desenhado.
*
* A fun��o desenha todas as op��es do menu no display. Se o
* ponteiro \a d for nulo, a fun��o n�o faz nada.
*/
void Menu_Draw(Menu* m, Display* d, int row, int col);

/**
* \brief Envia ao menu alguma entrada do usu�rio para processar.
* \param m Ponteiro para o menu que receber� o input.
* \param key N�mero que descreve o input.
*
* Caso o input seja seta para cima, o menu seleciona a op��o de cima,
* caso o input seja a tecla ENTER, a fun��o indica que o usu�rio
* escolheu aquela op��o etc...
*/
void Menu_Input(Menu* m, int key);

/**
* \brief Obt�m a �ltima op��o escolhida pelo usu�rio.
* \param m Ponteiro para o menu.
* \return �ndice da op��o que foi escolhida pelo usu�rio (ou -1 quando
*         n�o h�).
*
* A fun��o verifica se alguma das op��es foi escolhida pelo usu�rio
* e retorna essa op��o. Uma op��o � escolhida quando o menu
* recebe a tecla ENTER pela fun��o Menu_Input. Ap�s retornar
* que uma op��o foi escolhida, a mesma op��o n�o estar� mais
* escolhida a menos que outro ENTER seja enviado ao menu, ou seja,
* duas chamadas consecutivas � essa fun��o n�o retornam o mesmo valor,
* pois assim que uma escolha do usu�rio foi resgatada por essa fun��o,
* esse escolha do usu�rio � desmarcada.
*/
int Menu_Click(Menu* m);

#endif // _MENU_H
