/*************************************************************************
                           Stats  -  Classe de base pour l'analyse
                             -------------------
    début                : 2025
    copyright            : (C) 2025 GNU GPL 3.0
*************************************************************************/

//---------- Interface de la classe <Stats> (fichier stats.hpp) ----------
#if ! defined ( STATS_H )
#define STATS_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <optional>

//------------------------------------------------------ Include personnel
#include "parser.hpp"

//------------------------------------------------------------------------
// Rôle de la classe <Stats>
// Classe de base abstraite (ou concrète utilisable) pour l'analyse
// de fichiers de logs. Définit le protocole d'interprétation.
//------------------------------------------------------------------------

class Stats
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Interpret(Parser::LogLine const & line);
    // Mode d'emploi :
    // Méthode virtuelle appelée pour chaque ligne de log parsée.
    // L'implémentation par défaut affiche le contenu de la ligne.

    // line doit être une structure valide.

    bool InterpretFile(std::string const &path, bool exclude_documents, std::optional<int> time_selection);
    // Mode d'emploi :
    // Ouvre le fichier et lance l'interprétation ligne par ligne
    // Contrat : 
    // Le chemin doit être accessible en lecture

//-------------------------------------------- Constructeurs - destructeur
    Stats();
    // Mode d'emploi :
    // constructeurs
    
    virtual ~Stats();
    // Mode d'emploi :
    // destructeurs
};

#endif // STATS_H
