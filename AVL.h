#ifndef AVL_H
#define AVL_H

#include "BinaryTree.h"

template <typename K,typename V>
struct Entry{
    K key;V value;
    Entry(K _key = K(),V _value = V()):
        key(_key),
        value(_value){}
    Entry(const Entry<K,V> &e):
        key(e.key),
        value(e.value){}
    bool operator<(const Entry<K,V> &e){ return key < e.key; }
    bool operator>(const Entry<K,V> &e){ return key > e.key; }
    bool operator==(const Entry<K,V> &e){ return key == e.key; }
    bool operator!=(const Entry<K,V> &e){ return key != e.key; }

template <typename T>
class BST : public BinaryTree<T>{
public:
    virtual Node<T>*& search(const T &e);
    virtual Node<T>*& insert(const T &e);
    virtual bool remove(const T &e);

protected:
    Node<T> *_hot;

};

#endif // AVL_H
