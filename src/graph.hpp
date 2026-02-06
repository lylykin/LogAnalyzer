/*************************************************************************
                           Graph  -  Génération de graphes (GraphViz)
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Équipe LogAnalyzer
    e-mail               : equipe@loganalyzer.fr
*************************************************************************/

//---------- Interface de la classe <Graph> (fichier graph.hpp) ----------
#if ! defined ( GRAPH_HPP )
#define GRAPH_HPP

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <string>

//------------------------------------------------------ Include personnel
#include "parser.hpp"
#include "stats.hpp"

//------------------------------------------------------------------------
// Rôle de la classe <Graph>
// Modélise les transitions entre pages (Source -> Cible) et
// génère un fichier exportable pour GraphViz (.dot).
//------------------------------------------------------------------------

class Graph : public Stats
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Interpret(Parser::LogLine const &is) override;
    // Mode d'emploi :
    // Récupère les données du fichier de log et le convertit en fichier GraphViz
    
    void Graphiz(const std::string &);
    // Mode d'emploi :
    // Génére le fichier GraphViz

//-------------------------------------------- Constructeurs - destructeur
    Graph();
    // Mode d'emploi :
    // Constructeur par défaut
    
    Graph(const Graph &unGraph);
    // Mode d'emploi :
    // Constructeur de copie
    
    virtual ~Graph();
    // Mode d'emploi :
    // Destructeur

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    std::map<std::string, std::map<std::string, int>> mygraph;
};

#endif // GRAPH_HPP