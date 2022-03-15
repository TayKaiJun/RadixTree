//
//  AttributeTranslator.cpp
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>
using namespace std;

AttributeTranslator::AttributeTranslator(){
    map_sourceAtt_to_compatabileAtt = new RadixTree<std::vector<AttValPair>>;
}

AttributeTranslator::~AttributeTranslator(){
//    cerr << "DELETING: ATTRIBUTE TRANS" << endl;
    if(map_sourceAtt_to_compatabileAtt != nullptr)
        delete map_sourceAtt_to_compatabileAtt;
}

bool AttributeTranslator::Load(std::string filename){
    
    ifstream translator_file(filename);
    if (!translator_file)
        return false;
    
    while(translator_file.peek()!=EOF){
        string line;
        getline(translator_file, line);
        if(line == "")
            continue;
        else{
            string sourceAttVal, compAtt, compVal;
            int commaCount = 0;
            for(int i = 0; i < line.length(); i++){
                if(line[i] == ','){
                    if(commaCount == 0)
                        sourceAttVal += line[i];
                    commaCount++;
                }
                else{
                    switch (commaCount) {
                        case 0:
                        case 1:
                            sourceAttVal += line[i];
                            break;
                        case 2:
                            compAtt += line[i];
                            break;
                        case 3:
                            compVal += line[i];
                            break;
                        default:
                            break;
                    }
                }
            }
            vector<AttValPair>* entry = map_sourceAtt_to_compatabileAtt->search(sourceAttVal);
            if(entry == nullptr){
                entry = new vector<AttValPair>;
                entry->push_back(AttValPair(compAtt,compVal));
                map_sourceAtt_to_compatabileAtt->insert(sourceAttVal, *entry);
            }
            else{
                entry->push_back(AttValPair(compAtt,compVal));
            }
        }
    }
    translator_file.close();
    return true;
}


std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const{
    string attValPair_key = source.attribute + ',' + source.value;
    if(map_sourceAtt_to_compatabileAtt->search(attValPair_key) == nullptr){
        std::vector<AttValPair> temp;
        return temp;
    }
    else
        return *(map_sourceAtt_to_compatabileAtt->search(attValPair_key));
}
