#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "topten.hpp"
#include "parser.hpp"

using dict = std::map<std::string, int>;

void TopTen::printTopTen() const
{
    int i = 1;
    for (const std::vector<std::string>& linksVect : theTopTen)
    {
        std::cout << i << ")" << std::endl;
        for (const std::string& link : linksVect)
        {
            std::cout << link << std::endl;
        }
        std::cout << std::endl;
        i++;
    }
}

void TopTen::printAllLinks() const
{
    for (auto& pair : dAllLinks)
    {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}

void TopTen::interpret(Parser::LogLine const & line)
{
    std::string target(line.get.target);
    dict::iterator it = dAllLinks.find(target);
    if (it == dAllLinks.end())
    {
        dAllLinks.insert(std::pair<std::string, int>(target, 1));
    }
    else
    {
        it->second++;
    }
}

std::string TopTen::findTopOneLink()
{
    int max = 0;
    std::string topLink("");
    for (std::pair<const std::string, int>& pair : dAllLinks)
    {
        if (pair.second > max)
        {
            max = pair.second;
            topLink = pair.first;
        }
    }
    return topLink;
}

std::vector<std::vector<std::string>>& TopTen::findTopTenLinks()
{
    std::string currentTopLink;
    std::vector<std::vector<std::string>>::iterator vectIt;
    dict::iterator dIt;
    int numberLinks = 0;
    int lastValueAdded = 0;
    int i = 0;
    while (numberLinks < 10)
    {
        currentTopLink = findTopOneLink();
        dIt = dAllLinks.find(currentTopLink);
        if (dIt->second == lastValueAdded)
        {
            theTopTen[i-1].push_back(currentTopLink);
        }
        else
        {
            theTopTen[i].push_back(currentTopLink);
            lastValueAdded = dIt->second;
            i++;
        }
        numberLinks++;
        dAllLinks.erase(currentTopLink);
    }

    //on vérifie qu'il n'y a pas d'autres liens au delà du top 10 qui ont le même nombre de visites que le top 10
    i--;
    currentTopLink = findTopOneLink();
    dIt = dAllLinks.find(currentTopLink);
    while (dIt->second == lastValueAdded)
    {
        theTopTen[i].push_back(currentTopLink);
        dAllLinks.erase(currentTopLink);
        currentTopLink = findTopOneLink();
        dIt = dAllLinks.find(currentTopLink);
    }
    return theTopTen;
}

TopTen::TopTen()
    : Stats()
    {
        theTopTen.resize(10);
    }
