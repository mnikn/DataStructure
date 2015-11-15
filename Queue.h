#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using std::size_t;
using std::swap;



template <typename T>
class Queue{
private:
    size_t _capacity;
    size_t _size;
    T *_elem;
    static const int DEFAULT_CAPACITY = 3;

/*****辅助函数*****/
private:
    void copyFrom(const T *array,int lo,int hi);
    void expand();

/*****构造函数和析构函数*****/
public:
    Queue(int n = DEFAULT_CAPACITY)
    {
        _size = 0;
        _elem = new T[_capacity = n];
    }
    Queue(const Queue<T> &Q)
    {
        copyFrom(Q._elem,0,Q.size());
    }
    ~Queue()
    {
        delete [] _elem;
    }

/*****接口的声明*****/
public:
    size_t size() const;
    bool empty() const;
    T& front() const;
    void enqueue(const T &e);
    T dequeue();
    void clear();

public:
    Queue<T> operator=(const Queue<T> &Q)
    {
        copyFrom(Q._elem,0,Q.size());
    }
};

/*****接口的实现*****/
template <typename T>
void Queue<T>::copyFrom(const T *array, int lo, int hi)
{
    _size = 0;
    _capacity = (hi-lo)<<1;
    _elem = new T[_capacity];
    for(int i=lo;i<hi;++i){
        _elem[_size++] = array[i];
    }
}

template <typename T>
void Queue<T>::expand()
{
    if(_size<_capacity) return;
    _capacity = _capacity>DEFAULT_CAPACITY?_capacity:DEFAULT_CAPACITY;
    T *old_elem = _elem;
    _elem = new T[_capacity];
    for(int i=0;i<_size;++i){
        _elem[i] = old_elem[i];
    }
    delete old_elem;
}

template <typename T>
size_t Queue<T>::size() const
{
    return _size;
}

template <typename T>
bool Queue<T>::empty() const
{
    return _size==0;
}

template <typename T>
T& Queue<T>::front() const
{
    return _elem[0];
}

template <typename T>
void Queue<T>::enqueue(const T &e)
{
    _elem[_size++] = e;
}

template <typename T>
T Queue<T>::dequeue()
{
    T ret = front();
    for(int i=0;i<_size;++i){
        swap(_elem[i],_elem[i+1]);
    }
    --_size;
    return ret;
}

template <typename T>
void Queue<T>::clear()
{
    _size = 0;
}

#endif // QUEUE_H
