/*************************************************************************
                           Stats  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Stats>> (fichier Stats>.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <vector>
//------------------------------------------------------ Include personnel
#include "Stats.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
Stats::Append(log::log unLog )
{
    //Algorithms of Malak
}

/*void Stats::Execute_with_option_e()
{
  
}

void Stats::Execute_with_option_t(int hour)
{

}

void Stats::Execute_with_option_g(string file)
{

}
*/
void Stats::Execute_without_options()
{
    myTop = Top_10();
    auto it = myTop.begin();
    for(it = myTop.begin(); it != myTop.end(); ++it)
{
    cout << " " << it->first;
} 
    cout<<endl;    
}

int Stats::nbrOccur(const string& url) //Pour chaque url on sait son nombre d'occurence
{ 
    int n = 0;

    for (const auto& entry : url_map) // Parcours de toutes les entrées du unordered_map
{ 
        const vector<string>& referers = entry.second; // Récupère la liste des referers

        for (const string& referer : referers) // Parcours de tous les referers
{
            if (referer == url) 
{
                n++; // Incrémente le compteur si le referer correspond
}
}
}

    return n;
}

//Les sites avec leur nombre d'occurence et leur url
list<pair<string,int>> Stats::Top_10()
{
    int n;
    list<pair<string, int> top;
    iterator it = url_map.begin();
   for (const auto& entry : url_map)
{
    n = nbrOccur(entry->first);
    top.push_back({entry.first, n});
}
    // 📌 Tri par ordre décroissant du nombre de visites
    top.sort(compareOccurrences);

    // 📌 Ne garder que les 10 premiers éléments
    if (top.size() > 10) 
{
        auto it = next(top.begin(), 10);
        top.erase(it, top.end());
}
    return top;
}

//Tri par ordre décroissant du nombre d'occurence
bool Stats::compareOccurrences(const pair<string, int>& a, const pair<string, int>& b) 
{
    return a.second > b.second; // Trie en ordre décroissant
}

//-------------------------------------------- Constructeurs - destructeur
Stats::Stats ( const Stats & unStats )
// Algorithme :
//
{
    this->url_map = unStats.url_map;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Stats>" << endl;
#endif
} //----- Fin de Xxx (constructeur de copie)


Stats::Stats( ) 
// Algorithme :
//
{
    url_map<"", vector<"">;
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Stats>>" << endl;
#endif
} //----- Fin de Xxx


Stats::~Stats ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Stats>" << endl;
#endif
} //----- Fin de ~Stats


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

