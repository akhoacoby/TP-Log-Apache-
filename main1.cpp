#include "lecture.h"
#include "log.h"
#include "stats.h"
#include "struct.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unistd.h>  // pour getopt
#include <getopt.h>

using namespace std;

int main(int argc, char* argv[]) {
    string fichier_log;
    int exclure_extensions = 0;
    bool generer_dot = false;
    string fichier_dot;
    int heure = -1;
    int opt;

    // Analyse des arguments de la ligne de commande
    while ((opt = getopt(argc, argv, "g:t:e")) != -1) {
        switch (opt) {
            case 'g':
                generer_dot = true;
                fichier_dot = optarg;
                break;
            case 't':
                sscanf(optarg, "%d", &heure);
                break;
            case 'e':
                exclure_extensions = 1;
                break;
            default:
                cerr << "Usage: ./analog [-g fichier.dot] [-e] [-t heure] fichier_log\n";
                return 1;
        }
    }

    // Récupération du fichier log à partir des arguments
    if (optind < argc) {
        fichier_log = argv[optind];
    } else {
        cerr << "Fichier log non spécifié !\n";
        return 1;
    }

    // Initialisation des objets Stats et Lecture
    Stats stats;
    Lecture lecture(fichier_log);
    vector<string> lignes_log = lecture.getLogContent();

    for(string ligne : lignes_log){

      stats.ajouter(Log(ligne));
      //cout<<ligne<<endl;
      }

    // Application des filtres
    if (exclure_extensions==1) {
        stats.filtrerExtensions();
    }

    if (heure != -1) {
        stats.filtrerParHeure(heure);
    }

    //afficher top10 filtre ou non
    stats.afficherTop10();


    // Génération du fichier Graphviz ou affichage des top 10
    if (generer_dot) {
        stats.genererGraphViz(fichier_dot);
    }




    return 0;
}
