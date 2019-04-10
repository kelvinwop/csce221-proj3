#include "Tree.h"
#include <stdexcept>

#ifndef TREE_ITERATOR_CPP
#define TREE_ITERATOR_CPP

template <typename DataType, typename Compare>
Tree<DataType, Compare>::iterator::iterator()
{
    cur_point = root;
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
    // case 1, 2
    if (this->cur_point->keys == 1)  // two-tree
    {

    }

    // case 3, 4, 5, 6
    else if (this->cur_point->keys == 2)  // three-tree
    {

    }

    // exception
    else
    {
        throw std::runtime_error("Invalid node.keys value: " + std::to_string(this->cur_point->keys) + "Expected: [1 or 2]");
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


#endif
