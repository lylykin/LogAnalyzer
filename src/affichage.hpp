/*************************************************************************
                           Affichage  -  Gestion des arguments
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Équipe LogAnalyzer
    e-mail               : equipe@loganalyzer.fr
*************************************************************************/

//---------- Interface du module <Affichage> (fichier affichage.hpp) -----
#if ! defined ( AFFICHAGE_HPP )
#define AFFICHAGE_HPP

//--------------------------------------------------- Interfaces utilisées
#include <optional>
#include <string>

//------------------------------------------------------------------ Types
typedef struct ProgArgument
{
    std::optional<int> time_selection;
    bool gen_graph = false; // -g [graph_outfile]
    std::string graph_outfile;

    bool exclude_document = false; // -e
    bool has_dump = false; // -d

    std::string log_path; // LogAnalyzer [paramètres] [log_path]
                          // fichier log à analyser
} ProgArgument;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Fonctions publiques
ProgArgument ParseParameter(int argc, const char ** argv);
// Mode d'emploi :
// Analyse les arguments CLI et popule la structure ProgArgument.

bool IsOption(const char *arg);
// Mode d'emploi :
// Vérifie si la chaine est une option (-x).

void OptionInterpreter(ProgArgument &);
// Mode d'emploi :
// Exécute la logique métier en fonction des arguments (TopTen vs Graph).

//std::fstream open_file(const char * filename);
//récupère le contenu du fichier

#endif // AFFICHAGE_HPP
