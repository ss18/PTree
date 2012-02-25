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
//
//const int pre___[20] = { 4, 11, 2, 6, 20, 12, 13, 3, 14, 15, 5, 1, 9, 19, 7, 10, 16, 8, 17, 18};
//const int in___[20] = { 6, 20, 12, 3, 13, 14, 2, 15, 4, 11, 7, 8, 16, 10, 19, 9, 1, 5, 18, 17};
//const int post___[20] = { 3, 12, 14, 13, 20, 15, 6, 2, 4, 16, 10, 7, 8, 9, 19, 1, 18, 17, 5, 11};

int main (int argc, const char * argv[]) {

    int s = 0;
    
        PTreeCreator creator;
        for (int i = 0; i<10000; i++) {
        PTreeCreator::MistakeProbability P = 0.05;
        PTree *origin = creator.generateRandomTree(100);
        PTree *falseOrigin1 = creator.copyTree(origin, P);
        PTree *falseOrigin2 = creator.copyTree(origin, P);
        PTree *falseOrigin3 = creator.copyTree(origin, P);
    
    
        PTreeAnalyzer analyzer(origin, falseOrigin1->getPreOrder(), falseOrigin2->getInOrder(), falseOrigin3->getPostOrder());
            if (analyzer.analyze()) {
                s++;
            }
        PTree *restored = analyzer.restore();
            std::cout << restored->getRepresentation();
        
        delete falseOrigin3;
        delete falseOrigin2;
        delete falseOrigin1;    
        delete origin;
    }
    
    std::cout << s;
    
    return 0;
}
