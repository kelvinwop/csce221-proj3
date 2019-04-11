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
    int child_type;  // -1 left child, 0 middle child, 1 right child, 2 root node
    
};

#endif
