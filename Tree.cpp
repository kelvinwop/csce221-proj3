#include "Tree.h"
#include <stdexcept>
#include <iostream>

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
    root = copy_node(other);
    tree_size = other.size();
}

template <typename DataType, typename Compare>
Tree<DataType, Compare> &
Tree<DataType, Compare>::operator=(const Tree<DataType, Compare> &other)
{
    delete_node(root);
    root = copy_node(other);
    tree_size = other.size();
    return *this; 
}

template <typename DataType, typename Compare>
Tree<DataType, Compare>::~Tree()
{
    delete_node(root); 
    tree_size = 0;
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::insert(DataType data)
{
    ++tree_size;

    if (root == nullptr)
    {
        #ifdef DEBUG
        std::cout << "ALLOC root" << std::endl;
        #endif
        root = new Node<DataType> {
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            DataType(),
            DataType(),
            0,
            2
        };
    }
    insert(root, data);    
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::debug_print()
{
    dp_internal(root, 0);
    std::cout << std::endl;
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::dp_internal(Node<DataType>* cur, int level)
{
    for (int i=0; i<level; ++i)
    {
        std::cout << "    ";
    }
    if (cur == nullptr)
    {
        std::cout << "NULL" << std::endl;
        return;
    }
    if (cur->keys == 1)
    {
        std::cout << "childtype: " << cur->child_type << ", value: " << cur->value1 << ", parent: ";
        if (cur->parent == nullptr)
        {
            std::cout << "NULL" << std::endl;
        }
        else
        {
            std::cout << cur->parent->value1 << std::endl;
        }
    }
    else if (cur->keys == 2)
    {
        std::cout << "childtype: " << cur->child_type << ", value1: " << cur->value1 << ", value2: " << cur->value2 << ", parent: ";
        if (cur->parent == nullptr)
        {
            std::cout << "NULL" << std::endl;
        }
        else
        {
            std::cout << cur->parent->value1 << std::endl;
        }
    }
    dp_internal(cur->left, level + 1);
    dp_internal(cur->middle, level + 1);
    dp_internal(cur->right, level + 1);
}

template <typename DataType, typename Compare>
void Tree<DataType, Compare>::insert(Node<DataType>* ins_pt, DataType ins_val)
{
    // TODO: before inserts, check if nullptr and create a node if it is nullptr
    // TODO: set childtype
    // inserting into root node
    if (ins_pt->left == nullptr && ins_pt->middle == nullptr && ins_pt->right == nullptr)
    {
        if (ins_pt->keys == 0)
        {
            ins_pt->keys = 1;
            ins_pt->value1 = ins_val;
            return;
        }
        else
        {
            #ifdef DEBUG
            std::cout << "Inserting into leaf node with keys" << std::endl;
            #endif
            
            #ifdef DEBUG
            std::cout << "ALLOC temp" << ins_val << std::endl;
            #endif
            Node<DataType>* temp = new Node<DataType> {
                nullptr,
                nullptr,
                nullptr,
                ins_pt->parent,  // parents should be the same
                ins_val,
                DataType(),
                1,
                -2  // unknown
            };
            insert_up(ins_pt, temp);
        }
    }

    // not leaf with one key
    else if (ins_pt->keys == 1)
    {
        if (Compare()(ins_val, ins_pt->value1))  // if inserted value is less than current (ins left)
        {
            insert(ins_pt->left, ins_val);
            return;
        }
        else  // if inserted value is greater than or equal to current (ins right)
        {
            insert(ins_pt->right, ins_val);
            return;
        }
    }

    // not leaf with two keys
    else if (ins_pt->keys == 2)
    {
        if (Compare()(ins_val, ins_pt->value1))  // if inserted value is less than current1 (ins left)
        {
            insert(ins_pt->left, ins_val);
            return;
        }
        else if (Compare()(ins_val, ins_pt->value1))  // if inserted value is less than current2 (ins middle)
        {
            insert(ins_pt->middle, ins_val);
            return;
        }
        else  // if inserted value is greater than or equal to current (ins right)
        {
            insert(ins_pt->right, ins_val);
            return;
        }
    }

    // idk how you got here
    else
    {
        throw std::runtime_error("ERROR: Unsupported operation");
    }
    
}

// -2 leaf op, -1 left child, 0 middle child, 1 right child, 2 root node
template <typename DataType, typename Compare>
void Tree<DataType, Compare>::insert_up(Node<DataType>* ins_pt, Node<DataType>* inserting)
{
    // leaf with one key on first run, branches after
    if (ins_pt->keys == 1)  // TODO: add cases for insertion into one key (remember delete)
    {
        if (Compare()(inserting->value1, ins_pt->value1))  // if inserted value is less than current (ins left)
        {
            if (ins_pt->left == nullptr && ins_pt->middle == nullptr && ins_pt->right == nullptr)
            {
                ins_pt->value2 = ins_pt->value1;
                ins_pt->value1 = inserting->value1;
                ins_pt->keys = 2;
                #ifdef DEBUG
                std::cout << "DEALLOC" << ins_pt->value1 << std::endl;
                #endif
                delete inserting;
                return;
            }
            else
            {
                ins_pt->value2 = ins_pt->value1;
                ins_pt->value1 = inserting->value1;
                ins_pt->keys = 2;
                ins_pt->left = inserting->left;
                ins_pt->left->child_type = -1;
                ins_pt->left->parent = ins_pt;
                ins_pt->middle = inserting->right;
                ins_pt->middle->child_type = 0;
                ins_pt->middle->parent = ins_pt;
                #ifdef DEBUG
                std::cout << "DEALLOC" << ins_pt->value1 << std::endl;
                #endif
                delete inserting;
                return;
            }
        }
        else  // if inserted value is greater than or equal to current (ins right)
        {
            if (ins_pt->left == nullptr && ins_pt->middle == nullptr && ins_pt->right == nullptr)
            {
                ins_pt->value2 = inserting->value1;
                ins_pt->keys = 2;
                #ifdef DEBUG
                std::cout << "DEALLOC" << ins_pt->value2 << std::endl;
                #endif
                delete inserting;
                return;
            }
            else
            {
                ins_pt->value2 = inserting->value1;
                ins_pt->keys = 2;
                ins_pt->middle = inserting->left;
                ins_pt->middle->child_type = 0;
                ins_pt->middle->parent = ins_pt;
                ins_pt->right = inserting->right;
                ins_pt->right->child_type = 1;
                ins_pt->right->parent = ins_pt;
                #ifdef DEBUG
                std::cout << "DEALLOC" << ins_pt->value2 << std::endl;
                #endif
                delete inserting;
                return;
            }
        }
    }

    // leaf with two keys on first run, branches after
    else if (ins_pt->keys == 2)
    {
        DataType smol;
        DataType med;
        DataType big;
        if (Compare()(inserting->value1, ins_pt->value1))  // if inserted value is less than current1 (ins left)
        {
            smol = inserting->value1;
            med = ins_pt->value1;
            big = ins_pt->value2;
        }
        else if (Compare()(inserting->value1, ins_pt->value1))  // if inserted value is less than current2 (ins middle)
        {
            smol = ins_pt->value1;
            med = inserting->value1;
            big = ins_pt->value2;
        }
        else  // if inserted value is greater than or equal to current (ins right)
        {
            smol = ins_pt->value1;
            med = ins_pt->value2;
            big = inserting->value1;
        }
        ins_pt->value1 = smol;

        Node<DataType>* child1;
        Node<DataType>* child2;
        Node<DataType>* child3;
        Node<DataType>* child4;
        if (inserting->child_type == -2)
        {
            child1 = nullptr;
            child2 = nullptr;
            child3 = nullptr;
            child4 = nullptr;
        }
        else if (inserting->child_type == -1)  // left insert, child order: left, temp, middle, right
        {
            child1 = inserting->left;
            child2 = inserting->right;
            child3 = ins_pt->middle;
            child4 = ins_pt->right;
        }
        else if (inserting->child_type == 0)  // middle insert, child order: left, middle, temp, right
        {
            child1 = ins_pt->left;
            child2 = inserting->left;
            child3 = inserting->right;
            child4 = ins_pt->right;
        }
        else if (inserting->child_type == 1)  // right insert, child order: left, middle, right, temp
        {
            child1 = ins_pt->left;
            child2 = ins_pt->middle;
            child3 = inserting->left;
            child4 = inserting->right;
        }
        else
        {
            throw std::runtime_error("ILLEGAL CHILD TYPE");
        }
               

        #ifdef DEBUG
        std::cout << "ALLOC rhs" << big << std::endl;
        #endif
        // setup supercluster
        Node<DataType>* RHS = new Node<DataType> {  // rhs big one
            child3,
            nullptr,  // no middle
            child4,
            nullptr,  // parent set below
            big,  // always the big one
            DataType(),
            1,  // always has one key
            1  // always a right child
        };

        #ifdef DEBUG
        std::cout << "ALLOC supercluster" << med << std::endl;
        #endif
        Node<DataType>* supercluster = new Node<DataType> {  // newly split 3-group
            ins_pt,
            nullptr,  // no middle
            RHS,
            ins_pt->parent,  // set parent to store, will change
            med,
            DataType(),
            1,  // always has one key
            ins_pt->child_type
        };
        ins_pt->parent = supercluster;
        RHS->parent = supercluster;
        ins_pt->child_type = -1;  // left child always
        ins_pt->left = child1;
        ins_pt->right = child2;

        if (inserting->child_type != -2)
        {
            child1->parent = ins_pt;
            child2->parent = ins_pt;
            child3->parent = RHS;
            child4->parent = RHS;
            child1->child_type = -1;
            child2->child_type = 1;
            child3->child_type = -1;
            child4->child_type = 1;
        }

        ins_pt->middle = nullptr;
        ins_pt->keys = 1;  // always has one key


        #ifdef DEBUG
        std::cout << "DEALLOC" << inserting->value1 << std::endl;
        #endif
        delete inserting;

        if (supercluster->parent != nullptr)
        {
            insert_up(supercluster->parent, supercluster);
            return;
        }
        else
        {
            root = supercluster;
            if (supercluster->child_type != 2)
            {
                throw std::runtime_error("ASSUMPTIONS BROKEN: root has wrong child_type??");
            }
        }
    }

    else
    {
        throw std::runtime_error("no conditions hit???");
    }
    
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::empty() const
{
    return tree_size == 0;
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
    typename Tree<DataType, Compare>::iterator it;
    it.cur_point = iterator::get_leftmost(this->root);
    it.key_num = 1;
    return it;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator Tree<DataType, Compare>::end()
{
    return typename Tree<DataType, Compare>::iterator();
}

template <typename DataType, typename Compare>
template <typename KeyType>
typename Tree<DataType, Compare>::iterator 
Tree<DataType, Compare>::find_first(KeyType key)
{
    Tree<DataType, Compare>::iterator it;
    for (it = iterator().begin(); it < iterator().end(); ++it)
    {
        if (*it == key)
        {
            return it;
        }
    }
    return iterator().end();
}

template <typename DataType, typename Compare>
template <typename KeyType>
typename Tree<DataType, Compare>::iterator 
Tree<DataType, Compare>::find_last(KeyType key)
{
    Tree<DataType, Compare>::iterator trailing = iterator().end();
    Tree<DataType, Compare>::iterator it;
    for (it = iterator().begin(); it < iterator().end(); ++it)
    {
        if (*it == key)
        {
            trailing = it;
        }
    }
    return trailing;
}

template <typename DataType, typename Compare>
template <typename KeyType>
std::pair<typename Tree<DataType, Compare>::iterator,
          typename Tree<DataType, Compare>::iterator>
Tree<DataType, Compare>::find_range(KeyType key)
{
    Tree<DataType, Compare>::iterator first = iterator().end();
    Tree<DataType, Compare>::iterator trailing = iterator().end();
    Tree<DataType, Compare>::iterator it;
    for (it = iterator().begin(); it < iterator().end(); ++it)
    {
        if (*it == key)
        {
            trailing = it;
            if (first == iterator().end())
            {
                first = it;
            }
        }
    }
    return trailing;
    return std::make_pair(first, trailing);
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

    #ifdef DEBUG
    std::cout << "ALLOC copy" << other.value1 << std::endl;
    #endif
    Node<DataType>* out = new Node<DataType> {
        nullptr,
        nullptr,
        nullptr,
        &parent,
        other.value1,
        other.value2,
        other.keys,
        other.child_type
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
    #ifdef DEBUG
    std::cout << "DEALLOC delete_node" << other->value1 << std::endl;
    #endif
    delete other;
}

#endif
