/*
 * test.h
 *
 *  Created on: Feb 19, 2012
 *      Author: ss18
 */

#ifndef TEST_H_
#define TEST_H_

class PTree;

void testOneTree(const PTree *tree, size_t treeSize, const int *preOrder, const int *inOrder, const int *postOrder);

PTree* makeTestTree1();
PTree* makeTestTree2();
PTree* makeTestTree3();
PTree* makeTestTree4();

bool testPTree();


#endif /* TEST_H_ */
