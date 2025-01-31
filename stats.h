#ifndef STATS_H
#define STATS_H

#include "struct.h"
#include "log.h"

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

    void ajouter(const Log& nouveau_log);
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
  multimap<string,tuple<Date, string,string>> url_map{};
  vector<pair<string, pair<int, string>>> graph_vec;
};

#endif
