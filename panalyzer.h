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

    struct IterationData {
        PTree::TOrder::value_type node;
        
        PTree::TOrder leftPreOrder;
        PTree::TOrder leftInOrder;
        PTree::TOrder leftPostOrder;
        
        PTree::TOrder rightPreOrder;
        PTree::TOrder rightInOrder;
        PTree::TOrder rightPostOrder;
    };
    
public:    
    struct UnableToRestore {};
    
public:    
    PTreeAnalyzer(const PTree *origin, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_);
    PTree* restore() const;
    bool analyze() const;
    
private:

    void restore(PTree* tree,  PTree::TOrder& pre_,  PTree::TOrder& in_,  PTree::TOrder post_) const throw(UnableToRestore);
    IterationData getIterationData(PTree::TOrder& preOrder, PTree::TOrder& inOrder, PTree::TOrder postOrder) const throw(UnableToRestore);
    bool case1Check(const PTree::TOrder::value_type node, const PTree::TOrder::const_iterator start, const PTree::TOrder& inOrder) const;
    PTree::TOrder getUniqIntersection(const PTree::TOrder& o1, const PTree::TOrder& o2) const;
    
private:

    // initial data
    const PTree *originTree;
    
    mutable PTree::TOrder falsePreOrder;
    mutable PTree::TOrder falseInOrder;
    mutable PTree::TOrder falsePostOrder;
    
    const PTree::TOrder originFalsePreOrderMutable;
    const PTree::TOrder originFalseInOrderMutable;
    const PTree::TOrder originFalsePostOrderMutable;
    
    // analyzer results data
    PTree *possibleTree;
    PTreeCreator::MistakeProbability possiblePValue;
};

#endif
