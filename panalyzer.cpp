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

bool PTreeAnalyzer::analyze() {
    
//    std::cout << "Origin tree: " << originTree->getRepresentation() << std::endl;
//    std::cout << "Origin pre:";
//    PTree::printOrder(originTree->getPreOrder());
//    std::cout << "Origin in:";
//    PTree::printOrder(originTree->getInOrder());
//    std::cout << "Origin post:";
//    PTree::printOrder(originTree->getPostOrder());
//    
//    std::cout << std::endl <<"False pre:";
//    PTree::printOrder(falsePreOrder);
//    std::cout << "False in:";
//    PTree::printOrder(falseInOrder);
//    std::cout << "False post:";
//    PTree::printOrder(falsePostOrder);    

    int val = 0;
    size_t len = falsePreOrder.size();
    bool ret = false;
    if (falsePreOrder[0] == falsePostOrder[len - 1] || falsePreOrder[0] == falsePostOrder[len - 2]) {
        ret = check(falsePreOrder[0]);
        val = falsePreOrder[0];
    } else if (falsePreOrder[1] == falsePostOrder[len - 1] || falsePreOrder[1] == falsePostOrder[len - 2] ) {
        ret = check(falsePreOrder[1]);
        val = falsePreOrder[1];
    } else {
        ret = check(falsePreOrder[0]);
        val = falsePreOrder[0];        
        if (ret == false) {
            ret = check(falsePreOrder[1]);
            val = falsePreOrder[1];            
        }
    }
    
    return (ret && (val == originTree->value));
//    if (ret && val == originTree->value) {
//        std:: cout << "OK: " << val;
//    } else {
//        std:: cout << "Error: " << val << " :" << originTree->value;
//    }

}

bool PTreeAnalyzer::check(PTree::TOrder::value_type value) {

    PTree::TOrder fPreOrder = falsePreOrder;
    PTree::TOrder fInOrder = falseInOrder;
    PTree::TOrder fPostOrder = falsePostOrder;

    
    PTree::TOrder::iterator iter = std::find(fPreOrder.begin(), fPreOrder.end(), value);
    std::swap(*iter, *fPreOrder.begin());
    fPreOrder.erase(fPreOrder.begin());
    
    fInOrder.erase(std::find(fInOrder.begin(), fInOrder.end(), value));
    
    iter = std::find(fPostOrder.begin(), fPostOrder.end(), value);
    std::swap(*iter, *(fPostOrder.end() - 1));        
    fPostOrder.erase(fPostOrder.end() - 1);
    
    size_t pos = analyze(fPreOrder, fInOrder, fPostOrder);
    
    return pos != SIZE_T_MAX;
}

size_t PTreeAnalyzer::analyze(const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) {
    size_t pos = SIZE_T_MAX;
    PTree::TOrder pre = pre_;
    PTree::TOrder in = in_;
    PTree::TOrder post = post_;
       
    
    for (size_t p = 0; p < pre_.size(); p++) {
        PTree::TOrder::value_type value = pre[p];
        pre[p] = 0;
        PTree::TOrder::iterator iter = std::find(in.begin(), in.end(), value);
        *iter = 0;
        iter = std::find(post.begin(), post.end(), value);
        *iter = 0;
        
        
//        std::cout << std::endl;
//        std::cout << "Origin pre:";
//        PTree::printOrder(pre);
//        std::cout << "Origin in:";
//        PTree::printOrder(in);
//        std::cout << "Origin post:";
//        PTree::printOrder(post);        

        size_t preSize = countZerosFromLeft(pre);
        size_t postSize = countZerosFromLeft(post);
        size_t inSize = countZerosFromLeft(in);        

        if (preSize == postSize && postSize == inSize) {
            pos = p;            
            break;
        } else if (preSize == postSize) {
            break;
        }
//        } else if (postSize == inSize) {
//            break;
//        }  else if (preSize == inSize) {
//            break;
//        } 
    }
    
    return pos;
}

size_t PTreeAnalyzer::countZerosFromLeft(const PTree::TOrder& order_) {
    size_t count = 0;
    for (PTree::TOrder::const_iterator i = order_.begin(); i != order_.end(); i++) {
        if (*i == 0) {
            count++;
        } else {
            break;
        }
    }
    return count;
}
