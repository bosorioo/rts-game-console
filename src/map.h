#ifndef _MAP_H
#define _MAP_H

/**
* \file map.h
* \brief Criação e manipulação de mapas.
*
* Esse módulo introduz a estrutura Map, que contém posições
* e as unidades nessas posições. Permite fazer cálculos como
* se é possível mover-se em tal lugar, por onde deve-se ir
* para alcançar tal posição, obter unidade em tal posição etc.
* Qualquer função não fará nada se o ponteiro para o mapa
* passado como parâmetro for nulo, e as funções assumem que
* se esse ponteiro não for nulo, o mesmo será um ponteiro
* para uma estrutura Map válida.
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
* Essa função aloca recursos para criar um mapa e inicializa
* o mapa com as propriedades \a props, ou seja, com o tamanho
* dado e os recursos inciais para os jogadores fornecidos.
* Caso a alocação falhe, o retorno será NULO.
*/
Map* Map_NewMap(MapProperties props);

/**
* \brief Obtém as dimensões do mapa.
* \param m Ponteiro para o mapa.
* \param out_width Variável que receberá o valor da largura.
* \param out_height Variável que receberá o valor da altura.
*
* A função obtém as dimensões do mapa e escreve esses valores
* nas variáveis externas \a out_width e \a out_height. Caso
* algum desses ponteiros seja nulo, a função simplesmente
* ignora a escritura de tal valor.
*/
void Map_GetSize(Map* m, int* out_width, int* out_height);

/**
* \brief Valida uma posição no mapa.
* \param m Ponteiro para o mapa.
* \param p Posição que será validada.
* \return Booleano que indica se a posição é válida ou não.
*
* A função pega as coordenadas da posição \a p e verifica se
* essa posição existe dentro do mapa, ou seja, está contida dentro
* dos limites do mapa. As coordenadas devem estar contidas no
* intervalo [0, largura/altura) para que a função retorne 1.
*/
int Map_OutOfBounds(Map* m, Position p);

/**
* \brief Deleta o mapa.
* \param m Ponteiro para o mapa.
*
* A função libera todos os recursos utilizados pelo mapa.
* Note que a função não deleta as unidades dentro do mapa,
* já que não foi esse módulo responsável pela alocação
* de tais estruturas.
*/
void Map_Delete(Map* m);

/**
* \brief Adiciona a unidade no mapa.
* \param m Ponteiro para o mapa.
* \param u Ponteiro para a unidade.
*
* A função adiciona a unidade \a u no mapa. A posição
* no mapa onde a unidade vai estar será a posição atual
* da unidade, obtida com Unit_GetPosition. Caso o ponteiro
* \a u seja nulo, a função não faz nada.
*/
void Map_AddUnit(Map* m, Unit* u);

/**
* \brief Retira uma unidade do mapa.
* \param m Ponteiro para o mapa.
* \param p Posição onde a unidade será removida.
*
* Essa função procura uma unidade na posição \a p
* e retira ela do mapa. Isso não significa que a unidade
* morreu ou foi deletada. Apenas significa que ela não está
* mais no mapa. Caso a posição seja inválida, nada acontece.
* Se não houver unidades em tal posição, nada acontece também.
*/
void Map_RemoveUnit(Map* m, Position p);

/**
* \brief Obtém a unidade em uma posição.
* \param m Ponteiro para o mapa.
* \param p Posição onde será procurado.
* \return Ponteiro para a unidade que se encontra na tal posição.
*
* A função pega do mapa a unidade que se encontra na posição
* \a p. Caso a posição seja inválida ou nenhuma unidade estiver
* naquela posição, o valor de retorno será nulo.
*/
Unit* Map_GetUnit(Map* m, Position p);

/**
* \brief Verifica se é possível caminhar em tal posição.
* \param m Ponteiro para o mapa.
* \param p Posição verificada.
* \return Booleano que indica se é possível que uma unidade mova-se para tal posição.
*
* A função sempre retorna 0 caso a posição seja inválida. A única coisa que
* essa função faz é verificar se há alguma unidade em tal posição. Caso
* a posição já tenha alguma unidade, é impossível se mover para lá.
*/
int  Map_CanWalk(Map* m, Position p);

/**
* \brief Movimenta uma unidade dentro do mapa.
* \param m Ponteiro para o mapa.
* \param u Ponteiro para a unidade.
* \param d Direção para onde a unidade irá se mover.
*
* A função não faz nada caso o ponteiro \a u seja nulo.
* Essa função remove a unidade da posição anterior e adiciona
* a mesma unidade na posição localizada à direção \a d.
* A função não faz nada se for impossível se locomover na
* nova posição.
*/
void Map_MoveUnit(Map* m, Unit* u, enum Direction d);

/**
* \brief Obtém o inimigo mais próximo.
* \param m Ponteiro para o mapa.
* \param u Ponteiro para a unidade.
* \param max_range Máxima distância de procura.
* \return Ponteiro para a unidade encontrada.
*
* Essa função retorna NULO caso o ponteiro \a u seja nulo.
* A função busca no mapa todos os inimigos da unidade \a u
* que estão dentro do alcance \a max_range, e o inimigo mais
* próximo será retornado. Caso nenhuma unidade seja encontrada,
* a função retorna NULO.
*/
Unit* Map_GetClosestEnemy(Map* m, Unit* u, int max_range);

/**
* \brief Diz para qual direção deve-se ir para chegar a um destino.
* \param m Ponteiro para o mapa.
* \param start Posição de saída.
* \param goal Posição de destino.
* \return Direção indica para onde deve-se andar.
*
* A função procura uma possivél direção que diz por onde
* deve-se ir para alcançar a posição de destino. A função
* verifica por obstáculos. Não foi implementadao nenhum
* algoritmo de pathfinding que retorna o resultado exato
* ou ótimo, foi implementado apenas uma rápida tomada de decisão
* que não analisa obstáculos como um todo.
*/
enum Direction Map_GetDirectionTo(Map* m, Position start, Position goal);

/**
* \brief Obtém as propriedades de um mapa padrão.
* \return Propriedades do mapa padrão.
*
* Essa função apenas retorna a estrutura de propriedades
* com os seguintes valores para os campos:
*  comida inicial = 10
*  dinheiro inicial = 20
*  largura = 40
*  altura = 15
*/
MapProperties Map_DefaultMap();

/**
* \brief Obtém a posição livre (sem obstáculos) mais próxima.
* \param m Ponteiro para o mapa.
* \param pos Variável externa que receberá o valor.
* \return Booleano que indica se encontrou ou não uma posição.
*
* A função simplesmente procura em todas as direções
* em volta de uma posição por outra posição que não tenha
* obstáculos. Caso o ponteiro \a pos seja nulo, a função
* não escreve a posição encontrada na variável. Caso
* não seja encontrado nenhuma posição livre, a variável
* \a pos não é modificada e o valor de retorno é 0.
*/
int Map_GetClosestFreePosition(Map* m, Position* pos);

#endif // _MAP_H
