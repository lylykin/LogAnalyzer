#include "affichage.hpp"
#include <iostream>

void parse_parameter(int argc, const char** argv)
{
    // cas possible :
    //  si argc = 1 : erreur, géré par user_choice
    switch (argc)
    {
    case 0:
        std::cerr << "Aucun fichier sélectionné";
    case 1:
        if (is_option(argv[1])) // jsp ce qui lui plait pas la
        {
            std::cerr << "Aucun fichier sélectionné";
        }
        else
        {
            // cas par défaut ou on a pas défini d'option : topten
        }
        break;
    case 2:
    {
        // c'est le cas le plus chiant car il y a plein de possibilités. bref voir tablette
        break;
    }
    case 3:
    {
        if (is_option(argv[1]))
        {
            // youpi c'est bon : appeler de quoi faire
            break;
        }
    }
    default:
    {
        std::cerr << "Saisie incorrecte des options et/ou fichier";
    }
    }
}

bool is_option(const char *arg) { return (arg[0] == '-'); }


