//
//  PersonProfile.cpp
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#include "PersonProfile.h"
#include <iostream>

PersonProfile::PersonProfile(std::string name, std::string email) : p_name(name), p_email(email), numAttValPairs(0){
}

PersonProfile::~PersonProfile(){
//    std::cerr << "DELETING PERSON" << std::endl;
}

std::string PersonProfile::GetName() const {
//    std::cerr<<p_name<<std::endl;
    return p_name;
};

std::string PersonProfile::GetEmail() const {
    return p_email;
};

void PersonProfile::AddAttValPair(const AttValPair &attval){
    std::string key = attval.attribute + "," + attval.value;
    std::string* entry = attValPairs.search(key);
    
    if(entry != nullptr && attval.value == *entry)
        return;
    else{
        attValPairs.insert(key, attval.value);
        numAttValPairs++;
        attValPairs_vector.push_back(attval);
    }
};

int PersonProfile::GetNumAttValPairs() const {
    return numAttValPairs;
};

bool PersonProfile::GetAttVal(int attribute_num, AttValPair &attval) const{
    if(attribute_num < 0 || attribute_num >= numAttValPairs)
        return false;
    else{
        attval = attValPairs_vector[attribute_num];
        return true;
    }
    
}

