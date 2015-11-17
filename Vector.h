#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
using std::swap;
using std::ends;
using std::ostream;
using std::initializer_list;


template <typename T>
class Vector
{

private:
    int _capacity;
    int _size;
    T *_elem;
    static const int DEFAULT_CAPACITY = 3;


/*****辅助函数*****/
private:
    void copyFrom(const T *array,int lo,int hi);
    void expand();

/*****构造函数和析构函数*****/
public:
    Vector(int n = DEFAULT_CAPACITY)
    {
        _elem = new T[_capacity = n];
        _size = 0;
    }
    Vector(const initializer_list<T> &array)
    {
        copyFrom(array.begin(),0,array.size());
    }
    Vector(const T *array,int lo,int hi)
    {
        copyFrom(array,lo,hi);
    }
    template <int N>
    Vector(const T (&array)[N])
    {
        copyFrom(array,0,N);
    }
    Vector(const Vector<T> &V, int lo, int hi)
    {
        copyFrom(V._elem,lo,hi);
    }
    Vector(const Vector<T> &V)
    {
        copyFrom(V._elem,0,V._size);
    }
    ~Vector()
    {
        delete _elem;
    }

/*****声明各类接口*****/
public:
    void clear();
    int size() const;
    bool empty() const;
    void reserve(int capacity);
    void push_back(const T &e);
    T pop_back();
    void insert(int index,const T &e);
    int erase(int lo,int hi);
    T erase(int index);
    int deduplicate();
    int unique();
    int findFirst(int lo,int hi,const T &e) const;
    int findFirst(const T &e) const;
    int findLast(int lo,int hi,const T &e) const;
    int findLast(const T &e) const;
    int binarySearchFirst(int lo,int hi,const T &e) const;
    int binarySearchFirst(const T &e) const;
    int binarySearchLast(int lo,int hi,const T &e) const;
    int binarySearchLast(const T &e) const;


/*****运算符的重载*****/
public:
    T& operator[](const int &index)
    {
        return _elem[index];
    }
    const T& operator[](const int &index) const
    {
        return _elem[index];
    }
    Vector<T> operator=(const initializer_list<T> &array)
    {
        copyFrom(array.begin(),0,array.size());
        return *this;
    }
    template <int N>
    Vector<T> operator=(const T (&array)[N])
    {
        copyFrom(array,0,N);
        return *this;
    }
    Vector<T> operator=(const Vector<T> &V)
    {
        copyFrom(V._elem,0,V.size());
        return *this;
    }
    bool operator ==(const Vector<T> &V) const
    {
        if(_size!=V.size()) return false;
        for(int i=0;i<_size;++i){
            if(_elem[i]!=V[i]) return false;
        }
        return true;
    }
    bool operator !=(const Vector<T> &V) const
    {
        if(_size!=V.size()) return true;
        for(int i=0;i<_size;++i){
            if(_elem[i]!=V[i]) return true;
        }
        return false;
    }
    Vector<T> operator+=(const Vector<T> &V)
    {
        if(_size!=V.size()) return *this;
        for(int i=0;i<_size;++i){
            _elem[i] += V[i];
        }
        return *this;
    }
    Vector<T> operator-=(const Vector<T> &V)
    {
        if(_size!=V.size()) return *this;
        for(int i=0;i<_size;++i){
            _elem[i] -= V[i];
        }
        return *this;
    }
    Vector<T> operator*=(const Vector<T> &V)
    {
        if(_size!=V.size()) return *this;
        for(int i=0;i<_size;++i){
            _elem[i] *= V[i];
        }
        return *this;
    }
    Vector<T> operator/=(const Vector<T> &V)
    {
        if(_size!=V.size()) return *this;
        for(int i=0;i<_size;++i){
            _elem[i] /= V[i];
        }
        return *this;
    }
    Vector<T> operator%=(const Vector<T> &V)
    {
        if(_size!=V.size()) return *this;
        for(int i=0;i<_size;++i){
            _elem[i] %= V[i];
        }
        return *this;
    }

/*****友元运算符的重载*****/
friend ostream& operator<<(ostream &os,const Vector<T> &V)
{
    for(int i=0;i<V.size();++i) os<<V[i]<<ends;
    return os;
}
friend Vector<T> operator+(const Vector<T> &v1,const Vector<T> &v2)
{
    if(v1.size()!=v2.size()) return Vector<T>();
    Vector<T> ret_v;
    for(int i=0;i<v1.size();++i){
        ret_v.push_back(v1[i]+v2[i]);
    }
    return ret_v;
}
friend Vector<T> operator-(const Vector<T> &v1,const Vector<T> &v2)
{
    if(v1.size()!=v2.size()) return Vector<T>();
    Vector<T> ret_v;
    for(int i=0;i<v1.size();++i){
        ret_v.push_back(v1[i]-v2[i]);
    }
    return ret_v;
}
friend Vector<T> operator*(const Vector<T> &v1,const Vector<T> &v2)
{
    if(v1.size()!=v2.size()) return Vector<T>();
    Vector<T> ret_v;
    for(int i=0;i<v1.size();++i){
        ret_v.push_back(v1[i]*v2[i]);
    }
    return ret_v;
}
friend Vector<T> operator/(const Vector<T> &v1,const Vector<T> &v2)
{
    if(v1.size()!=v2.size()) return Vector<T>();
    Vector<T> ret_v;
    for(int i=0;i<v1.size();++i){
        ret_v.push_back(v1[i]/v2[i]);
    }
    return ret_v;
}
friend Vector<T> operator%(const Vector<T> &v1,const Vector<T> &v2)
{
    if(v1.size()!=v2.size()) return Vector<T>();
    Vector<T> ret_v;
    for(int i=0;i<v1.size();++i){
        ret_v.push_back(v1[i]%v2[i]);
    }
    return ret_v;
}

};

