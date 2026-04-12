#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <forward_list>
#include <string>
#include <type_traits>
#include <iterator>
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

template<typename T, typename Container = std::deque<T>>
class Stack {
private:
    Container data;
    
public:
    void push(const T& value) { data.push_back(value); }
    void push(T&& value) { data.push_back(std::move(value)); }
    
    void pop() {
        if (data.empty()) throw std::out_of_range("Stack::pop(): stack is empty");
        data.pop_back();
    }

    T& top() {
        if (data.empty()) throw std::out_of_range("Stack::top(): stack is empty");
        return data.back();
    }
    
    const T& top() const {
        if (data.empty()) throw std::out_of_range("Stack::top(): stack is empty");
        return data.back();
    }
    
    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }
    void clear() { data.clear(); }
};

template<>
class Stack<char, std::string> {
private:
    std::string data;
    
public:
    void push(char value) { data.push_back(value); }
    void push(const std::string& str) { data.append(str); }
    
    void pop() {
        if (data.empty()) throw std::out_of_range("Stack<char, string>::pop(): stack is empty");
        data.pop_back();
    }
    
    char& top() {
        if (data.empty()) throw std::out_of_range("Stack<char, string>::top(): stack is empty");
        return data.back();
    }
    
    const char& top() const {
        if (data.empty()) throw std::out_of_range("Stack<char, string>::top(): stack is empty");
        return data.back();
    }
    
    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }
    void clear() { data.clear(); }
    const std::string& str() const { return data; }
};


template<typename...>
using void_t = void;

template<typename Container, typename = void>
struct has_push_back : std::false_type {};

template<typename Container>
struct has_push_back<Container, void_t<decltype(std::declval<Container>().push_back(std::declval<typename Container::value_type>()))>> 
    : std::true_type {};

template<typename Container, typename = void>
struct has_pop_back : std::false_type {};

template<typename Container>
struct has_pop_back<Container, void_t<decltype(std::declval<Container>().pop_back())>> 
    : std::true_type {};

template<typename Container, typename = void>
struct has_back : std::false_type {};

template<typename Container>
struct has_back<Container, void_t<decltype(std::declval<Container>().back())>> 
    : std::true_type {};

template<typename Container, typename = void>
struct has_value_type : std::false_type {};

template<typename Container>
struct has_value_type<Container, void_t<typename Container::value_type>> 
    : std::true_type {};


template<typename Container, typename = void>
struct has_begin_end : std::false_type {};

template<typename Container>
struct has_begin_end<Container, 
    void_t<decltype(std::declval<Container>().begin()),
           decltype(std::declval<Container>().end())>> 
    : std::true_type {};

template<typename Iterator, typename = void>
struct is_random_access_iterator : std::false_type {};

template<typename Iterator>
struct is_random_access_iterator<Iterator, 
    void_t<typename std::iterator_traits<Iterator>::iterator_category>> 
    : std::is_base_of<std::random_access_iterator_tag, 
                      typename std::iterator_traits<Iterator>::iterator_category> {};

template<typename Container>
class CheckedStack {
private:
    static_assert(has_value_type<Container>::value,
                  "CheckedStack: Container must have value_type");
    static_assert(has_push_back<Container>::value,
                  "CheckedStack: Container must have push_back() method");
    static_assert(has_pop_back<Container>::value,
                  "CheckedStack: Container must have pop_back() method");
    static_assert(has_back<Container>::value,
                  "CheckedStack: Container must have back() method");
    Container data;
    
public:
    using value_type = typename Container::value_type;
    
    CheckedStack() = default;
    explicit CheckedStack(const Container& cont) : data(cont) {}
    
    void push(const value_type& value) { data.push_back(value); }
    void push(value_type&& value) { data.push_back(std::move(value)); }
    
    void pop() {
        if (data.empty()) throw std::out_of_range("CheckedStack::pop(): stack is empty");
        data.pop_back();
    }
    
    value_type& top() {
        if (data.empty()) throw std::out_of_range("CheckedStack::top(): stack is empty");
        return data.back();
    }
    
    const value_type& top() const {
        if (data.empty()) throw std::out_of_range("CheckedStack::top(): stack is empty");
        return data.back();
    }
    
    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }
};

template<typename Container, typename Compare>
void checked_sort(Container& cont, Compare comp) {
    static_assert(has_begin_end<Container>::value,
                  "checked_sort: Container must have begin() and end() methods");
    static_assert(is_random_access_iterator<decltype(cont.begin())>::value,
                  "checked_sort: Container must provide RandomAccessIterator");
    static_assert(std::is_assignable_v<decltype(*cont.begin()), decltype(*cont.begin())>,
                  "checked_sort: Container elements must be assignable");
    
    merge_sort(cont.begin(), cont.end(), comp);
}


template<typename Container>
void print(const Container& cont) {
    for (const auto& x : cont) std::cout << x << " ";
    std::cout << std::endl;
}

int main() {
    std::cout << "std::vector<int>:" << std::endl;
    CheckedStack<std::vector<int>> vec_stack;
    vec_stack.push(3);
    vec_stack.push(13);
    vec_stack.push(42);
    std::cout << "Top: " << vec_stack.top() << std::endl;
    
    std::cout << "std::deque<double>:" << std::endl;
    CheckedStack<std::deque<double>> deq_stack;
    deq_stack.push(3.14);
    deq_stack.push(2.71);
    std::cout << "Top: " << deq_stack.top() << std::endl;
    
    std::cout << "std::list<char>:" << std::endl;
    CheckedStack<std::list<char>> list_stack;
    list_stack.push('G');
    list_stack.push('C');
    std::cout << "Top: " << list_stack.top() << std::endl;
    
    std::cout << "std::string:" << std::endl;
    Stack<char, std::string> str_stack;
    str_stack.push("Never gonna");
    str_stack.push("give you up");
    std::cout << str_stack.str() << "\"" << std::endl;

    std::cout << "std::vector<int>:" << std::endl;
    std::vector<int> vec = {5, 2, 9, 1, 5, 6};
    print(vec);
    checked_sort(vec, std::less<int>());
    print(vec);
    
    std::cout << "std::deque<double>:" << std::endl;
    std::deque<double> deq = {3.14, 1.41, 2.71, 0.57};
    print(deq);
    checked_sort(deq, [](double a, double b) { return a > b; });
    print(deq);
    
    std::cout << "std::array<char, 6>:" << std::endl;
    std::array<char, 6> arr = {'z', 'a', 'm', 'b', 'o', 'e'};
    print(arr);
    checked_sort(arr, std::less<char>());
    print(arr);
    return 0;
}