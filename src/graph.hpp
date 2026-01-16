#include "parser.hpp"
#if ! defined GRAPH_HPP
#define GRAPH_HPP

#include "parser.hpp"
#include "stats.hpp"
#include <map>

class graph : public Stats
{
    public:
        
        //Récupère les données du fichier de log et le convertit en graph
        void interpret(Parser::LogLine const &is);
        
        //Constructeur par défaut
        graph();
        
        //Constructeur de copie
        graph(const graph &unGraph);

    
    protected:
        std::map<std::string, std::map<std::string, int>> mygraph;
        
        
};

#endif