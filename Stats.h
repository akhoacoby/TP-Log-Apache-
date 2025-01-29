/*************************************************************************
                           Stats  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Xxx> (fichier Xxx.h) ----------------
#if ! defined STATS_H
#define STATS_H
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <utility>
#include <string>
#include "simplelog.h"
using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Xxx>
//
//
//------------------------------------------------------------------------
class Stats
{
//----------------------------------------------------------------- PUBLIC
  friend class SimpleLog;
  friend class lecture;
  friend ostream& operator<<(ostream& os, const Stats& s);
public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
void Append(const SimpleLog& unLog);

void Execute_without_options();//on doit afficher sur la console sous forme textuelle la liste des 10 documents les plus consultés par ordre décroissant de popularité

int nbrOccur(const string& url);

//void Execute_with_option_e(string file) const;//Exclure tous les documents qui ont une extension de type image(png, jpg?), css ou javascript genre on appelle la fonction sans option mais sans les images

//void Execute_with_option_g(string file) const;//-g nomfichier.dot produire un fichier au format GraphViz du graphe analysé

//void Execute_with_option_t(int hour) const;//-t heure cette option permet de prendre en compte que les hits qui sont dans le créneau horaire [heure, heure+1[

list<pair<string,int>> Top_10();//mettre dans une liste les  10 documents les plus visités par ordre décroissant de popularité




//------------------------------------------------- Surcharge d'opérateurs
    //Stats & operator + ( const Stats & unStats );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Stats(const Stats & unStats);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Stats( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Stats( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    unordered_map <string, vector<string>> url_map;//vector de string on aura tout le temps la date/heure et le url cible.

};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // XXX_H
