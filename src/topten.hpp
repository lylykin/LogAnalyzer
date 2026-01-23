#if ! defined(TOPTEN_H)
#define TOPTEN_H

//imports
#include <string>
#include <map>
#include <vector>

//import personnel
#include "stats.hpp"
#include "parser.hpp"

using dict = std::map<std::string, int>; //dictionnaire contenant kles liens et leur nombre de hits
using pairSi = std::pair<std::string, int>; //une pair (lien, hits)
using tabLinks = std::vector<std::vector<pairSi>>; //tableau contenant les pairs de liens

class TopTen : public Stats
{
    public:
        //méthodes publiques
        void printTopTen() const;
        //affiche dans la console le top 10 des liens les plus visités (si findTopTenLinks() a été exécutée)

        void printAllLinks() const;
        //affiche tout le dictionnaire contenant les liens

        void interpret(Parser::LogLine const &);
        //interprète la ligne
        // rajoute dans le dictionnaire dAllLinks le lien (la clé) avec 1 comme élément
        // ou incrémente de un son élément s'il est déjà dans le dictionnaire

        std::string findTopOneLink();
        //renvoie le lien le plus visité du map dAllLinks

        std::vector<std::vector<std::pair<std::string, int>>>& findTopTenLinks();
        //met les 10 liens les plus visités en ordre dans le vecteur theTopTen
        // il se base sur les liens du dictionnaire dAllLinks
        // Les liens sont triés en ordre croissant d'indice dans le vecteur
        // Le vecteur contenant le top 10 est renvoyé

        TopTen();
        //constructeur par défaut

        ~TopTen(){}
        //Destructeur par défaut

    private:
        std::map <std::string, int> dAllLinks;
        tabLinks theTopTen;
        //on prend un vecteur de vecteur de pairs de string et int
        // de cette manière on peu avoir le classement exact dans le vecteur
        // (une case de vecteur contient un vecteur qui contient tous les liens qui sont à cette position)
};

#endif
