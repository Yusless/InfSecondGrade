
#include <iostream>
#include <cmath>
using namespace std;
union Float {
    float f;
    unsigned int i;
};
float next_float(float f) { // брутально добавляем 1 к флоту, добавляя к нему 1 * 2^exp.
    Float converter;
    converter.f = f;
    
    if (f >= 0) {
        converter.i++;
    } else {
        converter.i--;
    }
    
    return converter.f;
}

int main() {
    cout << "=== ПОИСК ЧИСЕЛ С РАССТОЯНИЕМ 1 ===" << endl;
    
    float a = 1.0f;
    float b = next_float(a);
    
    while (b - a < 1.0f) { //становится понятно, что разница между числами в 1 будет при exp = 23, то есть число 2^23
        a = b;
        b = next_float(a);
    }
    
    cout << "first nums with dist >= 1:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "b - a = " << b - a << endl;
    
    float x = 1.0f; // a результат сложения "возвращаться" назад, если пропасть между числами равна 2, то есть при числе 2^24
    while (x != x + 1.0f) {
        x *= 2.0f;
    }
    
    cout << "\nnum x0, where x == x + 1:" << endl;
    cout << "x0 ≈ " << x << endl;
    cout << "check: " << x << " + 1 = " << x + 1.0f << endl;
    cout << "equal? " << (x == x + 1.0f ? "ya" : "nah") << endl;
    return 0;
}