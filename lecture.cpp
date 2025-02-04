/*************************************************************************
                           lecture  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <lecture> (fichier lecture.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


//------------------------------------------------------ Include personnel
#include "lecture.h"
#include "log.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

vector<string> Lecture::getLogContent() const {
    return output ; // Retourner le contenu complet du fichier
}
// Algorithme :
//
// type lecture::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
//-------------------------------------------- Constructeurs - destructeur

Lecture::Lecture(const string & filename)
{
    ifstream apache_log(filename);
    vector<string> logLines;

    if (!apache_log.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        output = logLines;
        return;
    }

    string lineContent;
    while (getline(apache_log, lineContent))
    {
    logLines.push_back(lineContent);
    }

    apache_log.close();
    output = logLines;
}


Lecture::~Lecture()
// Algorithme :
//
{
    output.clear();
#ifdef MAP
    cout << "Appel au destructeur de <lecture>" << endl;
#endif
} //----- Fin de ~lecture


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//   Lecture test("test.txt");
