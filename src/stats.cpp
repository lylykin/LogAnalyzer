/*************************************************************************
                           Stats  -  Classe de base pour l'analyse
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Équipe LogAnalyzer
    e-mail               : equipe@loganalyzer.fr
*************************************************************************/

//---------- Réalisation de la classe <Stats> (fichier stats.cpp) --------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <ctime>

//------------------------------------------------------ Include personnel
#include "stats.hpp"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Stats::Interpret(Parser::LogLine const & l)
{
    std::cout << " IP: " << (int)l.ip[0] << "." << (int)l.ip[1] << "." << (int)l.ip[2] << "."
              << (int)l.ip[3] << std::endl;
    std::cout << " Time: " << std::asctime(&l.time);
    std::cout << " Request: " << l.request << std::endl;
    if (l.request == "GET")
    {
        std::cout << "  Source: " << l.source << std::endl;
        std::cout << "  Target: " << l.target << std::endl;
    }
}

bool Stats::InterpretFile(std::string const &path, bool exclude_documents, std::optional<int> time_selection)
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
        std::optional<Parser::LogLine> line = parser.GetLine();
        if (line.has_value())
        {
            Interpret(line.value());
        }
    }
    return true;
}

//-------------------------------------------- Constructeurs - destructeur
Stats::Stats()
{
#ifdef MAP
    std::cout << "Appel au constructeur de <Stats>" << std::endl;
#endif
}

Stats::~Stats()
{
#ifdef MAP
    std::cout << "Appel au destructeur de <Stats>" << std::endl;
#endif
}
