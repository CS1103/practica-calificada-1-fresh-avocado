//
// Created by ruben on 4/12/19.
//

#include <iostream>
#include <fstream>
#include <string>

#include "TwoLinkedList.h"

// DESTRUCTOR

TwoLinkedList::~TwoLinkedList() {
    // delete each node
    if (!is_merged) {
        if (!is_empty1() && !is_empty2()) {
            for (int i = 0; i < size1(); ++i) {
                pop_back1();
            }
            for (int i = 0; i < size2(); ++i) {
                pop_back2();
            }
            std::cout << "Two linked list (not merged) deleted from memory." << std::endl;
        }
    } else {
        // list is merged, delete each
        for (int i = 0; i < merged_size(); ++i) {
            pop_back1();
        }
        for (int i = 0; i < size1()-1; ++i) { // -1 porque ya se borró el tail1 y tail2
            pop_back1();
        }
        for (int i = 0; i < size2()-1; ++i) { // -1 porque ya se borró el tail1 y tail2
            pop_back2();
        }
    }
}

// POP_BACK

void TwoLinkedList::pop_back1() {
    if (is_empty1()) {
        std::cout << "Cannot remove elements of empty twolinkedlist1." << std::endl;
    } else if (is_merged) {
        delete tail;
        Node* temp = tail1;
        while (temp->next != tail) {
            temp = temp->next;
        }
        tail = temp;
        tail->next = nullptr;
    } else {
        delete tail1; // deletes content of tail, not the pointer tail
        Node* temp = head1;
        while (temp->next != tail1) {
            temp = temp->next;
        }
        tail1 = temp;
        tail1->next = nullptr;
    }
}

void TwoLinkedList::pop_back2() {
    if (is_empty2()) {
        std::cout << "Cannot remove elements of empty twolinkedlist2." << std::endl;
    } else if (is_merged) {
        delete tail;
        Node* temp = tail1;
        while (temp->next != tail) {
            temp = temp->next;
        }
        tail = temp;
        tail->next = nullptr;
    } else {
        delete tail2; // deletes content of tail, not the pointer tail
        Node* temp = head2;
        while (temp->next != tail2) {
            temp = temp->next;
        }
        tail2 = temp;
        tail2->next = nullptr;
    }
}

// EMPTY

bool TwoLinkedList::is_empty1() {
    return head1 == nullptr;
}

bool TwoLinkedList::is_empty2() {
    return head2 == nullptr;
}

// MERGE

std::string TwoLinkedList::merge(int value) {
    if (is_merged) {
        return "Operación duplicada";
    } else {
        if (!is_empty1() && !is_empty2()) {
            Node* merge_point = new Node(value);
            tail1->next = merge_point;
            tail1 = merge_point;
            tail2->next = merge_point;
            tail2 = merge_point;
            tail = merge_point;
            is_merged = true;
            return "Operación Exitosa";
        } else {
            return "Ambas listas deben tener al menos 1 elemento para llamar merge.";
        }
    }
}

// PUSH_BACK

void TwoLinkedList::push_back1(int value) {
    Node* temp = new Node(value);
    if (is_empty1()) {
        tail1 = temp;
        head1 = temp;
    } else if (is_merged) {
        tail->next = temp;
        tail = temp;
    } else {
            tail1->next = temp;
            tail1 = temp;
    }
}

void TwoLinkedList::push_back2(int value) {
    Node* temp = new Node(value);
    if (is_empty2()) {
        tail2 = temp;
        head2 = temp;
    } else if (is_merged) {
        tail->next = temp;
        tail = temp;
    } else {
        tail2->next = temp;
        tail2 = temp;
    }
}

// LIST

int TwoLinkedList::size1() {
    int count = 0;
    Node* actual = head1;
    while(actual != nullptr) {
        count++;
        actual = actual->next;
    }
    return count;
}

int TwoLinkedList::size2() {
    int count = 0;
    Node* actual = head2;
    while(actual != nullptr) {
        count++;
        actual = actual->next;
    }
    return count;
}

int TwoLinkedList::merged_size() {
    int count = 0;
    Node* actual = tail1;
    while (actual != nullptr) {
        count++;
        actual = actual->next;
    }
    return count;
}

// GETLIST

std::string TwoLinkedList::getlist(int list) {
    std::string output_list;
    if (list == 0) {
        if (is_merged) {
            // retornar string con nodos compartidos
            Node* temp = tail1;
            for (int i = 0; i < merged_size(); ++i) {
                output_list += std::to_string(temp->value);
                output_list += " ";
                temp = temp->next;
            }
            return output_list;
        } else {
            return "";
        }
    } else if (list == 1) {
        // print list1
        if (size1() == 0) {
            return "Empty list1.";
        }
        Node* temp = head1;
        for (int i = 0; i < size1(); ++i) {
            output_list += std::to_string(temp->value);
            output_list += " ";
            temp = temp->next;
        }
        return output_list;
    } else if (list == 2) {
        // print list2
        if (size2() == 0) {
            return "Empty list2";
        }
        Node* temp = head2;
        for (int i = 0; i < size2(); ++i) {
            output_list += std::to_string(temp->value);
            output_list += " ";
            temp = temp->next;
        }
        return output_list;
    } else {
        return "Unknown list parameter passed into getlist function.";
    }
}

// SEARCH

Node* TwoLinkedList::search(int value) {
    if (!is_merged) {
        // start by list1
        Node* temp = head1;
        for (int i = 0; i < size1(); ++i) {
            if (temp->value == value) {
                return temp;
            }
            temp = temp->next;
        }
        temp = head2;
        for (int j = 0; j < size2(); ++j) {
            if (temp->value == value) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    } else {
        Node* temp = tail1;
        for (int i = 0; i < merged_size(); ++i) {
            if (temp->value == value) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
}

void TwoLinkedList::save(std::string filename) {
    std::ofstream file;
    file.open(filename);

    if (!is_merged) {
        Node* temp = head1;
        for (int i = 0; i < size1(); ++i) {
            file << temp->value << ",";
            temp = temp->next;
        }
        file << "\n";
        temp = head2;
        for (int j = 0; j < size2(); ++j) {
            file << temp->value << ",";
            temp = temp->next;
        }
    } else if (is_merged) {
        Node* temp = head1;
        for (int i = 0; i < size1(); ++i) {
            file << temp->value << ",";
            temp = temp->next;
        }
        file << "\n";
        temp = head2;
        for (int j = 0; j < size2(); ++j) {
            file << temp->value << ",";
            temp = temp->next;
        }
        file << "\n";
        temp = tail2;
        for (int k = 0; k < merged_size(); ++k) {
            file << temp->value << ",";
            temp = temp->next;
        }
    }
}

void TwoLinkedList::load(std::string filename) {
    std::ifstream file;
    file.open(filename);
    std::string line;
    if (file.is_open()) {
        int current_line = 1;
        while (getline(file, line)) {
            std::string item;
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    if (current_line == 1) {
                        push_back1(std::stoi(line));
                    }
                    else if (current_line == 2) {
                        push_back2(std::stoi(line));
                    }
                    else if (current_line == 3) {
                        merge(std::stoi(line));
                    } else {
                        push_back1(std::stoi(line));
                    }
                    item = "";
                    continue;
                }
                item += line[i];
            }
            current_line++;
        }
    } else {
        std::cout << "No se pudo abrir el archivo con load()." << std::endl;
    }
}



















































