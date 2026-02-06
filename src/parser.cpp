/*************************************************************************
                           Parser  -  Analyseur syntaxique de logs
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Équipe LogAnalyzer
    e-mail               : equipe@loganalyzer.fr
*************************************************************************/

//---------- Réalisation de la classe <Parser> (fichier parser.cpp) ------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

//------------------------------------------------------ Include personnel
#include "parser.hpp"

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs
Parser::Parser(std::istream &stream, bool exclude_d, std::optional<int> hours) :
    excludeDocuments(exclude_d),
    certainHours(hours),
    _stream(stream)
{
    _stream.seekg(std::ios_base::beg);
}

//----------------------------------------------------- Méthodes publiques
std::optional<Parser::LogLine> Parser::GetLine()
{
    Parser::LogLine line = {};

    int cur = _stream.tellg();

    line.raw_line = SkipUntilAfter('\n');
    _stream.seekg(cur, std::ios_base::beg); // on revient en arrière

    if (!ParseIp(line))
    {
        return std::nullopt;
    }

    if (!ParseDate(line))
    {
        return std::nullopt;
    }

    if (!ParseRequest(line))
    {
        return std::nullopt;
    }

    if (line.request == "GET" || line.request == "POST" || line.request == "UPDATE" || line.request == "DELETE" || line.request == "OPTIONS" || line.request == "HEAD")
    {
        if (!ParseGetRequest(line))
        {
            return std::nullopt;
        }
    }
    else
    {
        std::cerr << "Requête non supportée: " << line.request << std::endl;
        SkipUntilAfter('\n');
    }
    SkipUntilAfter('\n');

    if (certainHours.has_value() && line.time.tm_hour != certainHours.value())
    {
        return std::nullopt;
    }

    if (excludeDocuments)
    {
        auto ext = line.target.substr(line.target.find_first_of("."), 4);

        if (ext == ".png" || ext == ".svg" || ext == ".jpg" || ext == ".gif" || ext == ".css" || ext == ".ico" || ext == ".js" || ext == ".jpeg")
        {
            return std::nullopt;
        }
    }

    static const std::string s = "http://intranet-if.insa-lyon.fr";

    std::string::size_type i = line.target.find(s);

    if (i != std::string::npos)
       line.target.erase(i, s.length());

    i = line.source.find(s);

    if (i != std::string::npos)
       line.source.erase(i, s.length());

    return line;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes privées
bool Parser::Skip(std::string const &l)
{
    size_t i = 0;
    size_t cur = _stream.tellg();

    while (Skip(l[i]))
    {
        i++;
    }

    if (i == l.length())
    {
        return true;
    }

    _stream.seekg(cur, std::ios_base::beg); // rollback
    return false;
}

std::string Parser::SkipUrl()
{
    std::string result = "";
    while (_stream)
    {
        char c = _stream.get();
        // On considère que les URL sont terminées par un espace, un point-virgule, un point d'interrogation, ou une guillemet
        if (c == ' ' || c == ';' || c == '?' || c == '"')
        {
            _stream.seekg(-1, std::ios_base::cur); // rollback
            return result;
        }
        result += c;
    }
    return result;
}

bool Parser::Skip(char l)
{
    if (_stream && _stream.get() == l)
    {
        return true;
    }
    _stream.seekg(-1, std::ios_base::cur); // rollback
    return false;
}

bool Parser::ParseIp(Parser::LogLine &element)
{
    // [192].0.0.1
    _stream >> element.ip[0];
    // 192[.]0.0.1
    if (!Skip(".")) return false;

    // 192.[0].0.1
    _stream >> element.ip[1];
    // 192.0[.]0.1
    if (!Skip(".")) return false;

    // 192.0.[0].1
    _stream >> element.ip[2];
    // 192.0.0[.]1
    if (!Skip(".")) return false;

    // 192.0.0.[1]
    _stream >> element.ip[3];
    if (!_stream) return false;

    return true;
}

std::string Parser::SkipUntilAfter(char end)
{
    std::string result = "";
    while (_stream)
    {
        char c = _stream.get();
        result += c;
        if (c == end)
        {
            return result;
        }
    }
    return result;
}

std::string Parser::SkipUntil(char end)
{
    std::string result = "";
    while (_stream)
    {
        char c = _stream.get();
        if (c == end)
        {
            _stream.seekg(-1, std::ios_base::cur); // rollback
            return result;
        }
        result += c;
    }
    return result;
}

int Parser::ParseInt()
{
    int result;
    _stream >> result;
    return result;
}

bool Parser::ParseDate(Parser::LogLine &element)
{
    // 192.160.0.0 - - [08/Sep/2012 :11:16:02 +0200]
    SkipUntilAfter('[');

    // [08/Sep/2012 :11:16:02 +0200]

    int day = ParseInt(); // [08] /Sep/2012 :11:16:02 +0200]
    Skip('/');
    std::string month_str = SkipUntil('/'); // 08/[Sep]/2012 :11:16:02 +0200]
    Skip('/');
    int year = ParseInt(); // 08/Sep/[2012] :11:16:02 +0200]

    // 08/Sep/2012[ :11:16:02 +0200]

    SkipUntilAfter(':');

    int hour = ParseInt(); // 08/Sep/2012 :[11]:16:02 +0200]

    SkipUntilAfter(':');
    int minute = ParseInt(); // 08/Sep/2012 :11:[16]:02 +0200]
    SkipUntilAfter(':');
    int second = ParseInt(); // 08/Sep/2012 :11:16:[02] +0200]
    SkipUntilAfter(']');

    std::tm t = {};
    t.tm_year = year - 1900;

    // FIXME: faire un tableau string => int
    if (month_str == "Jan") t.tm_mon = 0;
    else if (month_str == "Feb") t.tm_mon = 1;
    else if (month_str == "Mar") t.tm_mon = 2;
    else if (month_str == "Apr") t.tm_mon = 3;
    else if (month_str == "May") t.tm_mon = 4;
    else if (month_str == "Jun") t.tm_mon = 5;
    else if (month_str == "Jul") t.tm_mon = 6;
    else if (month_str == "Aug") t.tm_mon = 7;
    else if (month_str == "Sep") t.tm_mon = 8;
    else if (month_str == "Oct") t.tm_mon = 9;
    else if (month_str == "Nov") t.tm_mon = 10;
    else if (month_str == "Dec") t.tm_mon = 11;
    
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    t.tm_isdst = -1; // on ne considère pas l'heure d'été
    element.time = t;

    return _stream.good();
}

bool Parser::ParseRequest(Parser::LogLine &element)
{
    //    "GET /temps/InsaIF.ico HTTP/1.1" 200 766
    //    ["]GET /temps/InsaIF.ico HTTP/1.1" 200 766
    SkipUntilAfter('"');
    // [GET] /temps/InsaIF.ico HTTP/1.1" 200 766
    element.request = SkipUntil(' ');
    Skip(' ');
    return _stream.good();
}

bool Parser::ParseGetRequest(Parser::LogLine &element)
{
    // "GET /temps/FondInsa.jpg HTTP/1.1" 200 2828
    // // "http://intranet-if.insa-lyon.fr/temps/style_emploi_du_temps.css"
    // "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:15.0) Gecko/20100101 Firefox/15.0.1"
    
    // "GET [/temps/FondInsa.jpg]?a=10 HTTP/1.1" 200 2828...
    element.target = SkipUrl();

    // "GET /temps/FondInsa.jpg[?a=10] HTTP/1.1" 200 2828...
    SkipUntil(' ');

    // /temps/FondInsa.jpg [HTTP/1.1"] 200 2828...
    SkipUntilAfter('"');

    //  ...HTTP/1.1"[ 200 2828 "]http://intranet-if.insa-lyon.fr/temps/style_emploi_du_temps.css"
    SkipUntilAfter('"');
    
    element.source = SkipUrl();

    Skip('"');
    return true;
}

