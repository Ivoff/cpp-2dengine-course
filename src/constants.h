#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

/* Quantidade maxima de frames gerados pelo jogo */
const unsigned int MAX_FPS = 15;

/* Valor do tempo minimo que um fps deve levar para ser renderizado na tela 
 * 1000 e a quantidade de milisegundos em um segundo, dividido por MAX_FPS
 * da o tempo medio que cada fps tem que ter para o jogo ficar travado a 
 * 120 fps*/
const unsigned int MIN_FPS_TIME = 1000 / MAX_FPS;

#endif
