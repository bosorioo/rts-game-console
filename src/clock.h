#ifndef _CLOCK_H
#define _CLOCK_H

/**
* \file clock.h
* \brief Gerenciador de tempo
*
* Esse m�dulo disponibiliza duas fun��es que possuem
* implementa��o diferente para Windows/Linux. Uma fun��o
* para fazer o programa esperar em estado ocioso por um certo
* per�odo, isso para evitar 100% de uso do CPU no loop principal.
* Tamb�m disponibiliza uma fun��o para medir intervalos de tempo.
*/

/**
* \brief Paralisa o programa por um tempo.
* \param mili Tempo em ms que o programa ir� ficar ocioso.
*
* A fun��o diz para o sistema operacional ignorar o
* programa por um per�odo de tempo. Como o programa funciona
* baseado em um loop infinito, o consumo do cpu � de 100%, j�
* que o programa n�o para nunca. Botando o programa para dormir
* e atualizando ele apenas entre pequenos intervalos de tempo ajuda
* a reduzir a quantidade de c�lculos feitos.
*/
void Clock_Sleep(unsigned mili);

/**
* \brief Mede o tempo
* \param last Ponteiro para outro n�mero que foi obtido
*        por essa mesma fun��o. Tamb�m pode ser NULO.
* \return N�mero que indica quantos milisegundos se passaram
*         desde uma data no passado (geralmente janeiro de 1970).
*
* A fun��o retorna um n�mero que indica quantos milisegundos
* se passaram desde uma data fixa (geralmente janeiro de 1970). Quando o
* ponteiro \a last � diferente de NULO, a fun��o calcula a diferen�a de tempo
* entre os dois n�meros e retorna essa diferen�a convertida para segundos.
*/
unsigned long long Clock_GetTime(unsigned long long* last);

#endif // _CLOCK_H
