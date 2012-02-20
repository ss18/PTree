/*
 * test.cpp
 *
 *  Created on: Feb 19, 2012
 *      Author: ss18
 */

#include "ptree.h"
#include <memory>
#include <assert.h>
#include <iostream>

void testOneTree(const PTree *tree, size_t treeSize,
					const int *preOrder, const int *inOrder, const int *postOrder) {
	PTree::TOrder pre(preOrder, preOrder + treeSize);
	PTree::TOrder in(inOrder, inOrder + treeSize);
	PTree::TOrder post(postOrder, postOrder + treeSize);

	assert(tree->getPreOrder() == pre);
	assert(tree->getInOrder() == in);
	assert(tree->getPostOrder() == post);

	PTree copy1 = *tree;
	assert(*tree == copy1);
	assert(tree->getRepresentation() == copy1.getRepresentation());

	assert(tree->getPreOrder() == copy1.getPreOrder());
	assert(tree->getInOrder() == copy1.getInOrder());
	assert(tree->getPostOrder() == copy1.getPostOrder());

	PTree copy2(copy1.getPreOrder(), copy1.getInOrder());
    
	assert(copy2.getPreOrder() == copy1.getPreOrder());
	assert(copy2.getInOrder() == copy1.getInOrder());
	assert(copy2.getPostOrder() == copy1.getPostOrder());

	PTree copy3(0);
	assert(*tree != copy3);
}

// test tree1, numbers set [1,2,3,4]
// rep: (1(4()())(2(3()())()))
const size_t tree1Size = 4;
const int tree1PreOrder[tree1Size] = {1, 4, 2, 3};
const int tree1InOrder[tree1Size] = {4, 1, 3, 2};
const int tree1PostOrder[tree1Size] = {4, 3, 2, 1};
PTree* makeTestTree1() {
    PTree *t3 = new PTree(3, NULL, NULL);
    PTree *t4 = new PTree(4, NULL, NULL);
    PTree *t2 = new PTree(2, t3, NULL);
    PTree *t1 = new PTree(1, t4, t2);
	return t1;
}

// test tree2, numbers set [1,2,3,4]
// rep: (1(4()())(2()(3()())))
const size_t tree2Size = 4;
const int tree2PreOrder[tree2Size] = {1, 4, 2, 3};
const int tree2InOrder[tree2Size] = {4, 1, 2, 3};
const int tree2PostOrder[tree2Size] = {4, 3, 2, 1};
PTree* makeTestTree2() {
    PTree *t3 = new PTree(3, NULL, NULL);
    PTree *t4 = new PTree(4, NULL, NULL);
    PTree *t2 = new PTree(2, NULL, t3);
    PTree *t1 = new PTree(1, t4, t2);
	return t1;
}

// test tree3, numbers set [1,2,3,4,5,6,7]
// rep: (7(4(1(2()(3()()))())(5()(6()())))())
const size_t tree3Size = 7;
const int tree3PreOrder[tree3Size] = {7, 4, 1, 2, 3, 5, 6};
const int tree3InOrder[tree3Size] = {2, 3, 1, 4, 5, 6, 7};
const int tree3PostOrder[tree3Size] = {3, 2, 1, 6, 5, 4, 7};
PTree* makeTestTree3() {
	PTree *t3 = new PTree(3, NULL, NULL);
    PTree *t6 = new PTree(6, NULL, NULL);
    PTree *t2 = new PTree(2, NULL, t3);
    PTree *t1 = new PTree(1, t2, NULL);
    PTree *t5 = new PTree(5, NULL, t6);
    PTree *t4 = new PTree(4, t1, t5);
    PTree *t7 = new PTree(7, t4, NULL);
	return t7;
}

// test tree4, numbers set [1,2,3,4,5]
// rep: (2(1(4()())())(3()(5()())))
const size_t tree4Size = 5;
const int tree4PreOrder[tree4Size] = {2, 1, 4, 3, 5};
const int tree4InOrder[tree4Size] = {4, 1, 2, 3, 5};
const int tree4PostOrder[tree4Size] = {4, 1, 5, 3, 2};
PTree* makeTestTree4() {
    PTree *t4 = new PTree(4, NULL, NULL);
    PTree *t5 = new PTree(5, NULL, NULL);
    PTree *t1 = new PTree(1, t4, NULL);
    PTree *t3 = new PTree(3, NULL, t5);
    PTree *t2 = new PTree(2, t1, t3);
	return t2;
}

void testPTree() {
	std::auto_ptr<PTree> tree1(makeTestTree1());
	testOneTree(tree1.get(), tree1Size, tree1PreOrder, tree1InOrder, tree1PostOrder);

	std::auto_ptr<PTree> tree2(makeTestTree2());
	testOneTree(tree2.get(), tree2Size, tree2PreOrder, tree2InOrder, tree2PostOrder);

	std::auto_ptr<PTree> tree3(makeTestTree3());
	testOneTree(tree3.get(), tree3Size, tree3PreOrder, tree3InOrder, tree3PostOrder);

	std::auto_ptr<PTree> tree4(makeTestTree4());
	testOneTree(tree4.get(), tree4Size, tree4PreOrder, tree4InOrder, tree4PostOrder);

	assert(*tree1.get() != *tree2.get());
	assert(*tree2.get() != *tree3.get());
	assert(*tree3.get() != *tree4.get());
	assert(*tree4.get() != *tree1.get());
}
