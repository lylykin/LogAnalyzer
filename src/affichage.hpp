#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <optional>
#include <string>

typedef struct ProgArgument
{
    std::optional<int> time_selection;

    bool gen_graph = false; // -g [graph_outfile]
    std::string graph_outfile;

    bool exclude_document = false; // -e

    bool has_dump = false; // -d

    std::string log_path; // LogAnalyzer [paramètres] [log_path]
                          // fichier log à analyser
} ProgArgument;

ProgArgument parse_parameter (int argc, const char ** argv);
bool is_option(const char *arg);
void option_interpreter(ProgArgument &);

//std::fstream open_file(const char * filename);
//récupère le contenu du fichier
#endif
