#ifndef INT_COMPARE_H
#define INT_COMPARE_H

/* Declaration of the comparison functor for use with the Title index */

struct IntCompare
{
    /* 
     * Return whether or not int a is 
     * worth less than int b
     */
    bool operator()(const int a, const int b);
};

#endif
