#ifndef STATS_H
#define STATS_H

#include "parser.hpp"

 class Stats
{
    public:

        virtual void interpret(Parser::LogLine const &)=0;

//constructeurs/destructeurs   - - - - - - - - - - - - - - - - - -
         Stats();
         virtual ~Stats();

};


#endif
