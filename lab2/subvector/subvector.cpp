template<typename T>
class subvector {
    public:
    T *mas;
    unsigned int top;
    unsigned int capacity;

subvector(): mas(nullptr), top(0), capacity(0) {
}

subvector(const subvector& other): top(other.top), capacity(other.capacity) {
    mas = new T[other.capacity];
    for (unsigned int i = 0; i < other.top; i++) {
                mas[i] = other.mas[i];
}
};

// 1) забыт return statement;
// 2) Здесь фактически переписана логика деструктора + консруктора копирования
// Посмотри идеому copy&swap для оператора присваивания.
subvector& operator=(const subvector& other) {
    if (this != &other) {
        delete[] mas;
        mas = new T[other.capacity];
        capacity = other.capacity;
        top = other.top;
        for (unsigned int i = 0; i < other.top; i++) {
            mas[i] = other.mas[i];
    }
}
}

subvector(subvector&& other): mas(other.mas), capacity(other.capacity), top(other.top) {
    other.capacity = 0;
    other.top = 0;
    other.mas = nullptr
}


// Удаление можно оставить деструктору того объекта, который мувается.
// Это можно написать элегантнее через функцию swap
subvector& operator=(subvector&& other) {
    if (this != other) {
        delete[] mas;
        mas = other.mas;
        top = other.top;
        capacity = other.capacity;
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }
    return *this;
}

// Тот же самый код, что и в resize, нужно здесь его переиспользовать, чтобы не плодить ошибки типа "тут исправил -- там забыл".
bool push_back(const T& d) {
    if (top >= capacity) {
        unsigned int new_capacity = (capacity == 0) ? 1 : capacity * 2;

        int *new_mas = new int[new_capacity];
        for (unsigned int i = 0; i < top; i++) {
            new_mas[i] = mas[i];
        }
        
        delete[] mas;

        mas = new_mas;
        capacity = new_capacity;
    }
    mas[top] = d;
    top++;
    return true;
};

T pop_back() {
    if (top == 0) {
        return T();
    }
    top--;
    return mas[top];
};

bool resize(unsigned int new_capacity) {
    if (new_capacity == capacity) {
        return true;
    }
    int *new_mas = new int[new_capacity];

    unsigned int elements_to_copy = top;
    if (new_capacity < top) {
        elements_to_copy = new_capacity;
    }
    
    for (unsigned int i = 0; i < elements_to_copy; i++) {
        new_mas[i] = mas[i];
    }

    delete[] mas;

    mas = new_mas;
    capacity = new_capacity;
    top = elements_to_copy;
    // строки 89-92 и 102 можно записать в одну с использованием тернарного оператора 
    return true;
};

void shrink_to_fit() {
    if (top == capacity) {
        return;
    }
    
    if (top == 0) {
        delete[] mas;
        mas = nullptr;
        capacity = 0;
    } else {
        int *new_mas = new int[top];

        for (unsigned int i = 0; i < top; i++) {
            new_mas[i] = mas[i];
        }
        delete[] mas;

        mas = new_mas;
        capacity = top;
    }
};

void clear() {
    top = 0;
};

~subvector() {
    delete[] mas;
};

};
