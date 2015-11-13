#ifndef STACK_H
#define STACK_H

#include <iostream>
using std::size_t;

const int DEFAULT_CAPACITY = 3;

template <typename T>
class Stack{
private:
    size_t _capacity;
    size_t _size;
    T *_elem;

/*****辅助函数*****/
private:
    void copyFrom(const T *array,int lo,int hi);
    void expand();

/*****构造函数和析构函数*****/
public:
    Stack(int n = DEFAULT_CAPACITY)
    {
        _size = 0;
        _elem = new T[_capacity = n];
    }
    Stack(const Stack<T> &S)
    {
        copyFrom(S._elem,0,S.size());
    }
    ~Stack()
    {
        delete [] _elem;
    }

/*****接口的声明*****/
public:
        size_t size() const;
        bool empty() const;
        T& top() const;
        void push(const T &e);
        T pop();
        void clear();


/*****运算符的重载*****/
public:
        Stack<T> operator=(const Stack<T> &S)
        {
            copyFrom(S._elem,0,S.size());
        }
};

/*****接口的实现*****/
template <typename T>
void Stack<T>::copyFrom(const T *array, int lo, int hi)
{
    _size = 0;
    _capacity = (hi-lo)<<1;
    _elem = new T[_capacity];
    for(int i=lo;i<hi;++i){
        _elem[_size++] = array[i];
    }
}

template <typename T>
void Stack<T>::expand()
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
size_t Stack<T>::size() const
{
    return _size;
}

template <typename T>
bool Stack<T>::empty() const
{
    return _size==0;
}

template <typename T>
T& Stack<T>::top() const
{
    return _elem[_size-1];
}

template <typename T>
void Stack<T>::push(const T &e)
{
    expand();
    _elem[_size++] = e;
}

template <typename T>
T Stack<T>::pop()
{
    T ret = top();
    --_size;
    return ret;
}

template <typename T>
void Stack<T>::clear()
{
    _size = 0;
}



#endif // STACK_H
