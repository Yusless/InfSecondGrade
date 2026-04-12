#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <string>
#include <type_traits>

template<typename T, typename Container = std::deque<T>>
class Stack {
private:
    Container data;
    
public:
    void push(const T& value) {
        data.push_back(value);
    }
    
    void push(T&& value) {
        data.push_back(std::move(value));
    }
    
    void pop() {
        if (data.empty()) {
            throw std::out_of_range("Stack::pop(): stack is empty");
        }
        data.pop_back();
    }

    T& top() {
        if (data.empty()) {
            throw std::out_of_range("Stack::top(): stack is empty");
        }
        return data.back();
    }
    
    const T& top() const {
        if (data.empty()) {
            throw std::out_of_range("Stack::top(): stack is empty");
        }
        return data.back();
    }
    
    size_t size() const {
        return data.size();
    }
    
    bool empty() const {
        return data.empty();
    }
    
    void clear() {
        data.clear();
    }
    
    void swap(Stack& other) noexcept {
        data.swap(other.data);
    }
};

template<>
class Stack<char, std::string> {
private:
    std::string data;
    
public:
    void push(char value) {
        data.push_back(value);
    }

    void push(const std::string& str) {
        data.append(str);
    }
    
    void pop() {
        if (data.empty()) {
            throw std::out_of_range("Stack<char, string>::pop(): stack is empty");
        }
        data.pop_back();
    }
    
    char& top() {
        if (data.empty()) {
            throw std::out_of_range("Stack<char, string>::top(): stack is empty");
        }
        return data.back();
    }
    
    const char& top() const {
        if (data.empty()) {
            throw std::out_of_range("Stack<char, string>::top(): stack is empty");
        }
        return data.back();
    }
    
    size_t size() const {
        return data.size();
    }
    
    bool empty() const {
        return data.empty();
    }
    
    void clear() {
        data.clear();
    }
    
    const std::string& str() const {
        return data;
    }
    
    std::string release() {
        std::string result;
        result.swap(data);
        return result;
    }
};

template<typename StackType>
void demonstrate_stack(StackType& s) {
    std::cout << "Empty: " << std::boolalpha << s.empty() << std::endl;
    std::cout << "Size: " << s.size() << std::endl;
    
    std::cout << "Pushing nums" << std::endl;
    s.push(3);
    s.push(13);
    s.push(42);
    
    std::cout << "Empty: " << std::boolalpha << s.empty() << std::endl;
    
    std::cout << "Top: " << s.top() << std::endl;
    std::cout << "Size: " << s.size() << std::endl;
    
    std::cout << "Pop it all: ";
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
};

int main() {
    Stack<int> stack1;
    demonstrate_stack(stack1);

    std::cout << std::endl;
    
    Stack<int, std::vector<int>> stack2;
    demonstrate_stack(stack2);
    
    
    Stack<char, std::string> char_stack;
    std::cout << std::endl;
    
    std::cout << "Pushing" << std::endl;
    char_stack.push("Never");
    char_stack.push("odd");
    char_stack.push("or");
    char_stack.push("eve");
    char_stack.push('n');
    
    std::cout << "This is \"" << char_stack.str() << "\"" << std::endl;
    std::cout << "Size: " << char_stack.size() << std::endl;
    
    std::cout << "Popping: ";
    while (!char_stack.empty()) {
        std::cout << char_stack.top();
        char_stack.pop();
    }
    return 0;
}