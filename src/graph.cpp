/*************************************************************************
                           Graph  -  Génération de graphes (GraphViz)
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Équipe LogAnalyzer
    e-mail               : equipe@loganalyzer.fr
*************************************************************************/

//---------- Réalisation de la classe <Graph> (fichier graph.cpp) --------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
#include <iostream>

//------------------------------------------------------ Include personnel
#include "graph.hpp"

//------------------------------------------------------------------ Types
using graphe = std::map<std::string, std::map<std::string, int>>;
using dict = std::map<std::string, int>;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Graph::Interpret(Parser::LogLine const &is)
{
    std::string target(is.target);
    std::string source(is.source);
    graphe::iterator it = mygraph.find(source);
    if (it == mygraph.end()) //Cas où le noeud source n'existe pas
    {
        std::map<std::string, int> target_map;
        target_map[target] = 1;
        mygraph.insert(std::pair<std::string, std::map<std::string, int>>(source, target_map));
    }
    else
    {
        dict::iterator it2 = it->second.find(target);
        if (it2 == it->second.end()) //Cas où le noeud source existe mais pas le noeud cible
        {
            it->second.insert(std::pair<std::string, int>(target, 1));
        }
        else //Cas où le noeud source et le noeud cible existent.
        {
            it2->second++;
        }
    }
}

void Graph::Graphiz(std::string const &outfile)
{
    std::ofstream fic(outfile);
    fic << "digraph {" << std::endl;
    for (auto& pair : mygraph) //Parcours des noeuds sources
    {
        for (auto& pair2 : pair.second) //Parcours des noeuds cibles
        {
            fic << "\"" << pair.first << "\"" << " -> \"" << pair2.first << "\"[label=\"" << pair2.second << "\"];" << std::endl;
        }
    }
    fic << "}" << std::endl; 
}

//-------------------------------------------- Constructeurs - destructeur
Graph::Graph() : Stats()
{
#ifdef MAP
    std::cout << "Appel au constructeur de <Graph>" << std::endl;
#endif
    mygraph = {};
}

Graph::Graph(const Graph &unGraph) : Stats(unGraph), mygraph(unGraph.mygraph)
{
#ifdef MAP
    std::cout << "Appel au constructeur de copie de <Graph>" << std::endl;
#endif
}

Graph::~Graph()
{
#ifdef MAP
    std::cout << "Appel au destructeur de <Graph>" << std::endl;
#endif
}
