#include "Tree.h"
#include <stdexcept>

#ifndef TREE_ITERATOR_CPP
#define TREE_ITERATOR_CPP

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
Tree<DataType, Compare>::iterator::iterator(Node<DataType>* elem, int idx)
{
    this->cur_point = elem;
    this->key_num = idx;
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
    return this->cur_point == other.cur_point && this->key_num == other.key_num;
}

template <typename DataType, typename Compare>
bool Tree<DataType, Compare>::iterator::operator!=(const iterator &other) const
{
    return this->cur_point != other.cur_point || this->key_num != other.key_num;
}

template <typename DataType, typename Compare>
DataType Tree<DataType, Compare>::iterator::operator*() const
{
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
        // case 1, 2
        if (this->cur_point->keys == 1)  // two-tree
        {
            if (key_num == 2)
            {
                throw std::runtime_error("ASSUMPTIONS BROKEN: key_num must be 1 here");
            }
            // case 1
            if (this->cur_point->right != nullptr)
            {
                this->cur_point = get_leftmost(this->cur_point->right);
                return *this;
            }

            // case 2
            while (this->cur_point->parent != nullptr)
            {
                if (this->cur_point->child_type == -1)  // is a left child
                {
                    this->cur_point = this->cur_point->parent;
                    // smaller in parent so key stays 1
                    return *this;
                }
                else if (this->cur_point->child_type == 0)  // middle child
                {
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
            if (key_num == 1)
            {
                // case 3
                if (this->cur_point->middle != nullptr)
                {
                    this->cur_point = get_leftmost(this->cur_point->middle);
                    // smallest so key stays 1
                    return *this;
                }

                // case 5
                else
                {
                    key_num = 2;
                    return *this;
                }
            }
            else if (key_num == 2)
            {
                // case 4
                if (this->cur_point->right != nullptr)
                {
                    this->cur_point = get_leftmost(this->cur_point->right);
                    key_num = 1;
                    return *this;
                }

                // case 6
                while (this->cur_point->parent != nullptr)
                {
                    if (this->cur_point->child_type == -1)  // is a left child
                    {
                        this->cur_point = this->cur_point->parent;
                        key_num = 1;
                        return *this;
                    }
                    else if (this->cur_point->child_type == 0)  // middle child
                    {
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
    if (cur_point->left == nullptr)
    {
        return cur_point;
    }
    return get_leftmost(cur->left);
}

template <typename DataType, typename Compare>
Node<DataType>* Tree<DataType, Compare>::iterator::get_rightmost(Node<DataType>* cur)
{
    if (cur_point->left == nullptr)
    {
        return cur_point;
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
