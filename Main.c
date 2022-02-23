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
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    clear();
    start_color();
    
    fin = 0;
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_RED);
    chrono = initialiser_chronometre();
    gettimeofday(&temps_debut, NULL);
    chrono.avertissement = 25000;
    

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
                gettimeofday(&temps_debut, NULL);
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

        if (touche == KEY_F(1)){
            chrono.avertissement = chrono.avertissement + 3600000;
        }

        if (touche == KEY_F(2)
            && nb_ms_vers_heures(chrono.avertissement) > 0){
            chrono.avertissement -= 3600000;
        }

        if (touche == KEY_F(3)){
            chrono.avertissement  += 60000; 
        }

        if (touche == KEY_F(4)
            && nb_ms_vers_minutes(chrono.avertissement) > 0){
            chrono.avertissement  -= 60000;
        }
        
        if (touche == KEY_F(5)){
            chrono.avertissement += 1000;
        }

        if (touche == KEY_F(6)
            && nb_ms_vers_secondes(chrono.avertissement) > 0){
            chrono.avertissement -= 1000;
        }
        
        if ((chrono.avertissement <= chrono.duree_totale) 
            && chrono.duree_totale != 0){
            afficher_flash();
        }

        usleep(50000);
        if (chrono.etat) {
            gettimeofday(&temps_fin, NULL);
            chrono.duree_totale = chrono.duree_totale + intervalle(temps_debut, temps_fin);
            temps_debut.tv_sec = temps_fin.tv_sec;
            temps_debut.tv_usec = temps_fin.tv_usec;
        }
        affiche_interface(chrono);
        touche = getch();
    }
    endwin();
    return 0;
}