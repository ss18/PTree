//
//  main.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ptree.h"
#include "test.h"
#include "ptreecreator.h"
#include "panalyzer.h"

int main (int argc, const char * argv[]) {
    
    PTreeCreator creator;
    PTreeCreator::MistakeProbability P = 0.2;
    PTree *origin = creator.generateRandomTree(20);
    PTree *falseOrigin1 = creator.copyTree(origin, P);
    PTree *falseOrigin2 = creator.copyTree(origin, P);
    PTree *falseOrigin3 = creator.copyTree(origin, P);
        
    PTreeAnalyzer analyzer(origin, falseOrigin1->getPreOrder(), falseOrigin2->getInOrder(), falseOrigin3->getPostOrder());
    analyzer.analyze();

    delete falseOrigin3;
    delete falseOrigin2;
    delete falseOrigin1;    
    delete origin;
    
    return 0;
}
