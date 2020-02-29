#include "RedBlackTree.h"

RBTreeNode::RBTreeNode(int key) : key(key), color(COLOR_RED), parent(nullptr), left(nullptr), right(nullptr)
{
}