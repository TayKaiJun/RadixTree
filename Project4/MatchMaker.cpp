//
//  MatchMaker.cpp
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#include "MatchMaker.h"
#include <map>
#include <set>
#include <iostream>
using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at){
//    mm_mdb = new MemberDatabase(mdb);
//    mm_at = new AttributeTranslator(at);
    mm_mdb = &mdb;
    mm_at = &at;
}

MatchMaker::~MatchMaker(){
//    cerr << "DELETING: MATCHMAKER" << endl;
}

bool isGreaterThan(EmailCount e1, EmailCount e2){
    //when the method returns true, e1 is in front of e2, else e2 swaps with e1
    if(e1.count > e2.count)
        return true;
    else if(e1.count == e2.count){
        if(e1.email < e2.email)
            return true;
        else
            return false;
    }
    else
        return false;
}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const{
    const PersonProfile* pp = mm_mdb->GetMemberByEmail(email);
    std::vector<EmailCount> output;
    
    map<string,set<string>> email_histogram;
    for(int i = 0; i < pp->GetNumAttValPairs(); i++){
        AttValPair attValPair;
        if(!pp->GetAttVal(i, attValPair))
            break;
        vector<AttValPair> attVal_result = mm_at->FindCompatibleAttValPairs(attValPair);
        for(int j = 0; j < attVal_result.size(); j++){
            vector<string> email_result = mm_mdb->FindMatchingMembers(attVal_result[j]);
            for(int k = 0; k < email_result.size() ; k++){
                if(email_result[k] == email)
                    continue;
                email_histogram[email_result[k]].insert(attVal_result[j].attribute + "," + attVal_result[j].value);
            }
        }
    }
    
    if(threshold <= 0)
        threshold = 1;
    
    for (auto it = email_histogram.begin(); it != email_histogram.end(); it++) {
        if(it->second.size() < threshold)
            continue;
        else{
            output.push_back(EmailCount(it->first, it->second.size()));
        }
    }
    
    sort(output.begin(), output.end(), isGreaterThan);
    
    return output;
}
