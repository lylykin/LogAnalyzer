#include "graph.hpp"

using arrete = std::map<std::string, std::map<std::string,int>>;

graph::graph()
{
    mygraph={};
}

graph::interpret(Parser::LogLine const &is)
{
    std::string target(is.get.target);
    arrete::iterator it=mygraph.find(target)
}