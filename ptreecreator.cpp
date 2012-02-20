//
//  main.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ptreecreator.h"
#include <cstdlib>

PTreeCreator::PTreeCreator() {
	srand((unsigned)time(0));
	rand();
}

PTree* PTreeCreator::copyTree(const PTree *tree, MistakeProbability mistakeProbability) {
	PTree tr = *tree;
	return copy(&tr, mistakeProbability);
}

bool PTreeCreator::produceMistake(MistakeProbability mistakeProbability) const {
	return (rand() / double(RAND_MAX)) < mistakeProbability;
}

PTree* PTreeCreator::copy(PTree *tree, MistakeProbability mistakeProbability) {
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
