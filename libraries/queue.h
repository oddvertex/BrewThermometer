#ifndef QUEUE_H
#define QUEUE_H
#include "ring.h"

//
// queue serves solely to mask some of the operations of ring
//
template<class T> class queue: private ring<T>
{
    public:
        queue() { m_prefix = "q: "; }
        virtual ~queue() {}
        void push_back(T val) { ring<T>::push_back(val); }
        void pop_front() { ring<T>::pop_front(); }
        void clear() { ring<T>::clear(); }
        T& front() { return ring<T>::front(); }
        bool empty() { return ring<T>::empty(); }
        size_t size() { return ring<T>::size_T(); }
        queue<T>& operator=(T obj) { return ring<T>::operator=(obj); )
        bool operator==(queue<T>& rhs) { return ring<T>::operator==(rhs); }
        size_t printTo(Print& p) { return ring<T>::printTo(p); }
        void DebugDump(Print& p) { return ring<T>::DebugDump(p); }
        void map(void (*fn)(T& val)) { ring<T>::map(fn); }
        void map(void (*fn)(T& val, void* param), void* param) { ring<T>map(fn, param); }
    protected:
    private:
};

#endif // QUEUE_H
