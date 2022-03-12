//
//  PersonProfile.hpp
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include <stdio.h>
#include <vector>
#include "provided.h"
#include "RadixTree.h"

class PersonProfile{
public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    int numAttValPairs;
    std::string p_name;
    std::string p_email;
    RadixTree<std::string> attValPairs;
    std::vector<AttValPair> attValPairs_vector;
};

#endif /* PersonProfile_h */
