template<typename T>

class subforwardlist {
    public:
    struct Node {
        T data;
        Node* next;
        Node(const T& val): next(nullptr), data(val) {

        }
    }; 
    Node * begin;

    subforwardlist(): begin(nullptr) { //constructor
}

    ~subforwardlist() { //desstructor
        while (begin != nullptr) {
            Node* curr = begin;
            begin = begin->next;
            delete curr;
    }
}

    subforwardlist(const subforwardlist& other): begin(nullptr) { // copy constructor
        if (other.begin != nullptr) {
            Node* other_curr = other.begin;
            Node** curr_ptr = &begin;
            
            while (other_curr != nullptr) {
                *curr_ptr = new Node(other_curr->data);
                curr_ptr = &((*curr_ptr)->next);
                other_curr = other_curr->next;
        }
    }
}

    subforwardlist& operator=(const subforwardlist& other) { // copy assignment constructor
        if (this != &other) {
            Node* other_curr = other.begin;
            Node** curr_ptr = &begin;
            while (other_curr != nullptr) {
                *curr_ptr = new Node(other_curr->data);
                curr_ptr = &((*curr_ptr)->next);
                other_curr = other_curr->next;
            }
        if (other.begin != nullptr) {
            Node* other_curr = other.begin;
            Node** curr_ptr = &begin;
            
        while (other_curr != nullptr) {
            *curr_ptr = new Node(other_curr->data);
            curr_ptr = &((*curr_ptr)->next);
            other_curr = other_curr->next;
        }
        }
    }
    return *this;
}


    subforwardlist(subforwardlist&& other): begin(other.begin) { //move constructor
        other.begin = nullptr;
    }

    subforwardlist& operator=(subforwardlist&& other) { // move assignment constructor
        if (this != &other) {
            while (begin != nullptr) {
            Node* curr = begin;
            begin = begin->next;
            delete curr;
    }
            begin = other.begin;
            other.begin = nullptr;
        }
        return *this;
    }

void push_back(const T& data) {
    Node* new_node = new Node(data);
    
    if (begin == nullptr) {
        begin = new_node;
    }
    else {
        Node* curr = begin;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}

T pop_back() {
    if (begin == nullptr) {
        return T();
    }
    if (begin->next == nullptr) {
        T data = begin->data;
        delete begin;
        begin = nullptr;
        return data;
    }
    
    Node* curr = begin;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    int data = curr->next->data;
    delete curr->next;
    curr->next = nullptr;
    return data;
}

void push_forward(const T& data) {
    Node* new_node = new Node(data);
    new_node->next = begin;
    begin = new_node;
}

T pop_forward() {
    if (begin == nullptr) {
        return T();
    }
    Node* curr = begin;
    T data = curr->data;
    begin = begin->next;
    delete curr;
    return data;
}

void push_where( unsigned int where, const T& data) {
    if (where == 0) {
        push_forward(data);
    }
    
    Node* curr = begin;
    if (curr == nullptr) {
            return;
        }
    for (unsigned int i = 0; i < where - 1; i++) {
        curr = curr->next;
        if (curr == nullptr) {
            return;
        }
    }
    Node* new_node = new Node(data);
    new_node->next = curr->next;
    curr->next = new_node;
}

T erase_where(unsigned int where) {
    if (begin == nullptr) {
        return T();
    }
    
    if (where == 0) {
        return pop_forward();
    }
    
    Node* curr = begin;
    for (unsigned int i = 0; i < where - 1; i++) {
        if (curr == nullptr || curr->next == nullptr) {
            return T();
        }
        curr = curr->next;
    }
    
    if (curr->next == nullptr) {
        return T();
    }
    
    Node* act = curr->next;
    int data = act->data;
    curr->next = act->next;
    delete act;
    return data;
}

unsigned int size() {
    unsigned int count = 0;
    Node* curr = begin;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}
};