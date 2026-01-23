#ifndef STATS_H
#define STATS_H

#include <fstream>
#include <iostream>
#include <optional>
#include "parser.hpp"

class Stats
{
public:
    virtual void interpret(Parser::LogLine const & _)
    {
        std::cout << " IP: " << (int)_.ip[0] << "." << (int)_.ip[1] << "." << (int)_.ip[2] << "."
                  << (int)_.ip[3] << std::endl;
        std::cout << " Time: " << std::asctime(&_.time);
        std::cout << " Request: " << _.request << std::endl;
        if (_.request == "GET")
        {
            std::cout << "  Source: " << _.source << std::endl;
            std::cout << "  Target: " << _.target << std::endl;
        }
    }

    // constructeurs/destructeurs   - - - - - - - - - - - - - - - - - -
    Stats(){};
    virtual ~Stats() {};

    bool interpret_file(std::string const &path, bool exclude_documents, std::optional<int> time_selection)
    {
        std::ifstream file(path);
        if (!file)
        {
            std::cerr << "Erreur d'ouverture du fichier : " << path << std::endl;
            return false;
        }

        Parser parser(file, exclude_documents, time_selection);
        while (file)
        {
            std::optional<Parser::LogLine> line = parser.getLine();
            if (line.has_value())
            {
                interpret(line.value());
            }
        }
        return true;
    }
};

#endif
