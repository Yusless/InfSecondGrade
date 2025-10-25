#include <iostream>

struct subvector {
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

bool init(subvector *qv) {
    qv->mas = nullptr;
    qv->top = 0;
    qv->capacity = 0;
    return true;
}

bool push_back(subvector *qv, int d) {
    if (qv->top >= qv->capacity) {
        unsigned int new_capacity = (qv->capacity == 0) ? 1 : qv->capacity * 2;

        int *new_mas = new int[new_capacity];
        for (unsigned int i = 0; i < qv->top; i++) {
            new_mas[i] = qv->mas[i];
        }
        
        delete[] qv->mas;

        qv->mas = new_mas;
        qv->capacity = new_capacity;
    }
    qv->mas[qv->top] = d;
    qv->top++;
    return true;
}

int pop_back(subvector *qv) {
    if (qv->top == 0) {
        return 0;
    }
    qv->top--;
    return qv->mas[qv->top];
}

bool resize(subvector *qv, unsigned int new_capacity) {
    if (new_capacity == qv->capacity) {
        return true;
    }
    int *new_mas = new int[new_capacity];

    unsigned int elements_to_copy = qv->top;
    if (new_capacity < qv->top) {
        elements_to_copy = new_capacity;
    }
    
    for (unsigned int i = 0; i < elements_to_copy; i++) {
        new_mas[i] = qv->mas[i];
    }

    delete[] qv->mas;

    qv->mas = new_mas;
    qv->capacity = new_capacity;
    qv->top = elements_to_copy;
    
    return true;
}

void shrink_to_fit(subvector *qv) {
    if (qv->top == qv->capacity) {
        return;
    }
    
    if (qv->top == 0) {
        delete[] qv->mas;
        qv->mas = nullptr;
        qv->capacity = 0;
    } else {
        int *new_mas = new int[qv->top];

        for (unsigned int i = 0; i < qv->top; i++) {
            new_mas[i] = qv->mas[i];
        }
        delete[] qv->mas;

        qv->mas = new_mas;
        qv->capacity = qv->top;
    }
}


void clear(subvector *qv) {
    qv->top = 0;
}

void destructor(subvector *qv) {
    delete[] qv->mas;
    qv->mas = nullptr;
    qv->top = 0;
    qv->capacity = 0;
}