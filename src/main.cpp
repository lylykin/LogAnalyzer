/*************************************************************************
                           Main  -  Point d'entrée principal
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Équipe LogAnalyzer
    e-mail               : equipe@loganalyzer.fr
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "affichage.hpp"

//---------------------------------------------------------------- Main
int main(int argc, const char ** argv)
{
    if(argc < 2)
    {
        std::cerr << "Usage: LogAnalyzer [options] <logfile>" << std::endl;
        return 1;
    }
    else if (std::string(argv[1]) == "help")
    {
        std::cout << "manuel d'utilisation" << std::endl
        << "-----------" << std::endl
        << "./LogAnalyzer [options] <nomfichier.log>" << std::endl
        << "options : " << std::endl
        << "-g <nomfichier.dot>         Produire un fichier au format GraphViz." << std::endl
        << "-e                          Exclure les fichiers de type css, javascript, ou image" << std::endl
        << "-t <heure>                  Ne prendre en compte que les hits dans l'intervalle de temps [heure, heure + 1[" << std::endl
        << "no options                  Afficher le top 10 des ressources avec le plus de hits" << std::endl;
    }
    else 
    {
        // Utilisation des nouvelles fonctions PascalCase
        ProgArgument args = ParseParameter(argc, argv);
        OptionInterpreter(args);
    }

    return 0;
}
