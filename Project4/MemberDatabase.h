//
//  MemberDatabase.hpp
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <stdio.h>
#include "provided.h"
#include <vector>
#include "PersonProfile.h"
#include <set>

class MemberDatabase{

public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;

private:
    std::vector<std::string> emails; //to be deleted later??
    RadixTree<PersonProfile*>* map_Email_to_Members;
    RadixTree<std::set<std::string>>* map_AttValPair_to_Email;
};

#endif /* MemberDatabase_h */
