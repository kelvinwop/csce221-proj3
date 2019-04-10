#ifndef NODE_H
#define NODE_H

/* Node structure for use in 2-3 trees */
template <typename DataType>
struct Node
{
    Node<DataType>* left;
    Node<DataType>* middle;
    Node<DataType>* right;
    Node<DataType>* parent;
    DataType value1;
    DataType value2;
    int keys;  // 1 is a two-tree, 2 is a three-tree
};

#endif
