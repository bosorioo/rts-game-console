#ifndef _PLAYER_H
#define _PLAYER_H

/**
* \file player.h
*
* Esse módulo define a estrutura Player que guarda informações
* sobre um jogador. Todas as funções cujo primeiro parâmetro é
* um ponteiro para Player funcionam da seguinte forma: se o ponteiro
* for nulo, a função não faz nada, e caso contrário é assumido que
* o ponteiro aponta para uma estrutura Player válida.
*/

struct Player;
typedef struct Player Player;

#include "unit.h"

/**
* \brief Estrutura de um jogador
*/
struct Player
{
    unsigned money, food; /**< Recursos que o jogador possui. */
    float money_income, food_income; /**< Recursos sendo produzidos */
    unsigned unit_count; /**< Contador de quantas unidades o jogador posusi. */
    int camera_row, camera_col; /**< Posição da câmera do jogador */
    Unit* headquarter; /**< Quartel general (unidade principal) do jogador */
    Unit* selected_unit; /**< Unidade que o jogador está selecionando */
};

/**
* \brief Aloca memória para um novo jogador e inicializa ele.
* \param initial_money Dinheiro inicial do jogador.
* \param initial_food Comida inicial do jogador.
* \return Ponteiro para a estrutura alocada.
*
* Caso a alocação falhe, o retorno será um ponteiro NULO.
*/
Player* Player_NewPlayer(unsigned initial_money, unsigned initial_food);

/**
* \brief Libera os recursos utilizados de um Player.
* \param p Ponteiro para o jogador que será desalocado.
*
* A função apenas libera os recursos de um jogador, sem
* liberar os recursos de outras estruturas alocadas que
* o jogador faz referência, por exemplo, uma unidade
* que está sendo selecionada pelo jogador não será
* deletada.
*/
void Player_DeletePlayer(Player* p);

/**
* \brief Verifica se o jogador possui a quantidade de dinheiro e comida.
* \param p Ponteiro para o jogador que será verificado.
* \param money Quantidade de dinheiro que será checada.
* \param food Quantidade de comida que será checada.
* \return Booleano que indica se o player possui os recursos ou não.
*
* A função retorna 0 caso o ponteiro \a p seja nulo. A função
* irá retornar 1 se o jogador possui pelo menos \a money de dinheiro
* e \a food de comida, e 0 caso contrário.
*/
int Player_HasResources(Player* p, int money, int food);

/**
* \brief Adiciona recursos ao jogador.
* \param p Ponteiro para o jogador.
* \param money Quantidade de dinheiro que será adicionada.
* \param food Quantidade de comida que será adicionada.
*
* A função não faz nada caso o ponteiro \a p seja nulo. A função
* assume que caso o ponteiro não seja nulo, o mesmo seja um
* ponteiro que aponta para um estrutura Player válida. O player
* irá ganhar \a money de dinheiro e \a food de comida.
*/
void Player_AddResources(Player* p, int money, int food);

/**
* \brief Define a unidade principal do jogador.
* \param p Ponteiro para o jogador.
* \param u Ponteiro para a unidade.
*
* A função não faz nada caso o ponteiro \a p seja nulo.
* A unidade principal do jogoador é definida para \a u,
* que também pode ser NULO.
*/
void Player_SetHeadquarter(Player* p, Unit* u);

/**
* \brief Obtém o ponteiro para a unidade principal do jogador.
* \param p Ponteiro para o jogador.
*
* A função retorna a unidade principal do jogador. Caso
* o ponteiro \a p seja nulo, a função também retorna nulo.
*/
Unit* Player_GetHeadquarter(Player* p);

/**
* \brief Obtém os recursos disponíveis para o jogador.
* \param p Ponteiro para o jogador.
* \param money Ponteiro para a variável que irá guardar quanto
*        dinheiro o jogador possui.
* \param food Ponteiro para a variável que irá guardar quanta
*        comida o jogador possui.
*
* Caso o ponteiro \a p seja nulo, a função não altera as
* variáveis \a money e \a food. Caso algum dos outros parâmetros
* seja nulo, a informação não é escrita em nenhuma variável.
*/
void Player_GetResources(Player* p, int* money, int* food);

/**
* \brief Obtém as coordenadas da câmera do jogador.
* \param p Ponteiro para o jogador.
* \param row Ponteiro para a variável que irá receber a linha.
* \param col Ponteiro para a variável que irá receber a coluna.
*
* A função não faz nada caso o ponteiro \a p seja nulo.
*/
void Player_GetCamera(Player* p, int* row, int* col);

/**
* \brief Obtém o contador de unidades do jogador.
* \param p Ponteiro para o jogador.
* \return Quantidade de unidades que o jogador possui.
*
* A função retorna 0 caso o ponteiro \a p seja nulo.
*/
int Player_GetUnitCount(Player* p);

/**
* \brief Obtém a quantidade de recursos que o jogador está recebendo.
* \param p Ponteiro para o jogador.
* \param money Ponteiro para a variável que receberá o income de dinheiro.
* \param food Ponteiro para a variável que receberá o income de comida.
*
* A função não faz nada caso o ponteiro \a p seja nulo. Caso algum dos
* outros ponteiros seja nulo, a função simplesmente ignora aquele income.
*/
void Player_GetIncome(Player* p, float* money, float* food);

/**
* \brief Modifica o contador de unidades do jogador.
* \param p Ponteiro para o jogador.
* \param count Número de unidades que o jogador deve receber/perder (positivo/negativo).
*
* A função não faz nada caso o ponteiro para o jogador seja nulo.
*/
void Player_AddUnit(Player* p, int count);

/**
* \brief Modifica o contador de income do jogador.
* \param money Quanto o income de dinheiro irá mudar.
* \param food Quanto o income de comida irá mudar.
*
* A função não faz nada caso o ponteiro para o jogador seja nulo.
*/
void Player_AddIncome(Player* p, float money, float food);

/**
* \brief Modifica a unidade que o jogador está selecionando.
* \param p Ponteiro para o jogador.
* \param u Ponteiro para a unidade que irá ser selecionada.
*
* Caso o ponteiro \a p seja nulo, a função não faz nada.
* Caso o ponteiro \a u seja nulo, o jogador deixa de selecionar
* qualquer unidade.
*/
void Player_SelectUnit(Player* p, Unit* u);

/**
* \brief Obtém a unidade que o jogador está selecionando no momento.
* \param p Ponteiro para o jogador.
* \return Ponteiro para a unidade que o jogador está selecionando.
*
* Caso o jogador não esteja selecionando nenhuma unidade, ou o ponteiro
* \a p for nulo, a função retorna nulo.
*/
Unit* Player_GetSelectedUnit(Player* p);

/**
* \brief Faz o jogador pagar uma certa quantidade.
* \param p Ponteiro para o jogador.
* \param money Quanto dinheiro o jogador vai pagar.
* \param food Quanta comida o jogador vai pagar.
* \return Booleano indicando se o jogador pôde pagar ou não.
*
* A função não faz nada caso o ponteiro \a p seja nulo, retornando 0.
* Se o jogador tiver recursos para pagar os valores, ele
* perde esses recursos e a função retorna 1. Caso contrário,
* o jogador não perde nada, mas a função retorna 0.
*/
int Player_Pay(Player* p, int money, int food);
#endif // _PLAYER_H
