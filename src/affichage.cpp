/*************************************************************************
                           Affichage  -  Gestion des arguments
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Équipe LogAnalyzer
    e-mail               : equipe@loganalyzer.fr
*************************************************************************/

//---------- Réalisation du module <Affichage> (fichier affichage.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstdlib>
#include <string>

//------------------------------------------------------ Include personnel
#include "affichage.hpp"
#include "topten.hpp"
#include "graph.hpp"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Fonctions publiques
ProgArgument ParseParameter(int argc, const char **argv)
{
    // prendre les options
    //  tant que pas arrivés au dernier (avec argc)
    //  case switch en fonction des options

    ProgArgument args;

    int params = 1;
    while (params < argc)
    {
        if (IsOption(argv[params]))
        {
            if (argv[params][1] == 'e')
            {
                args.exclude_document = true;
            }
            else if (argv[params][1] == 'g')
            {
                args.gen_graph = true;
                if (params + 1 < argc)
                {
                    args.graph_outfile = argv[params+1];
                    //args.graph_outfile.assign(argv[params + 1], strlen(argv[params + 1]));
                    params++;
                }
            }
            else if (argv[params][1] == 't')
            {
                if (params + 1 < argc)
                {
                    args.time_selection = std::atoi(argv[params + 1]);
                    //args.time_selection.assign(argv[params + 1], strlen(argv[params + 1]));
                    params++;
                }
            }
        }
        else // comme ce n'est pas une option et que les paramètres des options sont gérés dans l'autre cas, c'est forcément le fichier source de logs
        {    // si params = 1 => cas par défaut
            args.log_path = argv[params];
            // pathLogs.assign(argv[params], strlen(argv[params]));
        }
        params++;
    }

    return args;
}

bool IsOption(const char *arg) { return (arg[0] == '-'); }

void OptionInterpreter(ProgArgument &optn)
{
    if (!(optn.gen_graph) && !(optn.has_dump))
    {
        // cas par défaut : topten
        TopTen top;
        // Appel aux nouvelles méthodes en PascalCase
        top.InterpretFile(optn.log_path, optn.exclude_document, optn.time_selection);
        top.FindTopTenLinks();
        top.PrintTopTen();
    }
    else
    {
        Graph graph;
        graph.InterpretFile(optn.log_path, optn.exclude_document, optn.time_selection);
        graph.Graphiz(optn.graph_outfile);
    }
}
