//
//  panalyzer.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <algorithm>
#include "panalyzer.h"
#include <assert.h>

//
// Public stuff
//

PTreeAnalyzer::PTreeAnalyzer(const PTree *origin, const PTree::TOrder& pre_, const PTree::TOrder& in_, const PTree::TOrder post_): originTree(PTree::copy(origin)), falsePreOrder(pre_), 
        falseInOrder(in_), falsePostOrder(post_), possibleTree(NULL), possiblePValue(0), originFalsePreOrderMutable(pre_), originFalseInOrderMutable(in_), originFalsePostOrderMutable(post_)
{
    
}

PTree* PTreeAnalyzer::restore() const {
    PTree *tree = new PTree(0, NULL, NULL);
    restore(tree, falsePreOrder, falseInOrder, falsePostOrder);
    return tree;
}

bool PTreeAnalyzer::analyze() const {
    IterationData data;
    
    try {
        data = getIterationData(falsePreOrder, falseInOrder, falsePostOrder);
    } catch (UnableToRestore &) {
        return false;
    }
    
    PTree::TOrder::value_type orignNode = originTree->value;
    PTree::TOrder orignLeftPreOrder;
    PTree::TOrder orignRightPreOrder;    
    if (originTree->left) {
        orignLeftPreOrder = originTree->left->getPreOrder();
    }
    
    if (originTree->right) {
        orignRightPreOrder = originTree->right->getPreOrder();        
    }
      
    if (orignNode == data.node && orignLeftPreOrder.size() == getUniqIntersection(orignLeftPreOrder, data.leftPreOrder).size() && orignRightPreOrder.size() == getUniqIntersection(orignRightPreOrder, data.rightPreOrder).size()) {
        return true;
    }
    
    return false;
}

//
// Private stuff
//

void PTreeAnalyzer::restore(PTree* tree,  PTree::TOrder& pre_,  PTree::TOrder& in_,  PTree::TOrder post_) const throw(UnableToRestore) {
    
    IterationData data = getIterationData(pre_, in_, post_);
    tree->value = data.node;
    
    if (data.leftPreOrder.size() > 0) {
        tree->left = new PTree(0);
        restore(tree->left, data.leftPreOrder, data.leftInOrder, data.leftPostOrder);
    }
    
    if (data.rightPreOrder.size() > 0) {
        tree->right = new PTree(0);
        restore(tree->right, data.rightPreOrder, data.rightInOrder, data.rightPostOrder);
    }
    
}

PTreeAnalyzer::IterationData PTreeAnalyzer::getIterationData(PTree::TOrder& preOrder, PTree::TOrder& inOrder, PTree::TOrder& postOrder) const throw(UnableToRestore) {
    assert(preOrder.size() > 0);
    assert(inOrder.size() > 0);
    assert(postOrder.size() > 0);
    
    // it could happens because of previous statistic errors
    if (getUniqIntersection(preOrder, inOrder).size() != getUniqIntersection(inOrder, postOrder).size()) {
    	throw UnableToRestore();
    }

    PTreeAnalyzer::IterationData data;
    data.node = 0;
    
    if (preOrder.size() == 1) {
        data.node = *preOrder.begin();
        
    } else if (*preOrder.begin() == *(postOrder.end() - 1)) {
        data.node = *preOrder.begin();

        if (ifNodeHasProperInOrderPosition(data.node, preOrder.begin() + 1, inOrder)) {
        	// case 1,
        	fillIterationDataForInOrderPosition(data, preOrder, inOrder, postOrder);
        } else {
        	// case 2,
        	fillIterationDataForWrongInOrder(data, preOrder, inOrder, postOrder);
        }
        
    } else {
        
        if (ifNodeHasProperInOrderPosition(*preOrder.begin(), preOrder.begin() + 1, inOrder)) {
        	// case 3,
            data.node = *preOrder.begin();
            fillIterationDataForInOrderPosition(data, preOrder, inOrder, postOrder);
            
        } else if (ifNodeHasProperInOrderPosition(*(postOrder.end() - 1), postOrder.begin(), inOrder)) {
        	// case 4:
        	data.node = *(postOrder.end() - 1);
            fillIterationDataForInOrderPosition(data, preOrder, inOrder, postOrder);
            
        } else {
        	// case 5,
            throw UnableToRestore();
        }
    }
    

    return data;
}

