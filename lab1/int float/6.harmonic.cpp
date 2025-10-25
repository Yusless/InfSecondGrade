#include <iostream>
#include <cmath>
using namespace std;
int main() {
    float sum = 0.0f;
    int k = 0;
    
    // Ищем момент, когда прибавление не увеличивает сумму
    for (int n = 1; n <= 10000000; n++) {
        float old_sum = sum;
        sum += 1.0f / n;
        
        if (sum == old_sum) {
            k = n;
            cout << "First element not to get the summ higher: k = " << k << endl;
            cout << "1/" << k << " = " << 1.0f/k << endl;
            cout << "sum k: " << old_sum << endl;
            break;
        }
    }

    
    // Суммируем до k + 100
    cout << "\nsumm till k + 100:" << endl;
    float sum_forward = 0.0f;
    for (int n = 1; n <= k + 100; n++) {
        sum_forward += 1.0f / n;
    }
    cout << "Summ: " << sum_forward << endl;
    
    // Суммируем в обратном порядке
    cout << "Summ till k + 100 reverse:" << endl;
    float sum_backward = 0.0f;
    for (int n = k + 100; n >= 1; n--) {
        sum_backward += 1.0f / n;
    }
    cout << "Summ: " << sum_backward << endl;
    
    cout << "Diff: " << fabs(sum_forward - sum_backward) << endl;
}