/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW06_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 13.12.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the headers of the functions of the derived CLASS   */
/*--------------------------------------------------------------------------*/
#ifndef HW6_GTUSET_H
#define HW6_GTUSET_H

#include "GTUSetBase.h"
#include "GTUSet.h"

namespace GTU{

    template <class T>
    class GTUSet : public GTUSetBase<T> {

    public:

        GTUSet();
        virtual bool empty();
        virtual size_t size();
        virtual size_t max_size();
        virtual void insert(T value);
        virtual void erase(int iterator);
        virtual void clear();
        virtual const int find (const T& val) const;
        virtual size_t count (const T& val) const;
        virtual int begin() noexcept;
        virtual int end() noexcept;
        void printSet();
        int getCapacity(){ return capacity;};
        void setCapacity(int cap){ capacity = cap;};

    private:

        shared_ptr<T> p1;
        T *myShared;
        bool isEmpty;
        int capacity;
        int sizeOf;

        class GTUIterator{

            GTUIterator(){};
            T &operator*(){};
            bool operator==(T other){};

        };

    };


}


#endif //HW6_GTUSET_H
