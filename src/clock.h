#ifndef _CLOCK_H
#define _CLOCK_H

/**
* \file clock.h
* \brief Gerenciador de tempo
*
* Esse módulo disponibiliza duas funções que possuem
* implementação diferente para Windows/Linux. Uma função
* para fazer o programa esperar em estado ocioso por um certo
* período, isso para evitar 100% de uso do CPU no loop principal.
* Também disponibiliza uma função para medir intervalos de tempo.
*/

/**
* \brief Paralisa o programa por um tempo.
* \param mili Tempo em ms que o programa irá ficar ocioso.
*
* A função diz para o sistema operacional ignorar o
* programa por um período de tempo. Como o programa funciona
* baseado em um loop infinito, o consumo do cpu é de 100%, já
* que o programa não para nunca. Botando o programa para dormir
* e atualizando ele apenas entre pequenos intervalos de tempo ajuda
* a reduzir a quantidade de cálculos feitos.
*/
void Clock_Sleep(unsigned mili);

/**
* \brief Mede o tempo
* \param last Ponteiro para outro número que foi obtido
*        por essa mesma função. Também pode ser NULO.
* \return Número que indica quantos milisegundos se passaram
*         desde uma data no passado (geralmente janeiro de 1970).
*
* A função retorna um número que indica quantos milisegundos
* se passaram desde uma data fixa (geralmente janeiro de 1970). Quando o
* ponteiro \a last é diferente de NULO, a função calcula a diferença de tempo
* entre os dois números e retorna essa diferença convertida para segundos.
*/
unsigned long long Clock_GetTime(unsigned long long* last);

#endif // _CLOCK_H
