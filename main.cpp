//
//  main.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "ptree.h"
#include "test.h"
#include "ptreecreator.h"
#include "panalyzer.h"

int main (int argc, const char * argv[]) {

    int count = 0;
    
    PTreeCreator creator;
    for (int i = 0; i < 1000; i++) {
        PTreeCreator::MistakeProbability P = 0.1;
        PTree *origin = creator.generateRandomTree(10);
        PTree *falseOrigin1 = creator.copyTree(origin, P);
        PTree *falseOrigin2 = creator.copyTree(origin, P);
        PTree *falseOrigin3 = creator.copyTree(origin, P);
        
        PTreeAnalyzer analyzer(origin, falseOrigin1->getPreOrder(), falseOrigin2->getInOrder(), falseOrigin3->getPostOrder());
        PTree *restored = NULL;
        try {
            restored = analyzer.restore();
        } catch (PTreeAnalyzer::UnableToRestore&) {
            ;
        }
        
        if (restored != NULL && *restored == *origin) {
            count++;
        }
            
        delete restored;
        
        delete falseOrigin3;
        delete falseOrigin2;
        delete falseOrigin1;    
        delete origin;
    }
    
    std::cout << count <<  std::endl;;
    
    
    return 0;
}
