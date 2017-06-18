#include <iostream>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL));
    size_t n;
    
    cin >> n;
    cout << n << endl;
    for ( size_t i = 0; i < n; i++ ) {
        size_t b = rand() % 100;
        size_t e = b + rand() % 100 + 1;
        size_t p = rand() % 100;
        cout << b << " " << e << " " << p << endl;
    }
    
    return 0;
}