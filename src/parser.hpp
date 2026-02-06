/*************************************************************************
                           Parser  -  Analyseur syntaxique de logs
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Équipe LogAnalyzer
    e-mail               : equipe@loganalyzer.fr
*************************************************************************/

//---------- Interface de la classe <Parser> (fichier parser.hpp) --------
#if ! defined ( PARSER_HPP )
#define PARSER_HPP

//--------------------------------------------------- Interfaces utilisées
#include <ctime>
#include <istream>
#include <string>
#include <optional>

//------------------------------------------------------------------------
// Rôle de la classe <Parser>
// Par exemple:
/*
 * 192.168.0.0 - - [08/Sep/2012:11:16:02 +0200] "GET /temps/4IF16.html HTTP/1.1"
 * 200 12106 "http://intranet-if.insa-lyon.fr/temps/4IF15.html" "Mozilla/5.0
 * (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1"
 * - ip: [192, 168, 0,0]
 * - time: 08/Sep/2012 :11:16:02
 * - request: GET
 * - source: http://intranet-if.insa-lyon.fr/temps/4IF15.html
 * - target: 4IF16.html
 * - user_agent: "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101
 * Firefox/14.0.1"
 */
//------------------------------------------------------------------------

class Parser
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------------------ Types
    struct LogLine
    {
        std::string raw_line; // ligne brute complète
        int ip[4];
        std::tm time;
        std::string request;
        std::string source;
        std::string target;
        std::string user_agent; // le string contenant le reste
    };

//----------------------------------------------------- Méthodes publiques
    std::optional<LogLine> GetLine();
    // Mode d'emploi :
    // Tente de lire la prochaine ligne du flux.
    // Renvoie un std::optional contenant la ligne parsée si succès,
    // ou std::nullopt si fin de fichier, erreur, ou ligne filtrée.

//-------------------------------------------- Constructeurs - destructeur
    Parser(std::istream &stream, bool exclude_documents, std::optional<int> certain_hours);
    // Mode d'emploi :
    // Constructeur prenant le flux à analyser et les options de filtrage.

//------------------------------------------------------------------ PRIVE

private:
//----------------------------------------------------- Méthodes privées
    bool ParseIp(LogLine &element);
    bool ParseDate(LogLine &element);
    bool ParseRequest(LogLine &element);
    bool ParseGetRequest(LogLine &element);

    int ParseInt();
    
    std::string SkipUrl();

    // "hello world".skipUntilAfter('o') => hello
    std::string SkipUntilAfter(char v);

    // "hello world".skipUntil('o') => hell
    std::string SkipUntil(char v);

    bool Skip(char l);
    bool Skip(std::string const &l);

//----------------------------------------------------- Attributs privés
    bool excludeDocuments;
    std::optional<int> certainHours;
    std::istream &_stream;
};

#endif // PARSER_HPP
