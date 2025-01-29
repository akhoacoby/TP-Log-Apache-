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
  void Stats::Append(const SimpleLog& unSimpleLog)
{
  // Créer un vecteur avec la date/heure et le referer à chaque appel
  vector<string> infos = {"", unSimpleLog.referer};

  // Ajouter la nouvelle entrée dans le vecteur associé à l'URL
  url_map[unSimpleLog.Request.url].push_back(infos);  // Ajouter un nouvel élément sans écraser l'existant
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
    list<pair<string,int>> myTop = Top_10();
    auto it = myTop.begin();
    cout << "Le top 10 des pages les plus visitées est" << endl;
    for(it = myTop.begin(); it != myTop.end(); ++it)
  {
      cout << " " << it->first << "(" << it->second << ")" << endl;
  }
    cout<<endl;
}

//int Stats::nbrOccur(const string& url) //Pour chaque url on sait son nombre d'occurence
//{
  /*int n = 0;
  for (const auto& entry : url_map) // Parcours de toutes les entrées du unordered_map
  {
  int n = 0;

  const vector<string>& referers = entry.second; // Récupère la liste des referers

  for (const string& referer : referers) // Parcours de tous les referers
    {
    n++;
    if (referer == url)
      {
      n++; // Incrémente le compteur si le referer correspond
      }
    }
  cout << n << endl;
  }

    return n;
}
*/
int Stats::nbrOccur(const string& url)
{
  int n = 0;
  for(  auto it = url_map.begin(); it != url_map.end(); ++it)
  {
    if(it->first == url)
    {
          n++;
    }
  }
  return n;
}
//Les sites avec leur nombre d'occurence et leur url
list<pair<string, int>> Stats::Top_10()
{
    int n;
    list<pair<string, int>> top;

    for (const auto& entry : url_map) {
        n = nbrOccur(entry.first);
        top.push_back({entry.first, n});
    }

    // 📌 Tri par ordre décroissant du nombre de visites avec une lambda expression
    top.sort([](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;  // Trie en ordre décroissant
    });

    // 📌 Ne garder que les 10 premiers éléments
    if (top.size() > 10) {
        auto it = next(top.begin(), 10);
        top.erase(it, top.end());
    }

    return top;
}


ostream& operator<<(ostream& os, const Stats& s){
    for (const auto& entry : s.url_map) {
        os << "URL: " << entry.first << "\n";
        for (const auto& info : entry.second) {
            os << "  - " << info << "\n";
        }

        os << "\n";
    }
    return os;
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
