//
//  MemberDatabase.cpp
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#include "MemberDatabase.h"
#include <fstream>
#include <iostream>
using namespace std;

MemberDatabase::MemberDatabase(){
    map_Email_to_Members = new RadixTree<PersonProfile*>;
    map_AttValPair_to_Email = new RadixTree<std::set<std::string>>;
}

MemberDatabase::~MemberDatabase(){
//    cerr << "DELETING: MDB" << endl;
    
    for(int i = 0; i < emails.size(); i++){
        PersonProfile* temp = *(map_Email_to_Members->search(emails[i]));
        if(temp != nullptr)
            delete temp;
    }
    
    if(map_Email_to_Members != nullptr)
        delete map_Email_to_Members;
    if(map_AttValPair_to_Email != nullptr)
        delete map_AttValPair_to_Email;
}

bool MemberDatabase::LoadDatabase(std::string filename){
    
    ifstream members_file(filename);
    if (!members_file)
        return false;
    
    while(members_file.peek()!=EOF){
        string name;
        getline(members_file, name);
        if(name == "")
            continue;
        else{
            string email;
            getline(members_file, email);
            emails.push_back(email);
            PersonProfile* pp = new PersonProfile(name,email);
            
            string numAttributes;
            getline(members_file, numAttributes);
            for(int i = 0; i < stoi(numAttributes); i++){
                string attValPair;
                getline(members_file, attValPair);
                string attribute = attValPair.substr(0, attValPair.find(','));\
                string val = attValPair.substr(attValPair.find(',')+1);
                pp->AddAttValPair(AttValPair(attribute,val));
                string attValPair_key = attribute + ',' + val;
                if(map_AttValPair_to_Email->search(attValPair_key) == nullptr){
                    set<string> entry;
                    entry.insert(email);
                    map_AttValPair_to_Email->insert(attValPair_key, entry);
                }
                else{
                    map_AttValPair_to_Email->search(attValPair_key)->insert(email);
                }
            }
            if(map_Email_to_Members->search(email) == nullptr)
                map_Email_to_Members->insert(email,pp);
            else
                return false;
        }
    }
//    map_Email_to_Members.print();
    members_file.close();
    return true;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const{
    if(map_Email_to_Members->search(email) == nullptr)
        return nullptr;
    else
        return *(map_Email_to_Members->search(email));
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const{
    string attValPair_key = input.attribute + ',' + input.value;
    set<string>* entry = map_AttValPair_to_Email->search(attValPair_key);
    
    vector<string> result;
    if(entry == nullptr)
        return result;
    else{
        auto it = (*entry).begin();
        while(it != (*entry).end()){
            result.push_back(*it);
            it++;
        }
    }
    return result;
}
