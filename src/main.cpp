#include <iostream>

#include "affichage.hpp"

int main(int argc, const char ** argv)
{
// but du main : on a le stream in de l'user, et en fonction des param

    if(argc < 2)
    {
        std::cerr << "Usage: LogAnalyzer [options] <logfile>" << std::endl;
        return 1;
    }
    else
    {
        ProgArgument args = parse_parameter(argc, argv);
        option_interpreter(args);
    }

    return 0;
}
