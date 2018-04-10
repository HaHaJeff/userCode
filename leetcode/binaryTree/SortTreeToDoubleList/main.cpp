#include <stdio.h>
#include <stdlib.h>
struct BinaryTreeNode {
    BinaryTreeNode():pLeft(NULL), pRight(NULL), value(0){}
    struct BinaryTreeNode* pLeft;
    struct BinaryTreeNode* pParent;
    struct BinaryTreeNode* pRight;
    int value;
};

struct BinarySearchTree {
    BinarySearchTree() : pRoot(NULL){}
    struct BinaryTreeNode *pRoot;
};

void Insert(struct BinarySearchTree* pTree, int value);

void CreateTree(struct BinarySearchTree* pTree, int size);

struct BinaryTreeNode* BinaryTreeToDoubleList(struct BinaryTreeNode* pRoot);

/*
 * The return value is the end node of double list, pRoot is left end, should return the max node of root
 * otherwise, return the min node of root
 * */
struct BinaryTreeNode* Recursion(struct BinaryTreeNode* pRoot, bool asRight);

void PrintList(struct BinaryTreeNode* pRoot);

void DeleteList(struct BinaryTreeNode* pRoot);

int main(void) {
    int size = 10;
    struct BinarySearchTree *pTree = NULL;
    pTree = (struct BinarySearchTree*)malloc(sizeof(struct BinarySearchTree));
    pTree->pRoot = NULL;

    CreateTree(pTree, size);

    struct BinaryTreeNode* pMin = pTree->pRoot;
    while (pMin->pLeft != NULL)
        pMin = pMin->pLeft;
    
    struct BinaryTreeNode* pList = BinaryTreeToDoubleList(pTree->pRoot);
    PrintList(pMin);
    DeleteList(pMin);

    free(pTree);
    pTree = NULL;
} 

void CreateTree(struct BinarySearchTree* pTree, int size) {
    srandom(100);
    for(int i=  0; i < size - 1; i++) {
        Insert(pTree, random()%size);
    }
}

struct BinaryTreeNode* BinaryTreeToDoubleList(struct BinaryTreeNode* pRoot) {
    return Recursion(pRoot, false);
}

struct BinaryTreeNode* Recursion(struct BinaryTreeNode* pRoot, bool asRight) {
    
    if (pRoot->pLeft == NULL && pRoot->pRight == NULL) {
        return pRoot;
    }

    struct BinaryTreeNode* pLeft = NULL;
    struct BinaryTreeNode* pRight = NULL;

    if (pRoot->pLeft != NULL) 
        pLeft = Recursion(pRoot->pLeft, false);

    if (pLeft != NULL) {
        pLeft->pRight = pRoot;
        pRoot->pLeft = pLeft;
    }

    if (pRoot->pRight != NULL) 
        pRight = Recursion(pRoot->pRight, true);

    if (pRight != NULL) {
        pRight->pLeft = pRoot;
        pRoot->pRight = pRight;
    }
        
    struct BinaryTreeNode* pRet = NULL;
    //return min node
    if (asRight) {
        pRet = pRoot;
        while(pRet->pLeft != NULL)
            pRet = pRet->pLeft;
    } else {
        pRet = pRoot;
        while(pRet->pRight != NULL) 
            pRet = pRet->pRight;
    }

    return pRet;

}


void Insert(struct BinarySearchTree* pTree, int value) {
    struct BinaryTreeNode* pNode = pTree->pRoot;
    struct BinaryTreeNode* pInsert = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    struct BinaryTreeNode* pParent = NULL;
    pInsert->value = value;

    //find proper node to insert
    while(pNode != NULL) {
        pParent = pNode;
        if (pInsert->value < pNode->value) 
            pNode = pNode->pLeft;
        else pNode = pNode->pRight;
    }

    pInsert->pParent = pParent;
    
    //pInsert is left child or right child of pParent
    if (pParent == NULL) pTree->pRoot = pInsert;
    else if (pInsert->value < pParent->value) pParent->pLeft = pInsert;
    else pParent->pRight = pInsert;

    
}

void PrintList(struct BinaryTreeNode* pRoot) {
    while(pRoot != NULL) {
        printf("%d\t", pRoot->value);
        pRoot = pRoot->pRight;
    }
    printf("\n");
}

void DeleteList(struct BinaryTreeNode* pRoot) {
    struct BinaryTreeNode* pDel = pRoot;
    while(pRoot != NULL) {
        pRoot = pRoot->pRight;
        free(pDel);
        pDel = pRoot;
    }
}
