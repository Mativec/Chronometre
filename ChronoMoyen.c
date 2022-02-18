/**
 * @file Chrono.c
 * @author TWARDAWA Yanis & VECCHIO Matias
 * @brief Main du programme pour le TP2 de ProgC
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
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    clear();
    /*start_color(); */
    struct timeval temps_debut, temps_fin;
    int pause, duree_totale, touche;
    
    
    gettimeofday(&temps_debut, NULL);
    duree_totale = 0;
    pause = 1; /* 1 = en pause / 0 = en marche */
    

    while(1) {
        if(touche == ' ') {
            if (pause) {
                gettimeofday(&temps_debut, NULL);
                pause--;
            }   
            else {
                pause++;
            }
        }
        usleep(50000);
        if (!pause) {
            gettimeofday(&temps_fin, NULL);
            duree_totale += intervalle(temps_debut, temps_fin);
            temps_debut.tv_sec = temps_fin.tv_sec;
            temps_debut.tv_usec = temps_fin.tv_usec;
        }
        mvprintw(0, 0, "%2d : %2d : %2d : %2d\n", nb_ms_vers_heures(duree_totale), nb_ms_vers_minutes(duree_totale), nb_ms_vers_secondes(duree_totale), nb_ms_vers_centiemes(duree_totale));
        touche = getch();
    }
    endwin();
    return 0;
}