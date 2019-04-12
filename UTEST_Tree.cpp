#include "Tree.h"
#include "IntCompare.h"
#include <stdexcept>
#include <iostream>
#include <time.h>


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
    srand(time(NULL));
    int randint;

    for (int i=100; i>0; --i)
    {
        randint = rand() % 35 + 1;
        std::cout << "inserting: " << randint << std::endl;
        nt.insert(randint);
        nt.debug_print();  // total heap usage: 32 allocs, 32 frees, 78,240 bytes allocated

        std::cout << "ord: ";
        Tree<int, IntCompare>::iterator it;
        for (it=nt.begin(); it!=nt.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    // nt.debug_print();

    Tree<int, IntCompare>::iterator it;
    for (it=nt.begin(); it!=nt.end(); ++it)
    {
        std::cout << "elem: " << *it << std::endl;
    }
}