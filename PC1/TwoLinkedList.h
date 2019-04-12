//
// Created by ruben on 4/12/19.
//

#ifndef PC1_TWOLINKEDLIST_H
#define PC1_TWOLINKEDLIST_H

struct Node {
    int value;
    Node* next;

    explicit Node(int value): value{value}, next{nullptr} {}
};

class TwoLinkedList {
    Node* head1;
    Node* head2;
    Node* tail1;
    Node* tail2;
    Node* tail;
    Node* merge_point;
    bool is_merged;

public:
    TwoLinkedList(): head1{nullptr}, head2{nullptr}, tail1{nullptr}, tail2{nullptr}, tail{nullptr}, is_merged{false}, merge_point{
            nullptr} {}
    ~TwoLinkedList();

    void push_back1(int value);
    void push_back2(int value);

    void pop_back1();
    void pop_back2();

    int size1();
    int size2();
    int merged_size();

    std::string merge(int value);

    std::string getlist(int list);

    Node* search(int value);

    void save(std::string filename);
    void load(std::string filename);

    bool is_empty1();
    bool is_empty2();
};


#endif //PC1_TWOLINKEDLIST_H
