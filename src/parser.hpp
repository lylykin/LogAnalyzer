#ifndef PARSER_HPP
#define PARSER_HPP
#include <ctime>
#include <istream>
#include <stdint.h>
#include <string>
#include <optional>
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



class Parser
{
public:
    struct LogLine
    {

        std::string raw_line; // ligne brute complète
        int ip[4];
        std::tm time;

        // soit request == "GET"
        // - du coup c'est une requête, infos dans .get
        // soit request == "ERROR"
        // - donne une erreur, infos dans .error
        // soit request == "POST"/"UPDATE"/...
        // - pas encore supporté

        std::string request;

        std::string source;
        std::string target;
        std::string user_agent; // le string contenant le reste
    };



    Parser(std::istream &stream, bool exclude_documents, std::optional<int> certain_hours) :
        excludeDocuments(exclude_documents),
        certainHours(certain_hours),
        _stream(stream)
    {
        _stream.seekg(std::ios_base::beg);
    };

    std::optional<LogLine> getLine();

private:
    bool excludeDocuments;
    std::optional<int> certainHours;

    bool parseIp(LogLine &element);
    bool parseDate(LogLine &element);
    bool parseRequest(LogLine &element);
    bool parseGetRequest(LogLine &element);
    bool parseErrorRequest(LogLine &element);

    std::string skipUrl();


    int parseInt();

    // "hello world".skipUntilAfter('o') => hello
    std::string skipUntilAfter(char v);

    // "hello world".skipUntil('o') => hell
    std::string skipUntil(char v);

    bool skip(char l);
    bool skip(std::string const &l);

    std::istream &_stream;
};

#endif
