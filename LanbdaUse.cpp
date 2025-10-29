#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int b = 20;
    
    auto lambda = [a, &b]() mutable {
        a += 5;
        b += 5;
        cout << "inside lambda: a = " << a << ", b = " << b << "\n";
    };
    lambda();
    
    cout << "After lambda: a = " << a << ", b = " << b << "\n";
    
    return 0;
}