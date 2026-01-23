#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "topten.hpp"
#include "parser.hpp"

void TopTen::printTopTen() const
{
    for (const std::vector<pairSi>& linksVect : theTopTen)
    {
        for (const pairSi& aPair : linksVect)
        {
            std::cout << aPair.first << "( " << aPair.second  << " hits)" << std::endl;
        }
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
    std::string target(line.target);
    dict::iterator it = dAllLinks.find(target);
    if (it == dAllLinks.end())
    {
        dAllLinks.insert(pairSi(target, 1));
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

tabLinks& TopTen::findTopTenLinks()
{
    std::string currentTopLink;
    dict::iterator dIt;
    pairSi aPair;
    int numberLinks = 0;
    int lastValueAdded = 0;
    int i = 0;
    while (numberLinks < 10 && (int)dAllLinks.size() != 0)
    {
        currentTopLink = findTopOneLink();
        dIt = dAllLinks.find(currentTopLink);
        aPair.first = currentTopLink;
        aPair.second = dIt->second;
        if (dIt->second == lastValueAdded)
        {
            theTopTen[i-1].push_back(aPair);
        }
        else
        {
            theTopTen[i].push_back(aPair);
            i++;
        }

        lastValueAdded = dIt->second;
        numberLinks++;
        dAllLinks.erase(currentTopLink);
    }

    //on vérifie qu'il n'y a pas d'autres liens au delà du top 10 qui ont le même nombre de visites que le top 10
    i--;
    currentTopLink = findTopOneLink();
    dIt = dAllLinks.find(currentTopLink);
    aPair.first = currentTopLink;
    aPair.second = dIt->second;
    while (dIt != dAllLinks.end() && dIt->second == lastValueAdded)
    {
        theTopTen[i].push_back(aPair);
        dAllLinks.erase(currentTopLink);
        currentTopLink = findTopOneLink();
        dIt = dAllLinks.find(currentTopLink);
    }
    return theTopTen;
}

TopTen::TopTen()
    : Stats()
    {
        //initie le vecteur à une longueur de 10
        theTopTen.resize(10);
    }
