#include "Tree.h"

#ifndef TREE_CPP
#define TREE_CPP

/* Stubs for the tree's methods */

template <typename DataType, typename Compare>
Tree<DataType, Compare>::Tree()
{
    root = nullptr;
    tree_size = 0;
}

template <typename DataType, typename Compare>
Tree<DataType, Compare>::Tree(const Tree<DataType, Compare> &other)
{
    root = copy_node(other)
}

template <typename DataType, typename Compare>
Tree<DataType, Compare> &
Tree<DataType, Compare>::operator=(const Tree<DataType, Compare> &other)
{
    /* Your code here... */    
}

template <typename DataType, typename Compare>
Tree<DataType, Compare>::~Tree()
{
    /* Your code here... */    
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::insert(DataType data)
{
    ++tree_size;

    // TODO: implement
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::empty() const
{
    /* Your code here... */    
    return false;
}

template <typename DataType, typename Compare>
size_t Tree<DataType, Compare>::size() const
{
    /* Your code here... */    
    return tree_size;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator Tree<DataType, Compare>::begin()
{
    /* Your code here... */    
    return iterator();
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator Tree<DataType, Compare>::end()
{
    /* Your code here... */    
    return iterator();
}

template <typename DataType, typename Compare>
template <typename KeyType>
typename Tree<DataType, Compare>::iterator 
Tree<DataType, Compare>::find_first(KeyType key)
{
    /* Your code here... */    
    return iterator();
}

template <typename DataType, typename Compare>
template <typename KeyType>
typename Tree<DataType, Compare>::iterator 
Tree<DataType, Compare>::find_last(KeyType key)
{
    /* Your code here... */    
    return iterator();
}

template <typename DataType, typename Compare>
template <typename KeyType>
std::pair<typename Tree<DataType, Compare>::iterator,
          typename Tree<DataType, Compare>::iterator>
Tree<DataType, Compare>::find_range(KeyType key)
{
    /* Your code here... */
    return std::make_pair(iterator(), iterator());
}

template <typename DataType, typename Compare>
std::ostream &operator<<(std::ostream &stream,
                         const Tree<DataType, Compare> &tree)
{
    /* Your code here... */
    return stream;
}

template <typename DataType, typename Compare>
Node<DataType> Tree<DataType, Compare>::copy_node(Node<DataType>* other, Node<DataType>* parent)
{
    if (other == nullptr)
    {
        return nullptr;
    }

    Node<DataType>* out = new Node<DataType> {
        nullptr,
        nullptr,
        nullptr,
        &parent,
        other.value1,
        other.value2,
        other.keys
    };
    out.left = copy_node(other.left, out);
    out.middle = copy_node(other.middle, out);
    out.right = copy_node(other.right, out);
    return out;
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::delete_node(Node<DataType>* other)
{
    if (other == nullptr)
    {
        return;
    }
    delete_node(other->left);
    delete_node(other->middle);
    delete_node(other->right);
    delete other;
}


#endif
