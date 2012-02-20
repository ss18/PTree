//
//  PTree.h
//  PTree
//
//  Created by Semen Zhydenko on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PTree_ptree_h
#define PTree_ptree_h

#include <vector>
#include <string>

class PTreeCreator;

class PTree {
public:

    typedef std::vector<int> TOrder;
    friend class PTreeCreator;

public:
    PTree(int val);
    PTree(int val, PTree *l, PTree *r);
    PTree(const TOrder& preOrder, const TOrder& inOrder);
    PTree(const PTree& t);
    ~PTree();

    TOrder getPreOrder() const;
    TOrder getInOrder() const;
    TOrder getPostOrder() const;
    TOrder getLevelOrder() const;

    std::string getRepresentation() const;

    bool operator==(const PTree& tree) const;
    bool operator!=(const PTree& tree) const;

    static void printOrder(const TOrder& order);

private:

    void getPreOrder(TOrder& order) const;
    void getInOrder(TOrder& order) const;
    void getPostOrder(TOrder& order) const;
    void getLevelOrder(TOrder& order) const;

    void getSubRepresentation(std::stringstream& stream) const;
    void restore(TOrder& preOrder, const TOrder& inOrder);

    static PTree* copy(PTree *tree);

private:

    int value;
    PTree *left;
    PTree *right;

};

#endif
