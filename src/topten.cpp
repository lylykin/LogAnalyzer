#include <string>
#include <map>
#include <vector>

#include "topten.hpp"
#include "parser.hpp"

using dict = std::map<std::string, int>;

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

std::vector<std::string>& TopTen::findTopTenLinks()
{
    std::string currentTopLink;
    std::vector<std::vector<std::string>>::iterator vectIt;
    dict::iterator dIt;
    int numberLinks = 0;
    int lastValueAdded = 0;
    while (true)
    {
        currentTopLink = findTopOneLink();
        dIt = dAllLinks.find(currentTopLink);
        if (dIt->second == lastValueAdded)
        {
            vectIt = theTopTen.begin() + i - 1;
        }
    }
}
