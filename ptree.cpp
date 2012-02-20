//
//  PTree.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ptree.h"
#include <iostream>
#include <sstream>
#include <algorithm>

//
// Public stuff
//

PTree::PTree(int val):value(val), left(NULL), right(NULL) {

}

PTree::PTree(int val, PTree *l, PTree *r):value(val), left(l), right(r) {

}

PTree::PTree(const TOrder& preOrder, const TOrder& inOrder) {
	TOrder pre = preOrder;
	this->restore(pre, inOrder);
}

PTree::PTree(const PTree& t) {
	value = t.value;
	left = copy(t.left);
	right = copy(t.right);
}

PTree::~PTree() {
    delete left;
    delete right;

    left = NULL;
    right = NULL;
}

PTree::TOrder PTree::getPreOrder() const {
    TOrder order;
    this->getPreOrder(order);
    return order;
}

PTree::TOrder PTree::getInOrder() const {
    TOrder order;
    this->getInOrder(order);
    return order;
}

PTree::TOrder PTree::getPostOrder() const {
    TOrder order;
    this->getPostOrder(order);
    return order;
}

PTree::TOrder PTree::getLevelOrder() const {
    TOrder order;
    this->getLevelOrder(order);
    return order;
}

std::string PTree::getRepresentation() const {
	std::stringstream stream;
	this->getSubRepresentation(stream);
	return stream.str();
}

bool PTree::operator==(const PTree& tree) const {
	if (value != tree.value) {
		return false;
	}

	if ((left == NULL && tree.left != NULL) || (right == NULL && tree.right != NULL) ||
			(left != NULL && tree.left == NULL) || (right != NULL && tree.right == NULL)) {
		return false;
	}

	bool cmp = true;

	if (left != NULL && tree.left != NULL ) {
		cmp &= (*left == *tree.left);
	}

	if (cmp && right != NULL && tree.right != NULL ) {
		cmp &= (*right == *tree.right);
	}

	return cmp;
}

bool PTree::operator!=(const PTree& tree) const {
	return !(*this == tree);
}

void PTree::printOrder(const TOrder& order) {
    std::cout << "{ ";
    for(TOrder::const_iterator i = order.begin(); i < order.end()- 1; i++) {
    	std::cout << *i << ", ";
    }
    std::cout << *(order.end()- 1) << "}" << std::endl;
}

//
// Private stuff
//

void PTree::getPreOrder(TOrder& order) const {
    order.push_back(value);

    if (left != NULL) {
        left->getPreOrder(order);
    }

    if (right != NULL) {
        right->getPreOrder(order);
    }
}

void PTree::getInOrder(TOrder& order) const {
    if (left != NULL) {
        left->getInOrder(order);
    }

    order.push_back(value);

    if (right != NULL) {
        right->getInOrder(order);
    }
}

void PTree::getPostOrder(TOrder& order) const {
    if (left != NULL) {
        left->getPostOrder(order);
    }

    if (right != NULL) {
        right->getPostOrder(order);
    }

    order.push_back(value);
}

void PTree::getLevelOrder(TOrder& order) const {
    // TODO: implement this
}

void PTree::getSubRepresentation(std::stringstream& stream) const {
	stream << "(" << value;
	if (left != NULL) {
		left->getSubRepresentation(stream);
	} else {
		stream << "()";
	}
	if (right != NULL) {
		right->getSubRepresentation(stream);
	} else {
		stream << "()";
	}
	stream << ")";
}

void PTree::restore(TOrder& preOrder, const TOrder& inOrder) {
	value = *preOrder.begin();
	TOrder::const_iterator center = std::find(inOrder.begin(), inOrder.end(), value);
	TOrder inOrderLeft(inOrder.begin(), center);
	TOrder inOrderRight(center + 1, inOrder.end());

	preOrder.erase(preOrder.begin());

	if (inOrderLeft.size() > 0 && preOrder.size() > 0) {
		left = new PTree(0);
		left->restore(preOrder, inOrderLeft);
	}

	if (inOrderRight.size() > 0 && preOrder.size() > 0) {
		right = new PTree(0);
		right->restore(preOrder, inOrderRight);
	}
}

PTree* PTree::copy(PTree *tree) {
	if (tree == NULL) {
		return NULL;
	}

	PTree *t = new PTree(tree->value);
	t->left = copy(tree->left);
	t->right = copy(tree->right);

	return t;
}

