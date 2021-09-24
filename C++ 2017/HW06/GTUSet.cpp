/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW06_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 13.12.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the implementations of the functions                */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include "GTUSetBase.h"
#include "GTUSet.h"

using namespace GTU;

template<class T>
GTUSet<T>::GTUSet() {

    sizeOf = 0;
    isEmpty = true;
    capacity = 15;


    shared_ptr<T> p1(new T[capacity]);
    myShared = &(*p1);

    myShared = new T[capacity];
    for (int i = 0; i < capacity ; ++i) {
        myShared[i] = '*';
    }
    *p1 = myShared[0];

}



template<class T>
bool GTUSet<T>::empty() {

    if(isEmpty == true){
        cout << "set is empty" << endl;
        return true;
    }

    else{
        cout << "set is not empty" << endl;
        return  false;
    }

}

template<class T>
size_t GTUSet<T>::size() {

    int count = 0;
    if(isEmpty != true){
        for (int i = 0; i < capacity ; ++i) {
            if(myShared[i] != '*'){
                count ++;
            }

        }
    }

    cout << "size of set = " << count << endl;
    sizeOf = count;
    return count ;
}

template<class T>
size_t GTUSet<T>::max_size() {

    return capacity;
}

template<class T>
void GTUSet<T>::insert(T value) {

    if(sizeOf < capacity){
        myShared[sizeOf] = value;
        isEmpty = false;
    }


    try{
        if(sizeOf == capacity )
            throw capacity;
    }
    catch(int e){
        cerr <<"capacity is = " << e << "!! set is full" << endl;
    }
    sizeOf++;
}

template<class T>
void GTUSet<T>::erase(int position) {
    myShared[position] = '*';
    int count = 0;
    for (int i = 0; i <capacity ; ++i) {
        if(myShared[i] == '*'){
            count++;
        }
    }
    if(count == capacity){
        isEmpty = false;
    }


}

template<class T>
void GTUSet<T>::clear() {
    for (int i = 0; i <capacity ; ++i) {
        if(myShared[i] = '*'){
        }
    }
    isEmpty = true;
}

template<class T>
const int GTUSet<T>::find(const T &val) const {
    int index = -1;
    for (int i = 0; i <capacity ; ++i) {
        if(myShared[i] == val){
            index = i;
        }
    }
    return index;
}

template<class T>
size_t GTUSet<T>::count(const T &val) const {
    int index = 0;
    for (int i = 0; i <capacity ; ++i) {
        if(myShared[i] == val){
            index = 1;
        }
    }
    return index;
}

template<class T>
int GTUSet<T>::begin() noexcept {
    return 0;
}

template<class T>
int GTUSet<T>::end() noexcept {
    return sizeOf;
}

template<class T>
void GTUSet<T>::printSet() {

    cout << "contains{";
    for (int i = begin(); i < end() ; ++i) {
        if(myShared[i] != '*'){
            cout << myShared[i] <<" ";
        }

    }
    cout << "}" << endl;
}




