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

int main (int argc, const char * argv[]) {
    
//    testPTree();
//    std::cout << "OK";

	PTreeCreator creator;
	PTree *tree = makeTestTree3();
    PTree *preOrderCopy = creator.copyTree(tree, 0.5);
    PTree *inOrderCopy = creator.copyTree(tree, 0.5);    
    PTree *postOrderCopy = creator.copyTree(tree, 0.5);
    
    std::cout << "Origin tree: " << std::endl << tree->getRepresentation() << std::endl;
    
    std::cout << "True pre order:" << std::endl;
    PTree::printOrder(tree->getPreOrder());
    
    std::cout << "True in order:" << std::endl;
    PTree::printOrder(tree->getInOrder());
    
    std::cout << "True post order:" << std::endl;
    PTree::printOrder(tree->getPostOrder());
    
    std::cout << "False pre-order tree: " << std::endl << preOrderCopy->getRepresentation() << std::endl;
    std::cout << "False pre-order:" << std::endl;
    PTree::printOrder(preOrderCopy->getPreOrder());
    
    std::cout << "False in-order tree: " << std::endl << inOrderCopy->getRepresentation() << std::endl;
    std::cout << "False in-order:" << std::endl;
    PTree::printOrder(inOrderCopy->getInOrder());
    
    std::cout << "False post-order tree: " << std::endl << postOrderCopy->getRepresentation() << std::endl;
    std::cout << "False post-order:" << std::endl;
    PTree::printOrder(postOrderCopy->getPostOrder());
    
    PTree trAnalyzer(preOrderCopy->getPreOrder(), inOrderCopy->getInOrder());
    std::cout << "Analyzer tree: " << std::endl << trAnalyzer.getRepresentation() << std::endl;
    std::cout << "Analyzer post-order:" << std::endl;
    PTree::printOrder(trAnalyzer.getPostOrder());    
    

    delete preOrderCopy;
    delete inOrderCopy;
    delete postOrderCopy;
	delete tree;

    return 0;
}
