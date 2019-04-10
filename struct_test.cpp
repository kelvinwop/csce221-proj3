#include <iostream>

using namespace std;

struct blah
{
    int x;
    int y;
    int z;
};

int get_x(blah &b)
{
    return b.x;
}

int main()
{
    blah* a = new blah {
        5,
        10,
        15
    };

    cout << get_x(*a) << endl;
    delete a;
}