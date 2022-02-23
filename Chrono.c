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
    assert(sizeof(debut) == sizeof(struct timeval));
    assert(sizeof(fin) == sizeof(struct timeval));
    
    return ((fin.tv_sec - debut.tv_sec) * 1000) + ((fin.tv_usec - debut.tv_usec) / 1000);
}


int nb_ms_vers_centiemes(int nb_ms){
    return (nb_ms / 10) % 100;
}


int nb_ms_vers_secondes(int nb_ms){
    return (nb_ms / 1000) % 60;
}


int nb_ms_vers_minutes(int nb_ms){
    return (nb_ms / (1000 * 60)) % 60;
}


int nb_ms_vers_heures(int nb_ms){
    return (nb_ms / (1000 * 60 * 60));
}


void affiche_duree(int y, int x, int nb_ms){

    mvprintw(y, x, "%2d : %2d : %2d : %2d\n", 
    nb_ms_vers_heures(nb_ms), 
    nb_ms_vers_minutes(nb_ms),
    nb_ms_vers_secondes(nb_ms), 
    nb_ms_vers_centiemes(nb_ms));
    mvaddch(y, COLS - 1, '|');
}
 

void affiche_interface(Chronometre chrono){

    int i;
    char * chaine;
    
    clear();
    mvprintw(0, COLS /2, "== Chronometre ==");
    for(i = 0; i < COLS; i++){
        mvprintw(LINES - 9, i, "-");
        mvprintw(0, i, "-");
        mvprintw(LINES - 1, i, "-");
    }
    for(i = 0; i < LINES; i++){
        mvprintw(i, 0, "|");
        mvprintw(i, COLS - 1, "|");
    }

    mvaddch(0, 0, '/');
    mvaddch(LINES - 1, 0, '\\');
    mvaddch(0, COLS - 1, '\\');
    mvaddch(LINES - 1, COLS - 1, '/');

    /*COLS/2 - (strlen(chaine)/2) pour centrer*/
    mvprintw(LINES - 8, 1, "Espace : lancer / mettre en pause");
    mvprintw(LINES - 7, 1, "r      : reinitialiser");
    mvprintw(LINES - 6, 1, "t      : marquer tour");
    mvprintw(LINES - 5, 1, "F1/F2  : incrementer / decrementer heure avertissement");
    mvprintw(LINES - 4, 1, "F3/F4  : incrementer / decrementer minute avertissement");
    mvprintw(LINES - 3, 1, "F5/F6  : incrementer / decrementer seconde avertissement");
    mvprintw(LINES - 2, 1, "q      : quitter");

    affiche_duree(LINES - 12, COLS/2, chrono.duree_totale);
    mvprintw(LINES - 10, COLS /2 - 15, "Avertissement : ");
    affiche_duree(LINES - 10, COLS/2, chrono.avertissement);
}


void afficher_flash(){
    int y, x, i;

    clear();

    for(i = 0; i <10; i++){
        for(y = 0; y < LINES; y++) {
            for(x = 0; x < COLS; x++) {
                mvaddch(y, x, "*");
                attron(COLOR_PAIR(1));
            }
        }
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2));
        attroff(COLOR_PAIR(2));
        refresh();
        usleep(5000);
    }
}


void ajouter_tour(Chronometre *chrono) {
    assert(chrono != NULL);
    
    chrono->nb_tours++;
    chrono->dernier_tour = (chrono->dernier_tour + 1) % 6;
    chrono->tours[chrono->dernier_tour] = chrono->duree_totale;
}