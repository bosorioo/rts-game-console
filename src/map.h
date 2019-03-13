#ifndef _MAP_H
#define _MAP_H

/**
* \file map.h
* \brief Cria��o e manipula��o de mapas.
*
* Esse m�dulo introduz a estrutura Map, que cont�m posi��es
* e as unidades nessas posi��es. Permite fazer c�lculos como
* se � poss�vel mover-se em tal lugar, por onde deve-se ir
* para alcan�ar tal posi��o, obter unidade em tal posi��o etc.
* Qualquer fun��o n�o far� nada se o ponteiro para o mapa
* passado como par�metro for nulo, e as fun��es assumem que
* se esse ponteiro n�o for nulo, o mesmo ser� um ponteiro
* para uma estrutura Map v�lida.
*/

struct Map;
typedef struct Map Map;
typedef struct
{
    unsigned width, height;/**< Tamanho do mapa. */
    unsigned money, food; /**< Recursos iniciais dos jogadores. */
} MapProperties;

#include "unit.h"
#include "position.h"

/**
* \brief Cria um novo mapa.
* \param props Propriedades do mapa.
* \return Ponteiro para o mapa criado.
*
* Essa fun��o aloca recursos para criar um mapa e inicializa
* o mapa com as propriedades \a props, ou seja, com o tamanho
* dado e os recursos inciais para os jogadores fornecidos.
* Caso a aloca��o falhe, o retorno ser� NULO.
*/
Map* Map_NewMap(MapProperties props);

/**
* \brief Obt�m as dimens�es do mapa.
* \param m Ponteiro para o mapa.
* \param out_width Vari�vel que receber� o valor da largura.
* \param out_height Vari�vel que receber� o valor da altura.
*
* A fun��o obt�m as dimens�es do mapa e escreve esses valores
* nas vari�veis externas \a out_width e \a out_height. Caso
* algum desses ponteiros seja nulo, a fun��o simplesmente
* ignora a escritura de tal valor.
*/
void Map_GetSize(Map* m, int* out_width, int* out_height);

/**
* \brief Valida uma posi��o no mapa.
* \param m Ponteiro para o mapa.
* \param p Posi��o que ser� validada.
* \return Booleano que indica se a posi��o � v�lida ou n�o.
*
* A fun��o pega as coordenadas da posi��o \a p e verifica se
* essa posi��o existe dentro do mapa, ou seja, est� contida dentro
* dos limites do mapa. As coordenadas devem estar contidas no
* intervalo [0, largura/altura) para que a fun��o retorne 1.
*/
int Map_OutOfBounds(Map* m, Position p);

/**
* \brief Deleta o mapa.
* \param m Ponteiro para o mapa.
*
* A fun��o libera todos os recursos utilizados pelo mapa.
* Note que a fun��o n�o deleta as unidades dentro do mapa,
* j� que n�o foi esse m�dulo respons�vel pela aloca��o
* de tais estruturas.
*/
void Map_Delete(Map* m);

/**
* \brief Adiciona a unidade no mapa.
* \param m Ponteiro para o mapa.
* \param u Ponteiro para a unidade.
*
* A fun��o adiciona a unidade \a u no mapa. A posi��o
* no mapa onde a unidade vai estar ser� a posi��o atual
* da unidade, obtida com Unit_GetPosition. Caso o ponteiro
* \a u seja nulo, a fun��o n�o faz nada.
*/
void Map_AddUnit(Map* m, Unit* u);

/**
* \brief Retira uma unidade do mapa.
* \param m Ponteiro para o mapa.
* \param p Posi��o onde a unidade ser� removida.
*
* Essa fun��o procura uma unidade na posi��o \a p
* e retira ela do mapa. Isso n�o significa que a unidade
* morreu ou foi deletada. Apenas significa que ela n�o est�
* mais no mapa. Caso a posi��o seja inv�lida, nada acontece.
* Se n�o houver unidades em tal posi��o, nada acontece tamb�m.
*/
void Map_RemoveUnit(Map* m, Position p);

