/**
 * @file Chrono.c
 * @author TWARDAWA Yanis & VECCHIO Matias
 * @brief Programme pour l'exercice 1 du TP3 de ProgC
 * @version 0.1
 * @date 2022-02-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <ncurses.h>


/**
 * @brief fonction qui renvoie le tmeps entre deux temps donné en 
 * paramètre, en milliseconde
 * 
 * @param debut le temps en microseconde
 * @param fin le temps en microseconde
 * @return int 
 */
int intervalle(struct timeval debut, struct timeval fin){
    return ((fin.tv_sec - debut.tv_sec) * 1000) + ((fin.tv_usec - debut.tv_usec) / 1000);
}


/**
 * @brief Fonction qui renvoie nb_ms en centiemes de secondes.
 * 
 * @param nb_ms: nombre de millisecondes. 
 * @return int: nombre de millisecondes convertis en centieme de secondes.
 */
int nb_ms_vers_centiemes(int nb_ms) {
    return (nb_ms / 10) % 100;
}


/**
 * @brief Fonction qui renvoie nb_ms en secondes.
 * 
 * @param nb_ms: nombre de millisecondes.
 * @return int: nombre de millisecondes convertis en secondes.
 */
int nb_ms_vers_secondes(int nb_ms){
    return (nb_ms / 1000) % 60;
}


/**
 * @brief Fonction qui renvoie nb_ms en secondes.
 * 
 * @param nb_ms: nombre de millisecondes.
 * @return int: nombre de millisecondes convertis en minutes.
 */
int nb_ms_vers_minutes(int nb_ms) {
    return (nb_ms / (1000 * 60)) % 60;
}


/**
 * @brief Fonction qui renvoie nb_ms en secondes.
 * 
 * @param nb_ms: nombre de millisecondes.
 * @return int: nombre de millisecondes convertis en heures.
 */
int nb_ms_vers_heures(int nb_ms) {
    return (nb_ms / (1000 * 60 * 60));
}


int main(void) {
    
    /* Variables de recuperation du temps. */
    struct timeval debut_prog, actuel;

    /* Variables pour recueillir les mesures. */
    int chrono;

    /* Mesure de temps initiale. */
    gettimeofday(&debut_prog, NULL);
    chrono = 0;


    while(1) {
        gettimeofday(&actuel, NULL);
        chrono = intervalle(debut_prog, actuel);
        printf("%2d : %2d : %2d : %2d\n", nb_ms_vers_heures(chrono), nb_ms_vers_minutes(chrono), nb_ms_vers_secondes(chrono), nb_ms_vers_centiemes(chrono));
        usleep(500000);
    }
    return 0;
}