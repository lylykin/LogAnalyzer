/*************************************************************************
                           TopTen  -  Classe de statistiques Top 10
                             -------------------
    début                : 2025
    copyright            : (C) 2025 GNU GPL 3.0
*************************************************************************/    
//---------- Interface de la classe <TopTen> (fichier topten.hpp) --------
#if ! defined ( TOPTEN_HPP )
#define TOPTEN_HPP

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>
#include <vector>

//------------------------------------------------------ Include personnel
#include "stats.hpp"
#include "parser.hpp"

//------------------------------------------------------------------ Types
using dict = std::map<std::string, int>; //dictionnaire contenant kles liens et leur nombre de hits
using pairSi = std::pair<std::string, int>; //une pair (lien, hits)
using tabLinks = std::vector<std::vector<pairSi>>; //tableau contenant les pairs de liens

//------------------------------------------------------------------------
// Rôle de la classe <TopTen>
// Calcule et affiche les 10 pages les plus visitées.
//------------------------------------------------------------------------

class TopTen : public Stats
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void PrintTopTen() const;
    // Mode d'emploi :
    // affiche dans la console le top 10 des liens les plus visités (si findTopTenLinks() a été exécutée)

    void PrintAllLinks() const;
    // Mode d'emploi :
    // affiche tout le dictionnaire contenant les liens

    void Interpret(Parser::LogLine const &) override;
    // Mode d'emploi :
    // interprète la ligne
    // rajoute dans le dictionnaire dAllLinks le lien (la clé) avec 1 comme élément
    // ou incrémente de un son élément s'il est déjà dans le dictionnaire

    std::string FindTopOneLink();
    // Mode d'emploi :
    // renvoie le lien le plus visité du map dAllLinks

    std::vector<std::vector<std::pair<std::string, int>>>& FindTopTenLinks();
    // Mode d'emploi :
    // met les 10 liens les plus visités en ordre dans le vecteur theTopTen
    // il se base sur les liens du dictionnaire dAllLinks
    // Les liens sont triés en ordre croissant d'indice dans le vecteur
    // Le vecteur contenant le top 10 est renvoyé

//-------------------------------------------- Constructeurs - destructeur
    TopTen();
    // Mode d'emploi :
    // constructeur par défaut
    
    virtual ~TopTen();
    // Mode d'emploi :
    // Destructeur par défaut

//------------------------------------------------------------------ PRIVE

private:
//----------------------------------------------------- Attributs privés
    std::map <std::string, int> dAllLinks;
    tabLinks theTopTen;
    //on prend un vecteur de vecteur de pairs de string et int
    // de cette manière on peu avoir le classement exact dans le vecteur
    // (une case de vecteur contient un vecteur qui contient tous les liens qui sont à cette position)
};

#endif // TOPTEN_HPP
