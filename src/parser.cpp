#include "parser.hpp"
#include <iomanip>
#include <vector>
#include <chrono>

bool Parser::skip(std::string const& l)
{
    size_t i = 0;

    while(skip(l[i]))
    {
        i++;
    }

    return i == l.length();
}

bool Parser::skip(char l)
{
    if(_stream &&  _stream.get() == l)
    {
        return true;
    }
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
        if(c == end)
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
        if(c == end)
        {
            _stream.seekg(-1, std::ios_base::cur); // rollback
            return result;
        }

        result += c;
    }

    return result;
}


bool Parser::parseDate(Parser::LogLine &element)
{
    // 192.160.0.0 - - [08/Sep/2012 :11:16:02 +0200]
    skipUntilAfter('[');


    // from stream

    std::chrono::sys_time date = std::chrono::system_clock();

    std::chrono::from_stream(_stream, "%d/%D/%Y :%H:%M:%S %Z", date);

    //auto v = std::chrono::utc_clock::(_stream);
    // [08]/Sep/2012
    std::string date_str=  skipUntil('/');

    // 08[/]Sep/2012
    if(!skip('/'))
    {
        return false;
    }


    // 08/[Sep]/2012
    std::string month =  skipUntil('/');
    if(!skip('/'))
    {
        return false;
    }


    std::string year = skipUntil(':');






    // 08/Sep/2012 :11:16:02 +0200
    //date_s%d/%b/%Y:%H:%M:%S %z");

   // std::get_time(&time, "%d/%"
  //  date_str >> std::get_time(&t, "%Y-%b-%d %H:%M:%S");
}

Parser::LogLine Parser::getLine()
{
    Parser::LogLine line = {};

    line.request = "INCOMPLETE";

    if (!parseIp(line))
    {
        return line;
    }

    if (!parseDate(line))
    {
        return line;
    }

    if (!parseRequest(line))
    {
        return line;
    }

    if (line.request == "GET")
    {
        if (!parseGetRequest(line))
        {
            return line;
        }
    }

    else if (line.request == "ERROR")
    {
        if (!parseErrorRequest(line))
        {
            return line;
        }
    }

    skipUntilAfter('\n');

    return line;
}