bool PTreeAnalyzer::ifNodeHasProperInOrderPosition(const PTree::TOrder::value_type node, const PTree::TOrder::const_iterator start, const PTree::TOrder& inOrder) const {
    PTree::TOrder::const_iterator iter = std::find(inOrder.begin(), inOrder.end(), node);
    size_t leftTreeLen = iter - inOrder.begin();
    assert(iter != inOrder.end());

    PTree::TOrder o1(inOrder.begin(), iter);
    PTree::TOrder o2(start, start + leftTreeLen);
    return o1.size() == getUniqIntersection(o1, o2).size();
}

void PTreeAnalyzer::fillIterationDataForInOrderPosition(IterationData& data, PTree::TOrder& preOrder, PTree::TOrder& inOrder, PTree::TOrder& postOrder) const {

	// move preOrder node to the right place, if needed
	std::swap(*preOrder.begin(), *std::find(preOrder.begin(), preOrder.end(), data.node));

	// move postOrder node to the right place, if needed
	std::swap(*(postOrder.end() - 1), *std::find(postOrder.begin(), postOrder.end(), data.node));

	PTree::TOrder::iterator inCenter = std::find(inOrder.begin(), inOrder.end(), data.node);
    size_t leftTreeLen = inCenter - inOrder.begin();

    data.leftPreOrder = PTree::TOrder(preOrder.begin() + 1, preOrder.begin() + 1 + leftTreeLen);
    data.rightPreOrder = PTree::TOrder(preOrder.begin() + 1 + leftTreeLen, preOrder.end());

    data.leftInOrder = PTree::TOrder(inOrder.begin(), inCenter);
    data.rightInOrder = PTree::TOrder(inCenter + 1, inOrder.end());

    data.leftPostOrder = PTree::TOrder(postOrder.begin(), postOrder.begin() + leftTreeLen);
    data.rightPostOrder = PTree::TOrder(postOrder.begin() + leftTreeLen, postOrder.end() - 1);
}

void PTreeAnalyzer::fillIterationDataForWrongInOrder(IterationData& data, PTree::TOrder& preOrder, PTree::TOrder& inOrder, PTree::TOrder& postOrder) const {
	int mult = -1;
	for(size_t pos = inOrder.size()/2, add = 0; pos < inOrder.size() && pos >=0; add++, mult *= -1) {
		PTree::TOrder modifiedInOrder = inOrder;
		std::swap(modifiedInOrder[pos], *std::find(modifiedInOrder.begin(), modifiedInOrder.end(), data.node));
		if (ifNodeHasProperInOrderPosition(data.node, preOrder.begin() + 1, modifiedInOrder) &&
				ifNodeHasProperInOrderPosition(data.node, postOrder.begin(), modifiedInOrder)) {
			fillIterationDataForInOrderPosition(data, preOrder, modifiedInOrder, postOrder);
			break;
		}
		pos += add*mult;
	}
}

PTree::TOrder PTreeAnalyzer::getUniqIntersection(const PTree::TOrder& o1, const PTree::TOrder& o2) const {
    PTree::TOrder order1 = o1;
    PTree::TOrder order2 = o2;
    
    PTree::TOrder inter(std::min(order1.size(), order2.size()));
    
    std::sort(order1.begin(), order1.end());
    std::sort(order2.begin(), order2.end());
    
    PTree::TOrder::iterator interEnd = set_intersection (order1.begin(), order1.end(), order2.begin(), order2.end(), inter.begin()); 
    
    return interEnd == inter.begin() ? PTree::TOrder() : PTree::TOrder(inter.begin(), interEnd);
}
