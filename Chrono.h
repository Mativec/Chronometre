/**
 * @file Chrono.h
 * @author TWARDAWA Yanis & VECCHIO Matias
 * @brief Headers du module Chrono
 * @version 0.1
 * @date 2022-02-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CHRONO__
#define __CHRONO__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <ncurses.h>
#include <assert.h>


typedef struct chrono {
    int etat; /*1 ou 0 */
    int duree_totale; /*En millisecondes */
    int avertissement;
    int dernier_tour;
    int nb_tours;
    int tours[6];
} Chronometre;

/**
 * @brief Initialise un chronometre et le renvoie.
 * 
 * @return Chronometre: chronometre initialisé ou NULL.
 */
Chronometre initialiser_chronometre();


/**
 * @brief fonction qui renvoie le tmeps entre deux temps donné en 
 * paramètre, en milliseconde
 * 
 * @param debut le temps en microseconde
 * @param fin le temps en microseconde
 * @return int 
 */
int intervalle(struct timeval debut, struct timeval fin);


/**
 * @brief affiche la durée d'un chronometre donnée
 * avec le module ncurses  
 * 
 * @param y 
 * @param x 
 * @param nb_ms 
 */
void affiche_duree(int y, int x, int nb_ms);



/**
 * @brief Fonction qui renvoie nb_ms en centiemes de secondes.
 * 
 * @param nb_ms: nombre de millisecondes. 
 * @return int: nombre de millisecondes convertis en centieme de secondes.
 */
int nb_ms_vers_centiemes(int nb_ms);


/**
 * @brief Fonction qui renvoie nb_ms en secondes.
 * 
 * @param nb_ms: nombre de millisecondes.
 * @return int: nombre de millisecondes convertis en secondes.
 */
int nb_ms_vers_secondes(int nb_ms);


/**
 * @brief Fonction qui renvoie nb_ms en secondes.
 * 
 * @param nb_ms: nombre de millisecondes.
 * @return int: nombre de millisecondes convertis en minutes.
 */
int nb_ms_vers_minutes(int nb_ms);


/**
 * @brief Fonction qui renvoie nb_ms en secondes.
 * 
 * @param nb_ms: nombre de millisecondes.
 * @return int: nombre de millisecondes convertis en heures.
 */
int nb_ms_vers_heures(int nb_ms);


/**
 * @brief Affiche le chronometre dans le terminal.
 * 
 * @param chrono 
 */
void affiche_interface(Chronometre chrono);

/**
 * @brief affiche un "flash" dans le chrono
 * 
 */
void afficher_flash();


/**
 * @brief Enregistre le chrono actuel dans un tour.
 * 
 * @param chrono 
 */
void ajouter_tour(Chronometre *chrono);

#endif