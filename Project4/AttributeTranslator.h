//
//  AttributeTranslator.hpp
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <stdio.h>
#include <vector>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator{
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<std::vector<AttValPair>>* map_sourceAtt_to_compatabileAtt;
};

#endif /* AttributeTranslator_h */
