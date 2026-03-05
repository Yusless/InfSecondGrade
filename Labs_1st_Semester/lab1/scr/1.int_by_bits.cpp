#include <iostream>
using namespace std;

void int_to_bits(int num) {
    unsigned int mask = 1 << (sizeof(int) * 8 - 1);  //создадим маску как "1" и 31 "0"
    
    cout << "Num " << num << " in memory ";
    
    for (int i = 0; i < sizeof(int) * 8; i++) {
        cout << ((num & mask) ? 1 : 0); // проходимся побитовым "и" маской по числу, каждый раз побитово сдвигая вправо 1 в маске
        mask >>= 1;
        
        if ((i + 1) % 8 == 0 && i != sizeof(int) * 8 - 1) { // для удобства разделим байты пробелом
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    int n = 2147483647; // max int
    int_to_bits(n);
    n = 1;
    int_to_bits(n);    
    n = -1;
    int_to_bits(n);
    n = -128;
    int_to_bits(n);
    // max int это 2^31, и в отрицательных числах первый бит 1, в положительных - 0. также видно, что для представления в памяти отрицательных чисел используется "дополнительный код"
    n = -2147483648;
    int_to_bits(n);
    n = 2147483648;
    int_to_bits(n); // если переехать через maxint, то получится минимальное число
    return 0;
}