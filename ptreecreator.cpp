//
//  ptreecreator.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ptreecreator.h"
#include <cstdlib>

//
// Public stuff
//

PTreeCreator::PTreeCreator() {
	srand((unsigned)time(0));
	rand();
}

PTree* PTreeCreator::generateRandomTree(NumberOfElements size) const {

	if (size > 0) {
		PTree *tree = new PTree(0, NULL, NULL);
		UnsortedData data = getTreeElements(size);
		generateRandomTree(tree, data);
		return tree;

	} else {
		return NULL;
	}
}

PTree* PTreeCreator::copyTree(const PTree *tree, MistakeProbability mistakeProbability) const {
	PTree tr = *tree;
	return copy(&tr, mistakeProbability);
}

//
// Private stuff
//

void PTreeCreator::generateRandomTree(PTree *tree, const UnsortedData& data) const {
	UnsortedData::const_iterator randomElement = data.begin() + rand()%data.size();
	tree->value = *randomElement;
	UnsortedData left(data.begin(), randomElement);
	UnsortedData right(randomElement + 1, data.end());

	if (left.size() > 0) {
		tree->left = new PTree(0);
		generateRandomTree(tree->left, left);
	}

	if (right.size() > 0) {
		tree->right = new PTree(0);
		generateRandomTree(tree->right, right);
	}

}

PTreeCreator::UnsortedData PTreeCreator::getTreeElements(NumberOfElements size) const {
	UnsortedData data, orderedData;

	// fill vector in order 1..size
	for(size_t i = 0; i < size; i++) {
		orderedData.push_back(i + 1);
	}

	// move elements from orderedData to data in random sequence
	for(size_t i = 0; i < size; i++) {
		UnsortedData::iterator ref = orderedData.begin() + rand()%(size - i);
		data.push_back(*ref);
		orderedData.erase(ref);
	}

	return data;
}

bool PTreeCreator::produceMistake(MistakeProbability mistakeProbability) const {
	return (rand() / double(RAND_MAX)) < mistakeProbability;
}

PTree* PTreeCreator::copy(PTree *tree, MistakeProbability mistakeProbability) const {
	if (tree == NULL) {
		return NULL;
	}

	PTree *node = produceMistake(0.5) ? tree->left : tree->right;
	if (produceMistake(mistakeProbability) && node) {
		std::swap(tree->value, node->value);
	}

	PTree *tr = new PTree(tree->value);
	tr->left = copy(tree->left, mistakeProbability);
	tr->right = copy(tree->right, mistakeProbability);

	return tr;
}
