#include "parser.hpp"
#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

bool Parser::skip(std::string const &l)
{
    size_t i = 0;

    size_t cur = _stream.tellg();

    while (skip(l[i]))
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

std::string Parser::skipUrl()
{
    std::string result = "";
    while (_stream)
    {
        char c = _stream.get();
        if (c == ' ' || c == ';' || c == '?' || c == '"')
        {
            _stream.seekg(-1, std::ios_base::cur); // rollback
            return result;
        }

        result += c;
    }

    return result;
}

bool Parser::skip(char l)
{
    if (_stream && _stream.get() == l)
    {
        return true;
    }

    _stream.seekg(-1, std::ios_base::cur); // rollback
    return false;
}

bool Parser::parseIp(Parser::LogLine &element)
{

    // [192].0.0.1
    _stream >> element.ip[0];
    // 192[.]0.0.1
    if (!skip("."))
    {
        return false;
    }

    // 192.[0].0.1
    _stream >> element.ip[1];
    // 192.0[.]0.1
    if (!skip("."))
    {
        return false;
    }

    // 192.0.[0].1
    _stream >> element.ip[2];
    // 192.0.0[.]1
    if (!skip("."))
    {
        return false;
    }

    // 192.0.0.[1]
    _stream >> element.ip[3];
    if (!_stream)
    {
        return false;
    }

    return true;
}

std::string Parser::skipUntilAfter(char end)
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

std::string Parser::skipUntil(char end)
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

int Parser::parseInt()
{
    int result;
    _stream >> result;
    return result;
}

bool Parser::parseDate(Parser::LogLine &element)
{
    // 192.160.0.0 - - [08/Sep/2012 :11:16:02 +0200]
    skipUntilAfter('[');

    // from stream

    int day = parseInt();

    skip('/');

    std::string month_str = skipUntil('/');

    skip('/');

    int year = parseInt();

    skipUntilAfter(':');
    int hour = parseInt();

    skipUntilAfter(':');
    int minute = parseInt();
    skipUntilAfter(':');
    int second = parseInt();
    skipUntilAfter(']');

    std::tm t = {};
    t.tm_year = year - 1900;

    // FIXME: faire un tableau string => int
    if (month_str == "Jan")
        t.tm_mon = 0;
    else if (month_str == "Feb")
        t.tm_mon = 1;
    else if (month_str == "Mar")
        t.tm_mon = 2;
    else if (month_str == "Apr")
        t.tm_mon = 3;
    else if (month_str == "May")
        t.tm_mon = 4;
    else if (month_str == "Jun")
        t.tm_mon = 5;
    else if (month_str == "Jul")
        t.tm_mon = 6;
    else if (month_str == "Aug")
        t.tm_mon = 7;
    else if (month_str == "Sep")
        t.tm_mon = 8;
    else if (month_str == "Oct")
        t.tm_mon = 9;
    else if (month_str == "Nov")
        t.tm_mon = 10;
    else if (month_str == "Dec")
        t.tm_mon = 11;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    t.tm_isdst = -1; // on ne considère pas l'heure d'été
    element.time = t;

    return _stream.good();
}
bool Parser::parseRequest(Parser::LogLine &element)
{
    //    "GET /temps/InsaIF.ico HTTP/1.1" 200 766
    //    ["]GET /temps/InsaIF.ico HTTP/1.1" 200 766
    skipUntilAfter('"');
    // [GET] /temps/InsaIF.ico HTTP/1.1" 200 766
    element.request = skipUntil(' ');

    skip(' ');
    return _stream.good();
}

bool Parser::parseGetRequest(Parser::LogLine &element)
{
    // "GET /temps/FondInsa.jpg HTTP/1.1" 200 2828
    // // "http://intranet-if.insa-lyon.fr/temps/style_emploi_du_temps.css"
    // "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:15.0) Gecko/20100101 Firefox/15.0.1"

    // "GET [/temps/FondInsa.jpg]?a=10 HTTP/1.1" 200 2828...

    element.target = skipUrl();

    // "GET /temps/FondInsa.jpg[?a=10] HTTP/1.1" 200 2828...

    skipUntil(' ');

    // /temps/FondInsa.jpg [HTTP/1.1"] 200 2828...
    skipUntilAfter('"');

    //  ...HTTP/1.1"[ 200 2828 "]http://intranet-if.insa-lyon.fr/temps/style_emploi_du_temps.css"
    skipUntilAfter('"');
    element.source = skipUrl();

    skip('"');
    return true;
}

std::optional<Parser::LogLine> Parser::getLine()
{
    Parser::LogLine line = {};

    int cur = _stream.tellg();

    line.raw_line = skipUntilAfter('\n');
    _stream.seekg(cur, std::ios_base::beg); // on revient en arrière

    if (!parseIp(line))
    {
        // empty
        return std::nullopt;
    }

    if (!parseDate(line))
    {
        return std::nullopt;
    }

    if (!parseRequest(line))
    {
        return std::nullopt;
    }

    if (line.request == "GET" || line.request == "POST" || line.request == "UPDATE" || line.request == "DELETE" || line.request == "OPTIONS" || line.request == "HEAD")
    {
        if (!parseGetRequest(line))
        {

            return std::nullopt;
        }
    }
    else
    {
        std::cerr << "Unsupported request type: " << line.request << std::endl;

        skipUntilAfter('\n');
    }
    skipUntilAfter('\n');

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

//    line.source.erase(line.source.begin(), line.source.end(), "http://intranet-if.insa-lyon.fr", "");

  //  line.target.replace(line.source.begin(), line.source.end(), "http://intranet-if.insa-lyon.fr", "");


    return line;
}
