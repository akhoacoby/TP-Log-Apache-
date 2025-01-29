#include "Lecture.h"
#include <iostream>
#include <getopt.h>
using namespace std; 

int main(int argc, char* argv[]) {
    string fichier_log;
    bool exclure_extensions = false;
    bool generer_dot = false;
    string fichier_dot;
    int heure = -1,

    int opt;
    while ((opt = getopt(argc, argv, "g:et:")) != -1) {
        switch (opt) {
            case 'g':
                generer_dot = true;
                fichier_dot = optarg;
                break;
            case 'e':
                exclure_extensions = true;
                break;
            case 't':
                sscanf(optarg, "%d", &heure);
                break;
            default:
                cerr << "Usage: ./analog [-g fichier.dot] [-e] [-t heure] fichier_log\n";
                return 1;
        }
    }

    if (optind < argc) {
        fichier_log = argv[optind];
    } else {
        cerr << "Fichier log non spécifié !\n";
        return 1;
    }

    Stats stats;
    Lecture lecture;
    lecture.lireFichier(fichier_log, stats);

    if (exclure_extensions) {
        stats.filtrerExtensions();
    }

    if (heure_debut != -1 && heure_fin != -1) {
        stats.filtrerParHeure(heure_debut, heure_fin);
    }

    if (generer_dot) {
        stats.genererGraphViz(fichier_dot);
    } else {
        stats.afficherTop10();
    }

    return 0;
}
