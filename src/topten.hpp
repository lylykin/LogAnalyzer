#if ! defined(TOPTEN_H)
#define TOPTEN_H

//imports
#include <string>
#include <map>
#include <vector>

//import personnel
#include "stats.hpp"
#include "parser.hpp"

class TopTen : public Stats
{
    public:
        //méthodes publiques
        void interpret(Parser::LogLine const &);
        //interprète la ligne
        // rajoute dans le dictionnaire dAllLinks le lien (la clé) avec 1 comme élément
        // ou incrémente de un son élément s'il est déjà dans le dictionnaire

        std::string findTopOneLink();
        //renvoie le lien le plus visité du map dAllLinks

        std::vector<std::string>& findTopTenLinks();
        //met les 10 liens les plus visités en ordre dans le vecteur theTopTen
        // il se base sur les liens du dictionnaire dAllLinks
        // Les liens sont triés en ordre croissant d'indice dans le vecteur

        TopTen() : Stats() {}
        //constructeur par défaut

        ~TopTen(){}
        //Destructeur par défaut

    private:
        std::map <std::string, int> dAllLinks;
        std::vector <std::vector<std::string>> theTopTen;
};

#endif
