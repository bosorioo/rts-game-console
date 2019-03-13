#ifndef _MENU_H
#define _MENU_H
#include "display.h"

/**
* \file menu.h
* \brief Criação de menus que possuem opções para interagir com o usuário
*
* Esse módulo define a estrutura Menu que cria menus com opções
* de maneira genérica. Todas as funções cujo primeiro parâmetro
* é um ponteiro para Menu funcionam da mesma forma: se o ponteiro
* for nulo, a função não faz nada, e caso contrário é assumido
* que o mesmo aponta para uma estrutura Menu válida.
*/

/**
* \brief Estrutura que guarda informações sobre uma opção dentro de um menu.
*/
struct MenuOption
{
    char* option; /**< String da opção. */
    struct MenuOption* next; /**< Ponteiro para o prox. elemento da lista. */
};

/**
* \brief Estrutura que define um menu.
*/
typedef struct
{
    char* title; /**< Título do menu. */
    struct MenuOption* options; /**< Lista encadeada das opções */
    int options_count; /**< Qntd. de opções que o menu tem */
    int selected_option; /**< Índice da opção que está selecionada */
    int click; /**< Índice da opção que o usuário escolheu  */
    int width; /**< Largura necessária para se criar o menu */
} Menu;

/**
* \brief Aloca memória para um novo menu.
* \param title String do título do menu.
* \return Ponteiro para o novo menu alocado.
*
* A função aloca memória para um Menu e inicializa ele sem opões.
* Caso a alocação falhe, a função retorna NULO. A função também
* cria uma string que é uma cópia do valor do parâmetro \a title
* para dar um título ao menu. Caso a string seja nula, o menu fica
* sem título.
*/
Menu* Menu_New(char* title);

/**
* \brief Libera os recursos de um menu.
* \param m Ponteiro para o menu que será liberado.
*
* Libera todos a memória utilizada pelo menu e pelas
* opções adicionadas a ele.
*/
void Menu_Delete(Menu* m);

/**
* \brief Adiciona uma nova opção ao menu.
* \param m Ponteiro para o menu.
* \param option String da opção.
*
* A função aloca uma nova opção e adiciona à lista encadeada de
* opções do menu. Se a string for maior que a atual largura do menu,
* atualiza a largura para que o desenho da caixa fique correto.
* Cada opção faz uma alocação de string e apenas copia o valor
* do parâmetro \a option para a string que foi alocada.
*/
void Menu_AddOption(Menu* m, char* option);

/**
* \brief Desenha um menu em um Display em uma dada coordenada.
* \param m Ponteiro para o menu que será desenhado.
* \param d Ponteiro para o display onde será desenhado.
* \param row Linha onde será desenhado.
* \param col Coluna onde será desenhado.
*
* A função desenha todas as opções do menu no display. Se o
* ponteiro \a d for nulo, a função não faz nada.
*/
void Menu_Draw(Menu* m, Display* d, int row, int col);

/**
* \brief Envia ao menu alguma entrada do usuário para processar.
* \param m Ponteiro para o menu que receberá o input.
* \param key Número que descreve o input.
*
* Caso o input seja seta para cima, o menu seleciona a opção de cima,
* caso o input seja a tecla ENTER, a função indica que o usuário
* escolheu aquela opção etc...
*/
void Menu_Input(Menu* m, int key);

/**
* \brief Obtém a última opção escolhida pelo usuário.
* \param m Ponteiro para o menu.
* \return Índice da opção que foi escolhida pelo usuário (ou -1 quando
*         não há).
*
* A função verifica se alguma das opções foi escolhida pelo usuário
* e retorna essa opção. Uma opção é escolhida quando o menu
* recebe a tecla ENTER pela função Menu_Input. Após retornar
* que uma opção foi escolhida, a mesma opção não estará mais
* escolhida a menos que outro ENTER seja enviado ao menu, ou seja,
* duas chamadas consecutivas à essa função não retornam o mesmo valor,
* pois assim que uma escolha do usuário foi resgatada por essa função,
* esse escolha do usuário é desmarcada.
*/
int Menu_Click(Menu* m);

#endif // _MENU_H
