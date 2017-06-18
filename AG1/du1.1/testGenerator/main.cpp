#include <iostream>
#include "time.h"

using namespace std;

char key()
{
    int k = rand() % 4;
    switch (k)
    {
        case 0:
            return 'x';
        case 1:
            return 'a';
        case 2:
            return 'b';
        case 3:
            return 'c';
    }
    return 'x';
};

char card()
{
    int k = rand() % 3;
    switch (k)
    {
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
    }
    return 'a';
}

int main() {
    size_t vert;
    size_t edge;

    cin >> vert >> edge;

    srand( time(0) );

    cout << vert << ' ' << rand() % (vert/2) << ' ' << (vert/2) + (rand() % (vert/2));
    cout << endl;

    for ( int i = 0; i < vert; i++ )
    {
        size_t en = rand() % edge;
        cout << en << ' ';
        for ( size_t j = 0; j < en; j++ )
        {
            size_t n = rand() % vert;
            cout << n << ' ' << key() << ' ';
        }
        cout << endl;
    }

    size_t c = rand() % (vert * 2);
    cout << c << ' ';

    for ( size_t i = 0; i < c; i++ )
    {
        size_t n = rand() % vert;
        cout << n << ' ' << card() << ' ';
    }
    cout << endl;

    return 0;
}