//
//  ptreecreator.cpp
//  PTree
//
//  Created by Semen Zhydenko on 2/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PTREECREATOR_H_
#define PTREECREATOR_H_

#include <vector>
#include "ptree.h"

class PTreeCreator {

public:
	typedef double MistakeProbability;
	typedef size_t NumberOfElements;

public:

	PTreeCreator();

	PTree* makeTree(const PTree::TOrder& preOrder, const PTree::TOrder& inOrder) const;
	PTree* generateRandomTree(NumberOfElements size) const;
	PTree* copyTree(const PTree *tree, MistakeProbability mistakeProbability) const;
    
    PTree* restore(const PTree::TOrder& preOrder, const PTree::TOrder& inOrder, const PTree::TOrder& postOrder) const;
    

private:
	typedef std::vector<int> UnsortedData;

private:

	void generateRandomTree(PTree *tree, const UnsortedData& data) const;
	UnsortedData getTreeElements(NumberOfElements size) const;
	bool produceMistake(MistakeProbability mistakeProbability) const;
	PTree* copy(PTree *tree, MistakeProbability mistakeProbability) const;
};


#endif /* PTREECREATOR_H_ */
