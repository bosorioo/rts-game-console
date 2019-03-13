#ifndef _POSITION_H
#define _POSITION_H

/**
* \file position.h
* \brief Encapsulamento de coordenadas
*
* Esse módulo define a estrutura Position, que é apenas
* um par de inteiros que definem uma certa posição, podendo
* ser coordenadas de uma unidade no mapa, de algo no terminal etc.
*/

/**
* \brief Estrutura que ajuda a manipular coordenadas.
*/
typedef struct
{
    int x, y; /**< Coordenadas */
} Position;

/**
* \brief Direções possíveis que uma unidade pode andar.
*/
enum Direction
{
    None, North, East, South, West
};

/**
* \brief Retorna uma posição (SEM alocar memória) cujas coodenadas são iniciadas.
* \param x Coordenada X da posição a ser retornada
* \param y Coordenada Y da posição a ser retornada
* \return Estrutura da posição que tem suas coordenadas iniciadas para (x, y)
*/
Position Position_NewPosition(int x, int y);

/**
* \brief Retorna uma posição relativa à outra a partir de uma direção
* \param p posição base
* \param d direção
* \return Estrutura da posição nova
*
* A função retorna uma posição imediatamente próxima àquela
* passada como parâmetro. A posição retornada pode ser a posição
* logo acima caso a direção seja Norte, logo abaixo caso seja
* Sul etc.
*/
Position Position_Moved(Position p, enum Direction d);

/**
* \brief Verifica se a distância entre duas posições está dentro de
*        um dado alcance.
* \param a uma posição
* \param b outra posição
* \param range alcance máximo
* \return 1 caso a distância entre as duas posições é menor que "range" e
*         0 caso contrário.
*/
int Position_IsInRange(Position a, Position b, int range);

/**
* \brief Verifica se duas posições são iguais.
* \param a uma posição para comparar
* \param b outra posição para comparar
* \return 1 caso as coordenadas x e y de ambas posições forem iguais e
*         0 caso contrário.
*/
int Position_Equals(Position a, Position b);

#endif
