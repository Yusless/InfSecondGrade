#include <iostream>
using namespace std;

void un_int_to_bits(unsigned int num) {
    unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
    
    cout << "Num " << num << " in memory ";
    
    for (int i = 0; i < sizeof(unsigned int) * 8; i++) {
        cout << ((num & mask) ? 1 : 0);
        mask >>= 1;
        
        if ((i + 1) % 8 == 0 && i != sizeof(unsigned int) * 8 - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    unsigned int n = 2147483647;
    un_int_to_bits(n);
    n = 1;
    un_int_to_bits(n);
    n = -1; // этот минибро не воспринимает отрицательные числа, и вместо -1 пишет max unsigned int (что фактически 0 - 1)
    un_int_to_bits(n);
    n = 2147483648; // теперь maxint + 1 побитово это 1 и 31 ноль
    un_int_to_bits(n);
    return 0;
}