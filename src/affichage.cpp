#include "affichage.hpp"
#include "topten.hpp"
#include "graph.hpp"

ProgArgument parse_parameter(int argc, const char **argv)
{
    // prendre les options
    //  tant que pas arrivés au dernier (avec argc)
    //  case switch en fonction des options

    ProgArgument args;

    int params = 1;
    while (params < argc)
    {

        if (is_option(argv[params]))
        {
            if (argv[params][1] == 'e')
            {
                args.exclude_document = true;
            }
            else if (argv[params][1] == 'g')
            {
                args.gen_graph = true;
                args.graph_outfile = argv[params+1];
                //args.graph_outfile.assign(argv[params + 1], strlen(argv[params + 1]));
                params++;
            }
            else if (argv[params][1] == 't')
            {
                args.time_selection = std::atoi(argv[params + 1]);
                //args.time_selection.assign(argv[params + 1], strlen(argv[params + 1]));
                params++;
            }
        }
        else // comme ce n'est pas une option et que les paramètres des options sont gérés dans l'autre cas, c'est forcément le fichier source de logs
        {    // si params = 1 => cas par défaut
            args.log_path = argv[params];
            // pathLogs.assign(argv[params], strlen(argv[params]));
        }
        params++;
    }

    return args;
}

bool is_option(const char *arg) { return (arg[0] == '-'); }

void option_interpreter(ProgArgument &optn)
{
    if (!(optn.gen_graph) && !(optn.has_dump))
    {
        // cas par défaut : topten
        TopTen top;
        top.interpret_file(optn.log_path,optn.exclude_document, optn.time_selection);
        top.findTopTenLinks();
        top.printTopTen();
    }
    else
    {
        Graph graph;
        graph.interpret_file(optn.log_path, optn.exclude_document, optn.time_selection);
        graph.graphiz(optn.graph_outfile);
    }
}
