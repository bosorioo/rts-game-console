#ifndef _PLAYER_H
#define _PLAYER_H

/**
* \file player.h
*
* Esse m�dulo define a estrutura Player que guarda informa��es
* sobre um jogador. Todas as fun��es cujo primeiro par�metro �
* um ponteiro para Player funcionam da seguinte forma: se o ponteiro
* for nulo, a fun��o n�o faz nada, e caso contr�rio � assumido que
* o ponteiro aponta para uma estrutura Player v�lida.
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
    int camera_row, camera_col; /**< Posi��o da c�mera do jogador */
    Unit* headquarter; /**< Quartel general (unidade principal) do jogador */
    Unit* selected_unit; /**< Unidade que o jogador est� selecionando */
};

/**
* \brief Aloca mem�ria para um novo jogador e inicializa ele.
* \param initial_money Dinheiro inicial do jogador.
* \param initial_food Comida inicial do jogador.
* \return Ponteiro para a estrutura alocada.
*
* Caso a aloca��o falhe, o retorno ser� um ponteiro NULO.
*/
Player* Player_NewPlayer(unsigned initial_money, unsigned initial_food);

/**
* \brief Libera os recursos utilizados de um Player.
* \param p Ponteiro para o jogador que ser� desalocado.
*
* A fun��o apenas libera os recursos de um jogador, sem
* liberar os recursos de outras estruturas alocadas que
* o jogador faz refer�ncia, por exemplo, uma unidade
* que est� sendo selecionada pelo jogador n�o ser�
* deletada.
*/
void Player_DeletePlayer(Player* p);

/**
* \brief Verifica se o jogador possui a quantidade de dinheiro e comida.
* \param p Ponteiro para o jogador que ser� verificado.
* \param money Quantidade de dinheiro que ser� checada.
* \param food Quantidade de comida que ser� checada.
* \return Booleano que indica se o player possui os recursos ou n�o.
*
* A fun��o retorna 0 caso o ponteiro \a p seja nulo. A fun��o
* ir� retornar 1 se o jogador possui pelo menos \a money de dinheiro
* e \a food de comida, e 0 caso contr�rio.
*/
int Player_HasResources(Player* p, int money, int food);

/**
* \brief Adiciona recursos ao jogador.
* \param p Ponteiro para o jogador.
* \param money Quantidade de dinheiro que ser� adicionada.
* \param food Quantidade de comida que ser� adicionada.
*
* A fun��o n�o faz nada caso o ponteiro \a p seja nulo. A fun��o
* assume que caso o ponteiro n�o seja nulo, o mesmo seja um
* ponteiro que aponta para um estrutura Player v�lida. O player
* ir� ganhar \a money de dinheiro e \a food de comida.
*/
void Player_AddResources(Player* p, int money, int food);

/**
* \brief Define a unidade principal do jogador.
* \param p Ponteiro para o jogador.
* \param u Ponteiro para a unidade.
*
* A fun��o n�o faz nada caso o ponteiro \a p seja nulo.
* A unidade principal do jogoador � definida para \a u,
* que tamb�m pode ser NULO.
*/
void Player_SetHeadquarter(Player* p, Unit* u);

/**
* \brief Obt�m o ponteiro para a unidade principal do jogador.
* \param p Ponteiro para o jogador.
*
* A fun��o retorna a unidade principal do jogador. Caso
* o ponteiro \a p seja nulo, a fun��o tamb�m retorna nulo.
*/
Unit* Player_GetHeadquarter(Player* p);

/**
* \brief Obt�m os recursos dispon�veis para o jogador.
* \param p Ponteiro para o jogador.
* \param money Ponteiro para a vari�vel que ir� guardar quanto
*        dinheiro o jogador possui.
* \param food Ponteiro para a vari�vel que ir� guardar quanta
*        comida o jogador possui.
*
* Caso o ponteiro \a p seja nulo, a fun��o n�o altera as
* vari�veis \a money e \a food. Caso algum dos outros par�metros
* seja nulo, a informa��o n�o � escrita em nenhuma vari�vel.
*/
void Player_GetResources(Player* p, int* money, int* food);

/**
* \brief Obt�m as coordenadas da c�mera do jogador.
* \param p Ponteiro para o jogador.
* \param row Ponteiro para a vari�vel que ir� receber a linha.
* \param col Ponteiro para a vari�vel que ir� receber a coluna.
*
* A fun��o n�o faz nada caso o ponteiro \a p seja nulo.
*/
void Player_GetCamera(Player* p, int* row, int* col);

/**
* \brief Obt�m o contador de unidades do jogador.
* \param p Ponteiro para o jogador.
* \return Quantidade de unidades que o jogador possui.
*
* A fun��o retorna 0 caso o ponteiro \a p seja nulo.
*/
int Player_GetUnitCount(Player* p);

/**
* \brief Obt�m a quantidade de recursos que o jogador est� recebendo.
* \param p Ponteiro para o jogador.
* \param money Ponteiro para a vari�vel que receber� o income de dinheiro.
* \param food Ponteiro para a vari�vel que receber� o income de comida.
*
* A fun��o n�o faz nada caso o ponteiro \a p seja nulo. Caso algum dos
* outros ponteiros seja nulo, a fun��o simplesmente ignora aquele income.
*/
void Player_GetIncome(Player* p, float* money, float* food);

/**
* \brief Modifica o contador de unidades do jogador.
* \param p Ponteiro para o jogador.
* \param count N�mero de unidades que o jogador deve receber/perder (positivo/negativo).
*
* A fun��o n�o faz nada caso o ponteiro para o jogador seja nulo.
*/
void Player_AddUnit(Player* p, int count);

/**
* \brief Modifica o contador de income do jogador.
* \param money Quanto o income de dinheiro ir� mudar.
* \param food Quanto o income de comida ir� mudar.
*
* A fun��o n�o faz nada caso o ponteiro para o jogador seja nulo.
*/
void Player_AddIncome(Player* p, float money, float food);

/**
* \brief Modifica a unidade que o jogador est� selecionando.
* \param p Ponteiro para o jogador.
* \param u Ponteiro para a unidade que ir� ser selecionada.
*
* Caso o ponteiro \a p seja nulo, a fun��o n�o faz nada.
* Caso o ponteiro \a u seja nulo, o jogador deixa de selecionar
* qualquer unidade.
*/
void Player_SelectUnit(Player* p, Unit* u);

/**
* \brief Obt�m a unidade que o jogador est� selecionando no momento.
* \param p Ponteiro para o jogador.
* \return Ponteiro para a unidade que o jogador est� selecionando.
*
* Caso o jogador n�o esteja selecionando nenhuma unidade, ou o ponteiro
* \a p for nulo, a fun��o retorna nulo.
*/
Unit* Player_GetSelectedUnit(Player* p);

/**
* \brief Faz o jogador pagar uma certa quantidade.
* \param p Ponteiro para o jogador.
* \param money Quanto dinheiro o jogador vai pagar.
* \param food Quanta comida o jogador vai pagar.
* \return Booleano indicando se o jogador p�de pagar ou n�o.
*
* A fun��o n�o faz nada caso o ponteiro \a p seja nulo, retornando 0.
* Se o jogador tiver recursos para pagar os valores, ele
* perde esses recursos e a fun��o retorna 1. Caso contr�rio,
* o jogador n�o perde nada, mas a fun��o retorna 0.
*/
int Player_Pay(Player* p, int money, int food);
#endif // _PLAYER_H
