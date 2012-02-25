//
//  panalyzer.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "panalyzer.h"
#include <assert.h>

//
// Public stuff
//

PTreeAnalyzer::PTreeAnalyzer(const PTree *origin, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_):
                                                originTree(PTree::copy(origin)), falsePreOrder(pre_), falseInOrder(in_), falsePostOrder(post_), possibleTree(NULL), possiblePValue(0){
    
}

PTree* PTreeAnalyzer::restore() const {
    
    PTree *tree = new PTree(0, NULL, NULL);
    restore(tree, falsePreOrder, falseInOrder, falsePostOrder);
    return tree;
}

void PTreeAnalyzer::restore(PTree* tree, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) const {
    PTree::TOrder fPreOrder = pre_;
    PTree::TOrder fInOrder = in_;    
    PTree::TOrder fPostOrder = post_;
    
    Iteration data = getNode(fPreOrder, fInOrder, fPostOrder);
    
    tree->value = data.node;
    
    std::swap(*std::find(fPreOrder.begin(), fPreOrder.end(), data.node), *fPreOrder.begin());
    fPreOrder.erase(fPreOrder.begin());
    
    
    
    PTree::TOrder::iterator iter= std::find(fInOrder.begin(), fInOrder.end(), data.node);
    
    std::cout << data.sizeofLeftSubTree << " "<< fInOrder[data.sizeofLeftSubTree - 1] << std::endl;;    
    PTree::printOrder(fInOrder);    
    
    std::swap(*iter, fInOrder[data.sizeofLeftSubTree - 1]);
    fInOrder.erase(std::find(fInOrder.begin(), fInOrder.end(), data.node));
    
    std::swap(*std::find(fPostOrder.begin(), fPostOrder.end(), data.node), *(fPostOrder.end() - 1));        
    fPostOrder.erase(fPostOrder.end() - 1);    
    
    
    if (fPreOrder.size() == 0) {
        return;
    }
    
    PTree::TOrder lpre(fPreOrder.begin(), fPreOrder.begin() + data.sizeofLeftSubTree);
    PTree::TOrder lin(fInOrder.begin(), fInOrder.begin() + data.sizeofLeftSubTree);
    PTree::TOrder lpost(fPostOrder.begin(), fPostOrder.begin() + data.sizeofLeftSubTree);    
    
    
    PTree::TOrder rpre(fPreOrder.begin() + data.sizeofLeftSubTree, fPreOrder.end());
    PTree::TOrder rin(fInOrder.begin() + data.sizeofLeftSubTree, fInOrder.end());
    PTree::TOrder rpost(fPostOrder.begin() + data.sizeofLeftSubTree, fPostOrder.end());
    
    if (lpre.size() > 0) {
        tree->left = new PTree(0, NULL, NULL);
        restore(tree->left, lpre, lin, lpost);
    }
    
    if (rpre.size() > 0) {
        tree->right = new PTree(0, NULL, NULL);
        restore(tree->right, rpre, rin, rpost);        
    }    
}

bool PTreeAnalyzer::analyze() const{
    Iteration data = getNode(falsePreOrder, falseInOrder, falsePostOrder);
    
    PTree::TOrder realIn = originTree->getInOrder();
    size_t realSizeOfLeftTree = std::find(realIn.begin(), realIn.end(), originTree->value) - realIn.begin();
    
    return (data.node == originTree->value) && (realSizeOfLeftTree == data.sizeofLeftSubTree);


}

PTreeAnalyzer::Iteration PTreeAnalyzer::getNode(const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) const {
    Iteration data;
    
    size_t len = pre_.size();
    assert(pre_.size() > 0);
    assert(pre_.size() == in_.size());
    assert(post_.size() == in_.size());
        
    if (pre_[0] == post_[len - 1]) {
        data.node = pre_[0];
        data.sizeofLeftSubTree = check2(pre_[0], pre_, in_, post_);
    } else {
        
        if (check1(pre_[0], pre_, in_, post_)) {
            data.node = pre_[0];
            data.sizeofLeftSubTree = std::find(in_.begin(), in_.end(), pre_[0]) - in_.begin();
        } else {
            data.node = post_[len - 1];
            data.sizeofLeftSubTree = std::find(in_.begin(), in_.end(), post_[len - 1]) - in_.begin();            
        }
    
    }
    
    return data;
}

size_t PTreeAnalyzer::check2(PTree::TOrder::value_type value, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) const {
    PTree::TOrder fPreOrder = pre_;
    PTree::TOrder fInOrder = in_;    
    PTree::TOrder fPostOrder = post_;
    
    fPreOrder.erase(fPreOrder.begin());
    fInOrder.erase(std::find(fInOrder.begin(), fInOrder.end(), value));
    fPostOrder.erase(fPostOrder.end() - 1);
    
    for (PTree::TOrder::iterator i = fPreOrder.begin(); i != fPreOrder.end(); i++) {
        PTree::TOrder::iterator j = std::find(fInOrder.begin(), fInOrder.end(), *i);
        PTree::TOrder::iterator k = std::find(fPostOrder.begin(), fPostOrder.end(), *i);
        *i = 0;
        *j = 0;
        *k = 0;
        
        const size_t zeros = i - fPreOrder.begin() + 1;
        
        // if possition the same, it could be possible left size        
        if (zeros == countZerosFromLeft(fPostOrder) && zeros == countZerosFromLeft(fInOrder)) {
            return zeros;
        }
    }
    
    return SIZE_MAX;
    
}

bool PTreeAnalyzer::check1(PTree::TOrder::value_type value, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) const {

    bool isOk = false;
    
    PTree::TOrder fPreOrder = pre_;
    PTree::TOrder fPostOrder = post_;

    std::swap(*std::find(fPreOrder.begin(), fPreOrder.end(), value), *fPreOrder.begin());
    fPreOrder.erase(fPreOrder.begin());
    
    std::swap(*std::find(fPostOrder.begin(), fPostOrder.end(), value), *(fPostOrder.end() - 1));        
    fPostOrder.erase(fPostOrder.end() - 1);
    
    
    PTreeAnalyzer::TPossibleSizes lSizes = getFromLeft(fPreOrder, fPostOrder);
    
    size_t tmp = std::find(in_.begin(), in_.end(), value) - in_.begin();
        
    for (int i = 0; i < lSizes.size(); i++) {
        if (tmp == lSizes[i]) {
            isOk = true;
            break;
        }
        
    }
    
    return  isOk;
}


PTreeAnalyzer::TPossibleSizes PTreeAnalyzer::getFromLeft(const PTree::TOrder& pre_, const PTree::TOrder post_) const {
    TPossibleSizes sizes;
    PTree::TOrder pre = pre_;
    PTree::TOrder post = post_;    
    for (PTree::TOrder::iterator i = pre.begin(); i != pre.end(); i++) {
        PTree::TOrder::iterator j = std::find(post.begin(), post.end(), *i);
        *i = 0;
        *j = 0;       
        
        const size_t zeros = i - pre.begin() + 1;
        // if possition the same, it could be possible left size        
        if (zeros == countZerosFromLeft(post)) {
            sizes.push_back(zeros);
        }
    }
    return sizes;
}

size_t PTreeAnalyzer::countZerosFromLeft(const PTree::TOrder& order_) const {
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


