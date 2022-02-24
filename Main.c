/**
 * @file Main.c
 * @author TWARDAWA Yanis & VECCHIO Matias
 * @brief Programme pour l'exercice 3 du TP3 de Prog C
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
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    chrono = initialiser_chronometre();
    gettimeofday(&temps_debut, NULL);
    chrono.avertissement = 25000;
    

    while(!fin) {

        affiche_interface(chrono);
        
        if(LINES <= 14 || COLS <= 58) {
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

        switch (touche) {
            case 'q' :
                fin = 1;
                break;

            case'r':
                gettimeofday(&temps_debut, NULL);
                chrono.duree_totale = 0;
                chrono.etat = 0;
                break;

            case't':
                ajouter_tour(&chrono);
                break;

            case KEY_F(1):
                chrono.avertissement = chrono.avertissement + 3600000;
                break;

            case KEY_F(2):
                if (nb_ms_vers_heures(chrono.avertissement) > 0) {
                    chrono.avertissement -= 3600000;
                }
                break;

            case KEY_F(3):
                chrono.avertissement  += 60000;
                break;

            case KEY_F(4):
                if (nb_ms_vers_minutes(chrono.avertissement) > 0) {
                    chrono.avertissement  -= 60000;
                }
                break;
        
            case KEY_F(5):
                chrono.avertissement += 1000;
                break;

            case KEY_F(6):
                if (nb_ms_vers_secondes(chrono.avertissement) > 0){
                    chrono.avertissement -= 1000;
                }
                break;
        }


        if ((chrono.avertissement <= chrono.duree_totale) 
            && chrono.avertissement != 0 && chrono.etat){
            chrono.etat--;
            afficher_flash();
            clear();
            chrono.avertissement = 0;
        }

        usleep(50000);
        if (chrono.etat) {
            gettimeofday(&temps_fin, NULL);
            chrono.duree_totale = chrono.duree_totale + intervalle(temps_debut, temps_fin);
            temps_debut.tv_sec = temps_fin.tv_sec;
            temps_debut.tv_usec = temps_fin.tv_usec;
        }
        
        touche = getch();
    }
    endwin();
    return 0;
}