/**
* \brief Obt�m a unidade em uma posi��o.
* \param m Ponteiro para o mapa.
* \param p Posi��o onde ser� procurado.
* \return Ponteiro para a unidade que se encontra na tal posi��o.
*
* A fun��o pega do mapa a unidade que se encontra na posi��o
* \a p. Caso a posi��o seja inv�lida ou nenhuma unidade estiver
* naquela posi��o, o valor de retorno ser� nulo.
*/
Unit* Map_GetUnit(Map* m, Position p);

/**
* \brief Verifica se � poss�vel caminhar em tal posi��o.
* \param m Ponteiro para o mapa.
* \param p Posi��o verificada.
* \return Booleano que indica se � poss�vel que uma unidade mova-se para tal posi��o.
*
* A fun��o sempre retorna 0 caso a posi��o seja inv�lida. A �nica coisa que
* essa fun��o faz � verificar se h� alguma unidade em tal posi��o. Caso
* a posi��o j� tenha alguma unidade, � imposs�vel se mover para l�.
*/
int  Map_CanWalk(Map* m, Position p);

/**
* \brief Movimenta uma unidade dentro do mapa.
* \param m Ponteiro para o mapa.
* \param u Ponteiro para a unidade.
* \param d Dire��o para onde a unidade ir� se mover.
*
* A fun��o n�o faz nada caso o ponteiro \a u seja nulo.
* Essa fun��o remove a unidade da posi��o anterior e adiciona
* a mesma unidade na posi��o localizada � dire��o \a d.
* A fun��o n�o faz nada se for imposs�vel se locomover na
* nova posi��o.
*/
void Map_MoveUnit(Map* m, Unit* u, enum Direction d);

/**
* \brief Obt�m o inimigo mais pr�ximo.
* \param m Ponteiro para o mapa.
* \param u Ponteiro para a unidade.
* \param max_range M�xima dist�ncia de procura.
* \return Ponteiro para a unidade encontrada.
*
* Essa fun��o retorna NULO caso o ponteiro \a u seja nulo.
* A fun��o busca no mapa todos os inimigos da unidade \a u
* que est�o dentro do alcance \a max_range, e o inimigo mais
* pr�ximo ser� retornado. Caso nenhuma unidade seja encontrada,
* a fun��o retorna NULO.
*/
Unit* Map_GetClosestEnemy(Map* m, Unit* u, int max_range);

/**
* \brief Diz para qual dire��o deve-se ir para chegar a um destino.
* \param m Ponteiro para o mapa.
* \param start Posi��o de sa�da.
* \param goal Posi��o de destino.
* \return Dire��o indica para onde deve-se andar.
*
* A fun��o procura uma possiv�l dire��o que diz por onde
* deve-se ir para alcan�ar a posi��o de destino. A fun��o
* verifica por obst�culos. N�o foi implementadao nenhum
* algoritmo de pathfinding que retorna o resultado exato
* ou �timo, foi implementado apenas uma r�pida tomada de decis�o
* que n�o analisa obst�culos como um todo.
*/
enum Direction Map_GetDirectionTo(Map* m, Position start, Position goal);

/**
* \brief Obt�m as propriedades de um mapa padr�o.
* \return Propriedades do mapa padr�o.
*
* Essa fun��o apenas retorna a estrutura de propriedades
* com os seguintes valores para os campos:
*  comida inicial = 10
*  dinheiro inicial = 20
*  largura = 40
*  altura = 15
*/
MapProperties Map_DefaultMap();

/**
* \brief Obt�m a posi��o livre (sem obst�culos) mais pr�xima.
* \param m Ponteiro para o mapa.
* \param pos Vari�vel externa que receber� o valor.
* \return Booleano que indica se encontrou ou n�o uma posi��o.
*
* A fun��o simplesmente procura em todas as dire��es
* em volta de uma posi��o por outra posi��o que n�o tenha
* obst�culos. Caso o ponteiro \a pos seja nulo, a fun��o
* n�o escreve a posi��o encontrada na vari�vel. Caso
* n�o seja encontrado nenhuma posi��o livre, a vari�vel
* \a pos n�o � modificada e o valor de retorno � 0.
*/
int Map_GetClosestFreePosition(Map* m, Position* pos);

#endif // _MAP_H
