
#ifndef TREE_H_
#define TREE_H_

typedef struct Node* Node;

extern Node newNode(char* data);
extern void freeNode(Node this);
extern void freeSingleNode(Node this);
extern char* getDataNode(Node this);
extern Node getLeftChild(Node this);
extern Node getRightSibling(Node this);

extern void insertNode(Node this, Node add);
extern void insertRightNode(Node this, Node add);

typedef struct Tree* Tree;

extern Tree newTree(void);
extern void freeTree(Tree this);

extern void insertRootTree(Tree this, Node new);
extern Node makeNode1(char* data, Node n1);
extern Node makeNode2(char* data, Node n1, Node n2);
extern Node makeNode3(char* data, Node n1, Node n2, Node n3);

extern void printNode(Node this, int indent);
extern void printTree(Tree this);

extern Tree parseToExpression(Tree this);
extern Node nodeToExpression(Node this);

extern int comparePrecedenceNode(Node left, Node right);
extern Node eliminateParenthesesExpression(Node this);

extern void printExpressionNode(Node this);
extern void printExpressionTree(Tree this);

#endif /* TREE_H_ */
