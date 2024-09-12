#ifndef INC_280PROJ5_DLIST_IMPL_H
#define INC_280PROJ5_DLIST_IMPL_H
#include "dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const {return !this->first;}
// If the first element of the list is a nullptr, the list is empty.

template <class T>
void Dlist<T>::insertFront(T *op){
    node* new_pointer = new node;
    new_pointer->op = op;
    new_pointer->next = this->first;
    new_pointer->prev = nullptr;
    if (this->isEmpty()) this->last = new_pointer;
    else this->first->prev = new_pointer;
    this->first = new_pointer;
}
// Insert a new element in the front of the list. Set the new first element.
// If the list is empty, also set the last element.

template <class T>
void Dlist<T>::insertBack(T *op) {
    node* new_pointer = new node;
    new_pointer->op = op;
    new_pointer->next = nullptr;
    new_pointer->prev = this->last;
    if (this->isEmpty()) this->first = new_pointer;
    else this->last->next = new_pointer;
    this->last = new_pointer;
}
// Insert a new element in the front of the list. Set the new first element.
// If the list is empty, also set the last element.

template <class T>
T *Dlist<T>::removeFront() {
    if (this->isEmpty()) throw emptyList();
    node *deleted = this->first;
    T *removed = this->first->op;
    if (this->first == this->last) {
        auto *returned = this->first->op;
        this->last = this->first = nullptr;
        delete deleted;
        return returned;
    }
    else {
        this->first = this->first->next;
        this->first->prev = nullptr;
        delete deleted;
        return removed;
    }
}
// Remove the element in the front of the list.
// If the list only has one element, also remove the last element.

template <class T>

T *Dlist<T>::removeBack() {
    if (this->isEmpty()) throw emptyList();
    node* deleted = this->last;
    T *removed = this->last->op;
    if (this->first == this->last) {
        auto *returned = this->last->op;
        this->last = this->first = nullptr;
        delete deleted;
        return returned;
    }
    else {
        this->last = this->last->prev;
        this->last->next = nullptr;
        delete deleted;
        return removed;
    }
}
// Remove the element in the last of the list.
// If the list only has one element, also remove the first element.

template <class T>
Dlist<T>::Dlist() {this->first = this->last = nullptr;}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l) {this->copyAll(l);}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l) {
    this->removeAll();
    this->copyAll(l);
    return *this;
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l) {
    if(!l.isEmpty()){
        node *insert = l.first;
        while(insert){
            T *element = new T(*insert->op);
            insertBack(element);
            insert = insert->next;
        }
    }
}

template <class T>
void Dlist<T>::removeAll() {
    while (!this->isEmpty()){
        delete this->first->op;
        node *deleted = this->first;
        this->first = this->first->next;
        delete deleted;
    }
}

template <class T>
Dlist<T>::~Dlist() {this->removeAll();}
#endif