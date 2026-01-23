#if ! defined GRAPH_HPP
#define GRAPH_HPP

#include "parser.hpp"
#include "stats.hpp"
#include <map>
#include <string>

class Graph : public Stats
{
    public:
        
        //Récupère les données du fichier de log et le convertit en fichier GraphViz
        void interpret(Parser::LogLine const &is);
        
        //Génére le fichier GraphViz
        void graphiz(const std::string &);
        
        //Constructeur par défaut
        Graph();
        
        //Constructeur de copie
        Graph(const Graph &unGraph);

    
    protected:
        std::map<std::string, std::map<std::string, int>> mygraph;
        
};

#endif