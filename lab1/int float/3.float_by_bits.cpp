#include <iostream>
#include <cmath>
using namespace std;

union Float {
    float f;
    unsigned int i;
};

void float_to_bits(float f) {
    Float conv;
    conv.f = f;
    unsigned int bits = conv.i;
    
    cout << "num: " << f << endl;
    cout << "bits: ";

    for (int i = 31; i >= 0; i--) { // первый бит - знак, следующие 8 - экспонента и 23 - мантисса.
        cout << ((bits >> i) & 1);
        if (i == 31) cout << " ";
        if (i == 23) cout << " ";
    }
    cout << endl;
    
    unsigned int sign = (bits >> 31) & 1; // означает знак, 0 - положительное, 1 - отрицательное
    unsigned int exp = (bits >> 23) & 255; //2^8-1, означает степень двойки, на которую умножается конечное число
    unsigned int mantiss = bits & 8388607; //2^23-1, означает дробную часть от числа, которую надо умножить на степень двойки
    
    cout << "mantiss: " << mantiss << endl;
    
    int real_exp = (int)exp - 127;
    float real_mantiss = 1.0f + (float)mantiss / (1 << 23);
    
    cout << "real exp: " << real_exp << endl;
    cout << "real mantiss: " << real_mantiss << endl;
    cout << "Value: " << (sign ? "-" : "") << real_mantiss << " * 2^" << real_exp << endl;
}

int main() {
    float n = 0.3254f;  // 1/2
    float_to_bits(n);
    n = 0.25f; // 1/4
    float_to_bits(n);
    n = -0.25f;// -1/4
    float_to_bits(n); 
    return 0;
}