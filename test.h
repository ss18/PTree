//
//  test.h
//  PTree
//
//  Created by Semen Zhydenko on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TEST_H_
#define TEST_H_

class PTree;

void testOneTree(const PTree *tree, size_t treeSize, const int *preOrder, const int *inOrder, const int *postOrder);

PTree* makeTestTree1();
PTree* makeTestTree2();
PTree* makeTestTree3();
PTree* makeTestTree4();

// run me for testing :)
bool testPTree();


#endif /* TEST_H_ */