/*****接口的实现*****/
template<typename T>
void Vector<T>::copyFrom(const T *array, int lo, int hi)
{
    _size = 0;
    _capacity = (hi-lo)<<1;
    _elem = new T[_capacity];
    for(int i=lo;i<hi;++i){
        _elem[_size++] = array[i];
    }
}

template<typename T>
void Vector<T>::expand()
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

template<typename T>
void Vector<T>::clear()
{
    _size = 0;
    _elem = new T[_capacity];
}

template<typename T>
int Vector<T>::size() const
{
    return _size;
}

template<typename T>
bool Vector<T>::empty() const
{
    return _size==0;
}

template<typename T>
void Vector<T>::reserve(int capacity)
{
    _capacity = capacity;
    T *old_elem = _elem;
    _elem = new T[_capacity];
    for(int i=0;i<_size;++i){
        _elem[i] = old_elem[i];
    }
    delete old_elem;
}

template<typename T>
void Vector<T>::push_back(const T &e)
{
    insert(_size,e);
}

template<typename T>
T Vector<T>::pop_back()
{
    return erase(_size-1);
}

template<typename T>
void Vector<T>::insert(int index, const T &e)
{
    expand();
    for(int i=_size;i>=index;--i){
        _elem[i] = _elem[i-1];
    }
    _elem[index] = e;
    ++_size;
}

template<typename T>
int Vector<T>::erase(int lo, int hi)
{
    if(lo==hi) return 0;
    while(hi<_size){
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    return hi-lo;
}

template<typename T>
T Vector<T>::erase(int index)
{
    T ret = _elem[index];
    erase(index,index+1);
    return ret;
}

template<typename T>
int Vector<T>::deduplicate()
{
    int oldSize = _size;
    int i = 1;
    while(i<_size){
        findFirst(_elem[i],0,i)<0?i++:erase(i);
    }
    return oldSize - _size;
}

template<typename T>
int Vector<T>::unique()
{

    int i=0,j=0;
    while(j++<_size){
        if(_elem[i]!=_elem[j]){
            _elem[++i] = _elem[j];
        }
    }
    _size = i;
    return j-i;
}

template<typename T>
int Vector<T>::findFirst(int lo, int hi, const T &e) const
{
    for(int i=lo;i<hi;++i){
        if(_elem[i]==e) return i;
    }
    return -1;
}

template<typename T>
int Vector<T>::findFirst(const T &e) const
{
    return findFirst(0,_size,e);
}

template<typename T>
int Vector<T>::findLast(int lo, int hi, const T &e) const
{
    int find_index = -1;
    for(int i=lo;i<hi;++i){
        if(_elem[i]==e){
            find_index = i;
        }
    }
    return find_index;
}

template<typename T>
int Vector<T>::findLast(const T &e) const
{
    return findLast(0,_size,e);
}

template<typename T>
int Vector<T>::binarySearchFirst(int lo, int hi, const T &e) const
{
    while(lo<hi){
        int mid = (lo+hi)>>1;
        _elem[mid]<e?lo = mid+1:hi = mid;
    }
    return (_elem[lo]==e?lo:-1);
}

template<typename T>
int Vector<T>::binarySearchFirst(const T &e) const
{
    return binarySearchFirst(0,_size,e);
}

template<typename T>
int Vector<T>::binarySearchLast(int lo, int hi, const T &e) const
{
    while(lo<hi){
        int mid = (lo+hi)>>1;
        _elem[mid]>e?hi=mid:lo = mid+1;
    }
    return (_elem[--lo]==e?lo:-1);
}

template<typename T>
int Vector<T>::binarySearchLast(const T &e) const
{
    return binarySearchLast(0,_size,e);
}

#endif // VECTOR_H
