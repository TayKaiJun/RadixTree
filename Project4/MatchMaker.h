//
//  MatchMaker.hpp
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include <stdio.h>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase* mm_mdb;
    const AttributeTranslator* mm_at;
};

#endif /* MatchMaker_h */
