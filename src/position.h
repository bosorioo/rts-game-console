#ifndef _POSITION_H
#define _POSITION_H

/**
* \file position.h
* \brief Encapsulamento de coordenadas
*
* Esse m�dulo define a estrutura Position, que � apenas
* um par de inteiros que definem uma certa posi��o, podendo
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
* \brief Dire��es poss�veis que uma unidade pode andar.
*/
enum Direction
{
    None, North, East, South, West
};

/**
* \brief Retorna uma posi��o (SEM alocar mem�ria) cujas coodenadas s�o iniciadas.
* \param x Coordenada X da posi��o a ser retornada
* \param y Coordenada Y da posi��o a ser retornada
* \return Estrutura da posi��o que tem suas coordenadas iniciadas para (x, y)
*/
Position Position_NewPosition(int x, int y);

/**
* \brief Retorna uma posi��o relativa � outra a partir de uma dire��o
* \param p posi��o base
* \param d dire��o
* \return Estrutura da posi��o nova
*
* A fun��o retorna uma posi��o imediatamente pr�xima �quela
* passada como par�metro. A posi��o retornada pode ser a posi��o
* logo acima caso a dire��o seja Norte, logo abaixo caso seja
* Sul etc.
*/
Position Position_Moved(Position p, enum Direction d);

/**
* \brief Verifica se a dist�ncia entre duas posi��es est� dentro de
*        um dado alcance.
* \param a uma posi��o
* \param b outra posi��o
* \param range alcance m�ximo
* \return 1 caso a dist�ncia entre as duas posi��es � menor que "range" e
*         0 caso contr�rio.
*/
int Position_IsInRange(Position a, Position b, int range);

/**
* \brief Verifica se duas posi��es s�o iguais.
* \param a uma posi��o para comparar
* \param b outra posi��o para comparar
* \return 1 caso as coordenadas x e y de ambas posi��es forem iguais e
*         0 caso contr�rio.
*/
int Position_Equals(Position a, Position b);

#endif
