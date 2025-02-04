#ifndef STATS_H
#define STATS_H

#include "struct.h"
#include "log.h"
#include "simplelog.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;


class Stats {
public:
    Stats();
    // Constructeur par défaut

    void ajouter(const SimpleLog& nouveau_log);
    // Ajouter un log

    void afficherTop10() const;
    // Afficher le top 10 des pages consultées

    void genererGraphViz(const string& fichier_dot) ;
    // Générer un fichier GraphViz

    void filtrerExtensions() ;
    //Filtrer par extension

    void filtrerParHeure(int heure);
    //Filtrer par heure

private:
  //map dont les cles sont des urls et les valeurs sont la date, le url de reference
  //et l'extension du premier url respectivement.
  multimap<string,tuple<Date, string,string>> url_map;

};

#endif
