#include "Tree.h"
#include "IntCompare.h"
#include <stdexcept>
#include <iostream>


int main()
{
    if (IntCompare()(1, 3))
    {
        std::cout << "Intcompare test passed." << std::endl;
    }
    else
    {
        throw std::runtime_error("IntCompare Failed.");
    }  // Intcompare test passed.
    

    // Tree tests =========================================
    Tree<int, IntCompare> nt;
    int bound = 100;

    for (int i=7; i>0; --i)
    {
        std::cout << "inserting: " << i << std::endl;
        nt.insert(i);
        nt.insert(bound -i);
        nt.debug_print();  // total heap usage: 32 allocs, 32 frees, 78,240 bytes allocated
    }

    // nt.debug_print();

    Tree<int, IntCompare>::iterator it;
    for (it=nt.begin(); it!=nt.end(); ++it)
    {
        std::cout << "elem: " << *it << std::endl;
    }

    std::for_each(titleIndex.begin(), titleIndex.end(), printSong);
}