/**
 * @file ChronoDur.c
 * @author TWARDAWA Yanis & VECCHIO Matias
 * @brief Code du Module ChronoDur
 * @version 0.1
 * @date 2022-02-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Chrono.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <ncurses.h>


Chronometre initialiser_chronometre(){
    Chronometre * tmp = (Chronometre *) malloc(sizeof(Chronometre));
    if (tmp != NULL) {
        tmp -> etat = 0;
        tmp -> duree_totale = 0;
        tmp -> avertissement = 0;
        tmp -> dernier_tour = 0;
        tmp -> nb_tours = 0;
    }
    return *tmp;
}


int intervalle(struct timeval debut, struct timeval fin){
    return ((fin.tv_sec - debut.tv_sec) * 1000) + ((fin.tv_usec - debut.tv_usec) / 1000);
}


int nb_ms_vers_centiemes(int nb_ms) {
    return (nb_ms / 10) % 100;
}


int nb_ms_vers_secondes(int nb_ms){
    return (nb_ms / 1000) % 60;
}


int nb_ms_vers_minutes(int nb_ms) {
    return (nb_ms / (1000 * 60)) % 60;
}


int nb_ms_vers_heures(int nb_ms) {
    return (nb_ms / (1000 * 60 * 60));
}


void affiche_duree(int y, int x, int nb_ms){
    mvprintw(y, x, "%2d : %2d : %2d : %2d\n", 
    nb_ms_vers_heures(nb_ms), 
    nb_ms_vers_minutes(nb_ms),
    nb_ms_vers_secondes(nb_ms), 
    nb_ms_vers_centiemes(nb_ms));
}
 

void affiche_interface(Chronometre chrono){
    int i;
    char * chaine;
    
    clear();
    mvprintw(0, COLS /2, "== Chronometre ==");
    for(i = 0; i < LINES; i++){
        mvprintw(COLS /2, i, "-");
    }
        /*COLS/2 - (strlen(chaine)/2) pour centrer*/
        chaine = "Espace : lancer / mettre en pause";
        mvprintw(LINES - 7, 0, chaine); /*mettre des constantes pour plus tard*/
        chaine = "r      : reinitialiser";
        mvprintw(LINES - 6, 0, chaine);
        chaine = "t      : marquer tour";
        mvprintw(LINES - 5, 0, chaine);
        chaine = "F1/F2  : incrementer / decrementer heure avertissement";
        mvprintw(LINES - 4, 0, chaine);
        chaine = "F3/F4  : incrementer / decrementer minute avertissement";   
        mvprintw(LINES - 3, 0, chaine);
        chaine = "F5/F6  : incrementer / decrementer seconde avertissement";
        mvprintw(LINES - 2, 0, chaine);
        chaine = "q      : quitter";   
        mvprintw(LINES - 1, 0, chaine);

}


void afficher_flash(){
    int y, x;

    clear();
    for(y = 0; y < LINES; y++) {
        for(x = 0; x < COLS; x++) {
                mvaddch(y, x, "*");
                /* attron(COLOR_PAIR(1)); */
                /* attroff(COLOR_PAIR(1)); */
            }
        }
    refresh();
}
