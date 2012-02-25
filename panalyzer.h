//
//  panalyzer.h
//  PTree
//
//  Created by Semen Zhydenko on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// Restore a binary tree of N nodes, every node is uniquely labeled with a number from 1 to N, given the tree vectors corresponding of the Inorder, Postorder and Preorder iterations of the tree (http://en.wikipedia.org/wiki/Tree_traversal). However, the iterators produce an imperfect result: sometimes, with an unknown uniform probability P, the iterator swaps two connected nodes before iterating them (you can imagine there is a machine reading the data, but the process of reading is stochastic). Every iterator runs on the tree master copy, this means, the changes of one iteration don't affect the others.
                                                                                                                                                                                                
// To solve the problem, return the true Inorder and Preorder. Optionally, for each element, return the probability of being located in that position by chance (also known as p-value) and approximate P.

#ifndef PTree_panalyzer_h
#define PTree_panalyzer_h

#include <vector>

#include "ptree.h"
#include "ptreecreator.h"

class PTreeAnalyzer {
    
    typedef std::vector<size_t> TPossibleSizes;
    
    struct Iteration {
        PTree::TOrder::value_type node;
        size_t sizeofLeftSubTree;
    };
    
public:    
    PTreeAnalyzer(const PTree *origin, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_);
    
    PTree* restore() const;
    
    bool analyze() const;
    
private:

    void restore(PTree* tree, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) const;
    
    Iteration getNode(const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) const;
    
    bool check1(PTree::TOrder::value_type value, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) const;
    size_t check2(PTree::TOrder::value_type value, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_) const;
    
    TPossibleSizes getFromLeft(const PTree::TOrder& pre_, const PTree::TOrder post_) const;
    size_t countZerosFromLeft(const PTree::TOrder& order_) const;
    
private:

    // initial data
    const PTree *originTree;
    
    const PTree::TOrder falsePreOrder;
    const PTree::TOrder falseInOrder;
    const PTree::TOrder falsePostOrder;
    
    // analyzer results data
    PTree *possibleTree;
    PTreeCreator::MistakeProbability possiblePValue;
};

#endif
