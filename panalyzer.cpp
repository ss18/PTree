//
//  panalyzer.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "panalyzer.h"

//
// Public stuff
//

PTreeAnalyzer::PTreeAnalyzer(const PTree *origin, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_):
                                                originTree(PTree::copy(origin)), falsePreOrder(pre_), falseInOrder(in_), falsePostOrder(post_), possibleTree(NULL), possiblePValue(0){
    
}

void PTreeAnalyzer::analyze() {
    
    std::cout << "Origin tree: " << originTree->getRepresentation() << std::endl;
    std::cout << "Origin pre:";
    PTree::printOrder(originTree->getPreOrder());
    std::cout << "Origin in:";
    PTree::printOrder(originTree->getInOrder());
    std::cout << "Origin post:";
    PTree::printOrder(originTree->getPostOrder());
    
    std::cout << std::endl <<"False pre:";
    PTree::printOrder(falsePreOrder);
    std::cout << "False in:";
    PTree::printOrder(falseInOrder);
    std::cout << "False post:";
    PTree::printOrder(falsePostOrder);    
    

//    PTree::TOrder::value_type root;
//    
//    if (falsePreOrder[0] == falsePostOrder[falsePostOrder.size() - 1]) {
//        root = falsePreOrder[0];
//    } else if (falsePreOrder[1] == falsePostOrder[falsePostOrder.size() - 2]) {
//        root = 
//    }
//
//    if (f)
    
    
    //possibleTree = analyze(PTree *tree, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_);
}
