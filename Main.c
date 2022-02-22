/**
 * @file Main.c
 * @author TWARDAWA Yanis & VECCHIO Matias
 * @brief 
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "Chrono.h"

int main(void) {
    int touche, fin;
    struct timeval temps_debut;
    struct timeval temps_fin;
    Chronometre chrono;
    
    
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    clear();
    /*start_color(); */
    
    fin = 0;
    chrono = initialiser_chronometre();
    gettimeofday(&temps_debut, NULL);
    

    while(!fin) {

        if(LINES < 14 || COLS < 58) {
            system("echo Fenetre trop petite...");
            fin++;
        }

        if(touche == ' ') {
            if(chrono.etat) {
                gettimeofday(&temps_debut, NULL);
                chrono.etat = 0;
            }   
            else {
                chrono.etat = 1;
            }
        }
        if (touche == 'q') {
            fin = 1;
        }

        if (touche == 'r') {
            gettimeofday(&temps_debut, NULL);
            chrono.duree_totale = 0;
            chrono.etat = 0;
        }
        usleep(50000);
        if (chrono.etat) {
            gettimeofday(&temps_fin, NULL);
            chrono.duree_totale = chrono.duree_totale + intervalle(temps_debut, temps_fin);
            temps_debut.tv_sec = temps_fin.tv_sec;
            temps_debut.tv_usec = temps_fin.tv_usec;
        }
        affiche_interface(chrono);
        affiche_duree(LINES/3, COLS/2, chrono.duree_totale);
        touche = getch();
    }
    endwin();
    return 0;
}