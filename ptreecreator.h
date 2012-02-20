//
//  main.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PTREECREATOR_H_
#define PTREECREATOR_H_

#include "ptree.h"

class PTreeCreator {

public:
	typedef double MistakeProbability;

public:

	PTreeCreator();

public:
	PTree* makeTree(const PTree::TOrder& preOrder, const PTree::TOrder& inOrder);
	PTree* generateRandomTree(size_t size);
	PTree* copyTree(const PTree *tree, MistakeProbability mistakeProbability);

private:
	bool produceMistake(MistakeProbability mistakeProbability) const;
	PTree* copy(PTree *tree, MistakeProbability mistakeProbability);
};


#endif /* PTREECREATOR_H_ */
