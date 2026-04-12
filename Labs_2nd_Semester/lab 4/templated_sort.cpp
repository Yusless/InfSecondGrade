#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <cmath>
#include <iterator>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

template< typename RandomAccessIterator, typename Compare >
void merge(RandomAccessIterator first, 
           RandomAccessIterator mid, 
           RandomAccessIterator last, 
           Compare comp)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    
    auto dist_left = std::distance(first, mid);
    auto dist_right = std::distance(mid, last);
    
    ValueType* leftArr = new ValueType[dist_left];
    ValueType* rightArr = new ValueType[dist_right];

    ValueType* leftPtr = leftArr;
    for (auto it = first; it != mid; ++it, ++leftPtr) {
        *leftPtr = *it;
    }
    
    ValueType* rightPtr = rightArr;
    for (auto it = mid; it != last; ++it, ++rightPtr) {
        *rightPtr = *it;
    }
    
    size_t i = 0, j = 0;
    auto dest = first;
    
    while (i < dist_left && j < dist_right) {
        if (comp(leftArr[i], rightArr[j])) {
            ValueType temp = leftArr[i];
            std::iter_swap(dest, &temp);
            ++i;
        } else {
            ValueType temp = rightArr[j];
            std::iter_swap(dest, &temp);
            ++j;
        }
        ++dest;
    }
    while (i < dist_left) {
        ValueType temp = leftArr[i];
        std::iter_swap(dest, &temp);
        ++i;
        ++dest;
    }
    
    while (j < dist_right) {
        ValueType temp = rightArr[j];
        std::iter_swap(dest, &temp);
        ++j;
        ++dest;
    }
    
    delete[] leftArr;
    delete[] rightArr;
}

template< typename RandomAccessIterator, typename Compare >
void merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    auto dist = std::distance(first, last);
    if (dist <= 1) return;
    
    auto mid = first + dist / 2;
    
    merge_sort(first, mid, comp);
    merge_sort(mid, last, comp);
    merge(first, mid, last, comp);
}

template<typename Container, typename Compare>
double measure_sort_time(Container& cont, Compare comp) {
    auto start = std::chrono::high_resolution_clock::now();
    
    merge_sort(cont.begin(), cont.end(), comp);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    
    return duration.count();
}


int main() {
    std::vector<int> demo = {5, -3, 9, -1, 7, -4, 2, -8};
    
    std::cout << "Исходный массив: ";
    for (int x : demo) std::cout << x << " ";
    std::cout << std::endl;

    merge_sort(demo.begin(), demo.end(), std::less<int>());
    for (int x : demo) std::cout << x << " ";
    std::cout << std::endl;

    std::list<int> lst = {4, 2, 7, 1, 9};
    //sort(lst.begin(), lst.end(), std::less<int>());


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-1000000, 1000000);

    std::vector<size_t> sizes = {1000, 5000, 10000, 50000, 100000, 500000};
    
    std::cout << std::setw(10) << "Размер" 
              << std::setw(15) << "Vector (ms)" 
              << std::setw(15) << "Deque (ms)"
              << std::endl;
    
    for (size_t n : sizes) {
        std::vector<int> vec_original(n);
        std::generate(vec_original.begin(), vec_original.end(), [&]() { return dist(gen); });
        
        std::vector<int> vec = vec_original;
        std::deque<int> deq(vec_original.begin(), vec_original.end());

        double vec_time = measure_sort_time(vec, std::less<int>());
        double deq_time = measure_sort_time(deq, std::less<int>());

        
        std::cout << std::setw(10) << n
                  << std::setw(15) << vec_time
                  << std::setw(15) << deq_time
                  << std::endl;
    }

    return 0;
}
