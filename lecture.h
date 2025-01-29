/*************************************************************************
                           lecture  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <lecture> (fichier lecture.h) ----------------
#if ! defined ( lecture_H )
#define lecture_H
#include "log.h"

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <lecture>
//
//
//------------------------------------------------------------------------

class Lecture
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
vector<string> getLogContent() const;

//-------------------------------------------- Constructeurs - destructeur
    explicit Lecture( const string & filename);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Lecture ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<string> output;     
};

//-------------------------------- Autres définitions dépendantes de <lecture>

#endif // lecture_H

