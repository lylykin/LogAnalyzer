#include "graph.hpp"

using graphe = std::map<std::string, std::map<std::string, int>>;
using dict = std::map<std::string, int>;

Graph::Graph()
{
    mygraph = {};
}

void Graph::interpret(Parser::LogLine const &is)
{
    std::string target(is.target);
    std::string source(is.source);
    graphe::iterator it = mygraph.find(source);
    if (it == mygraph.end())                    //Cas où le noeud source n'existe pas
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
        else        //Cas où le noeud source et le noeud cible existent.
        {
            it2->second++;
        }
    }
}

void Graph::graphiz(std::string const &outfile)
{
    std::ofstream fic(outfile);
    fic<<"digraph {"<<std::endl;
    for (auto& pair : mygraph)          //Parcours des noeuds sources
    {
        for (auto& pair2 : pair.second)          //Parcours des noeuds cibles
        {
            fic<<"\""<<pair.first<<"\"" <<" -> \""<<pair2.first<<"\"[label=\""<<pair2.second<<"\"];"<<std::endl;
        }
    }
    fic<<"}"<<std::endl; 

}
