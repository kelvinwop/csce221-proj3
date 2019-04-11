#include "Tree.h"
#include <stdexcept>
#include <iostream>

#ifndef TREE_ITERATOR_CPP
#define TREE_ITERATOR_CPP
// #define DEBUG

template <typename DataType, typename Compare>
Tree<DataType, Compare>::iterator::iterator()
{
    cur_point = nullptr;
    key_num = 1;
}

template <typename DataType, typename Compare>
Tree<DataType, Compare>::iterator::iterator(const iterator &other)
{
    this->cur_point = other.cur_point;
    this->key_num = other.key_num;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator &
Tree<DataType, Compare>::iterator::operator=(const iterator &other)
{
    this->cur_point = other.cur_point;
    this->key_num = other.key_num;
    return *this;
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::iterator::operator==(const iterator &other) const
{
    if (this->cur_point == nullptr && other.cur_point == nullptr)
    {
        return true;
    }
    return this->cur_point == other.cur_point && this->key_num == other.key_num;
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::iterator::operator!=(const iterator &other) const
{
    return !(*this == other);
}

template <typename DataType, typename Compare>
DataType Tree<DataType, Compare>::iterator::operator*() const
{
    #ifdef DEBUG
    if (this->cur_point == nullptr)
    {
        std::cout << "*() op NULL" << std::endl;
    }
    else
    {
        std::cout << "*() nonnull" << std::endl;
    }
    #endif
    if (this->key_num == 1)
    {
        return this->cur_point->value1;
    }
    else if (this->key_num == 2)
    {
        return this->cur_point->value2;
    }
    else
    {
        throw std::runtime_error("Invalid iterator.key_num value: " + std::to_string(this->key_num) + "Expected: [1 or 2]");
    }
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator &
Tree<DataType, Compare>::iterator::operator++()  // pre-increment
{
    if (this->cur_point != nullptr)
    {
        #ifdef DEBUG
        std::cout << "iterator is not at the end" << std::endl;
        #endif
        // case 1, 2
        if (this->cur_point->keys == 1)  // two-tree
        {
            #ifdef DEBUG
            std::cout << "this is a one key node" << std::endl;
            #endif
            if (key_num == 2)
            {
                throw std::runtime_error("ASSUMPTIONS BROKEN: key_num must be 1 here");
            }
            // case 1
            if (this->cur_point->right != nullptr)
            {
                #ifdef DEBUG
                std::cout << "this node has a right branch... getting leftmost on right branch" << std::endl;
                #endif
                this->cur_point = get_leftmost(this->cur_point->right);
                return *this;
            }

            // case 2
            while (this->cur_point->parent != nullptr)
            {
                #ifdef DEBUG
                std::cout << "this node has a parent" << std::endl;
                #endif
                if (this->cur_point->child_type == -1)  // is a left child
                {
                    #ifdef DEBUG
                    std::cout << "this node is a left child (no right branch), traversing up" << std::endl;
                    #endif
                    this->cur_point = this->cur_point->parent;
                    // smaller in parent so key stays 1 (going to left parent)
                    return *this;
                }
                else if (this->cur_point->child_type == 0)  // middle child
                {
                    #ifdef DEBUG
                    std::cout << "this node is a middle child, traversing up" << std::endl;
                    #endif
                    this->cur_point = this->cur_point->parent;
                    key_num = 2;
                    return *this;
                }
                this->cur_point = this->cur_point->parent;
            }

            // we are biggest element
            this->cur_point = nullptr;
            return *this;
        }

        // case 3, 4, 5, 6
        else if (this->cur_point->keys == 2)  // three-tree
        {
            #ifdef DEBUG
            std::cout << "this node has two key values" << std::endl;
            #endif
            if (key_num == 1)
            {
                #ifdef DEBUG
                std::cout << "currently on smaller of two keys" << std::endl;
                #endif
                // case 3
                if (this->cur_point->middle != nullptr)
                {
                    #ifdef DEBUG
                    std::cout << "traversing down the central branch" << std::endl;
                    #endif
                    this->cur_point = get_leftmost(this->cur_point->middle);
                    // smallest so key stays 1
                    return *this;
                }

                // case 5
                else
                {
                    #ifdef DEBUG
                    std::cout << "this node has no central branch" << std::endl;
                    #endif
                    key_num = 2;
                    return *this;
                }
            }
            else if (key_num == 2)
            {
                // case 4
                if (this->cur_point->right != nullptr)
                {
                    #ifdef DEBUG
                    std::cout << "a right subtree exists... getting left most on right branch" << std::endl;
                    #endif
                    this->cur_point = get_leftmost(this->cur_point->right);
                    key_num = 1;
                    return *this;
                }

                // case 6
                while (this->cur_point->parent != nullptr)
                {
                    #ifdef DEBUG
                    std::cout << "this node has a parent" << std::endl;
                    #endif
                    if (this->cur_point->child_type == -1)  // is a left child
                    {
                        #ifdef DEBUG
                        std::cout << "this node is a left child, traversing up" << std::endl;
                        #endif
                        this->cur_point = this->cur_point->parent;
                        key_num = 1;
                        return *this;
                    }
                    else if (this->cur_point->child_type == 0)  // middle child
                    {
                        #ifdef DEBUG
                        std::cout << "this node is a middle child, traversing up" << std::endl;
                        #endif
                        this->cur_point = this->cur_point->parent;
                        // larger in parent so key stays 2
                        return *this;
                    }
                    this->cur_point = this->cur_point->parent;
                }

                // we are biggest element
                this->cur_point = nullptr;
                return *this;
            }
        }

        // exception
        else
        {
            throw std::runtime_error("Invalid node.keys value: " + std::to_string(this->cur_point->keys) + "Expected: [1 or 2]");
        }
    }
    else
    {
        throw std::runtime_error("Incremented an iterator at end.");
    }
    
    
    return *this;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator
Tree<DataType, Compare>::iterator::operator++(int unused)  // post-increment
{
    ++(*this);
    return *this;
}

template <typename DataType, typename Compare>
Node<DataType>* Tree<DataType, Compare>::iterator::get_leftmost(Node<DataType>* cur)
{
    if (cur->left == nullptr)
    {
        return cur;
    }
    return get_leftmost(cur->left);
}

template <typename DataType, typename Compare>
Node<DataType>* Tree<DataType, Compare>::iterator::get_rightmost(Node<DataType>* cur)
{
    if (cur->right== nullptr)
    {
        return cur;
    }
    return get_leftmost(cur->left);
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator &
Tree<DataType, Compare>::iterator::endify()
{
    this->cur_point = nullptr;
    return *this;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator &
Tree<DataType, Compare>::iterator::startify()
{
    // traverse up to root
    while (cur_point->parent != nullptr)
    {
        this->cur_point = this->cur_point->parent;
    }

    // traverse down to leftmost
    this->cur_point = get_leftmost(this->cur_point);
    return *this;
}

template <typename DataType, typename Compare>
typename Tree<DataType, Compare>::iterator &
Tree<DataType, Compare>::iterator::lastify()
{
    // traverse up to root
    while (cur_point->parent != nullptr)
    {
        this->cur_point = this->cur_point->parent;
    }

    // traverse down to rightmost
    this->cur_point = get_rightmost(this->cur_point);
    return *this;
}

#endif
