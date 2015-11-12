#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <initializer_list>
using std::initializer_list;
using std::ostream;
using std::size_t;
using std::cout;
using std::ends;

/*****列表节点*****/
template <typename T>
struct ListItem{
    T data;
    ListItem<T> *pred;
    ListItem<T> *succ;
    ListItem(){}
    ListItem(T _data,ListItem<T> *_pred = new ListItem<T>(),ListItem<T> *_succ = new ListItem<T>()):
        data(_data),
        pred(_pred),
        succ(_succ){}
    void insertAsPred(const T &e)
    {
        ListItem<T> *node = new ListItem<T>(e,pred,this);
        pred->succ = node;pred = node;
    }
    void insertAsSucc(const T &e)
    {
        ListItem<T> *node = new ListItem<T>(e,this,succ);
        succ->pred = node;succ = node;
    }
};



template <typename T>
class List{
private:
    ListItem<T> *_header;
    ListItem<T> *_trailer;
    size_t _size;

/*****辅助函数*****/
private:
    void copyNodes(ListItem<T> *node,size_t n);

/*****构造函数与析构函数*****/
public:
    List()
    {
        _size = 0;
        _header = new ListItem<T>();
        _trailer = new ListItem<T>();
        _header->pred = nullptr;
        _header->succ = _trailer;
        _trailer->pred = _header;
        _trailer->succ = nullptr;
    }
    List(const initializer_list<T> &I)
    {
        _size = 0;
        _header = new ListItem<T>();
        _trailer = new ListItem<T>();
        _header->pred = nullptr;
        _header->succ = _trailer;
        _trailer->pred = _header;
        _trailer->succ = nullptr;
        for(auto e:I){
            insertAsLast(e);
        }
    }
    List(const List<T> &L)
    {
        _size = 0;
        _header = new ListItem<T>();
        _trailer = new ListItem<T>();
        _header->pred = nullptr;
        _header->succ = _trailer;
        _trailer->pred = _header;
        _trailer->succ = nullptr;
        copyNodes(L.front(),L.size());
    }
    ~List()
    {
        clear();
        delete _header;
        delete _trailer;
    }

/*****声明各类接口*****/
public:
    ListItem<T> *nodeAt(int index) const;
    size_t size() const;
    bool empty() const;
    void clear();
    ListItem<T>* front() const;
    ListItem<T>* last() const;
    void insertAsFirst(const T &e);
    void insertAsLast(const T &e);
    int erase(int lo,int hi);
    void erase(int index);
    int findFirst(const T &e);
    int findLast(const T &e);

/*****运算符的重载*****/
public:
    T& operator[](int index) const
    {
        ListItem<T> *node = front();
        while(index--){
            node = node->succ;
        }
        return node->data;
    }
    List<T> operator=(const initializer_list<T> &I)
    {
        clear();
        for(auto e:I){
            insertAsLast(e);
        }
        return *this;
    }
    List<T> operator=(const List<T> &L)
    {
        copyNodes(L.front(),L.size());
        return *this;
    }
    bool operator==(const List<T> &L)
    {
        if(_size!=L.size()) return false;
        ListItem<T> *node = front();
        ListItem<T> *node_otr = L.front();
        while(node!=_trailer){
            if(node->data!=node_otr->data) return false;
            node = node->succ;
            node_otr = node_otr->succ;
        }
        return true;
    }
    bool operator!=(const List<T> &L)
    {
        if(_size!=L.size()) return true;
        ListItem<T> *node = front();
        ListItem<T> *node_otr = L.front();
        while(node!=_trailer){
            if(node->data!=node_otr->data) return true;
            node = node->succ;
            node_otr = node_otr->succ;
        }
        return false;
    }
    List<T> operator+=(const List<T> &L)
    {
        if(_size!=L.size()) return *this;

        ListItem<T> *node = front();
        ListItem<T> *node_otr = L.front();
        while(node!=_trailer){
            node->data += node_otr->data;
            node = node->succ;
            node_otr = node_otr->succ;
        }
    }
    List<T> operator-=(const List<T> &L)
    {
        if(_size!=L.size()) return *this;

        ListItem<T> *node = front();
        ListItem<T> *node_otr = L.front();
        while(node!=_trailer){
            node->data -= node_otr->data;
            node = node->succ;
            node_otr = node_otr->succ;
        }
    }
    List<T> operator*=(const List<T> &L)
    {
        if(_size!=L.size()) return *this;

        ListItem<T> *node = front();
        ListItem<T> *node_otr = L.front();
        while(node!=_trailer){
            node->data *= node_otr->data;
            node = node->succ;
            node_otr = node_otr->succ;
        }
    }
    List<T> operator/=(const List<T> &L)
    {
        if(_size!=L.size()) return *this;

        ListItem<T> *node = front();
        ListItem<T> *node_otr = L.front();
        while(node!=_trailer){
            node->data /= node_otr->data;
            node = node->succ;
            node_otr = node_otr->succ;
        }
    }
    List<T> operator%=(const List<T> &L)
    {
        if(_size!=L.size()) return *this;

        ListItem<T> *node = front();
        ListItem<T> *node_otr = L.front();
        while(node!=_trailer){
            node->data %= node_otr->data;
            node = node->succ;
            node_otr = node_otr->succ;
        }
    }

/*****友元运算符的重载*****/
friend ostream& operator<<(ostream &os,List<T> &L)
{
    ListItem<T> *node = L.front();
    while(node != L._trailer){
        os<<node->data<<ends;
        node = node->succ;
    }
    return os;
}
friend List<T> operator+(List<T> &L1,List<T> &L2)
{
    if(L1.size()!=L2.size()) return List<T>();
    List<T> ret;
    ListItem<T> *node_a = L1.front();
    ListItem<T> *node_b = L2.front();
    while(node_a != L1._trailer){
        ret.insertAsLast(node_a->data+node_b->data);
        node_a = node_a->succ;
        node_b = node_b->succ;
    }
    return ret;
}
friend List<T> operator-(List<T> &L1,List<T> &L2)
{
    if(L1.size()!=L2.size()) return List<T>();
    List<T> ret;
    ListItem<T> *node_a = L1.front();
    ListItem<T> *node_b = L2.front();
    while(node_a != L1._trailer){
        ret.insertAsLast(node_a->data-node_b->data);
        node_a = node_a->succ;
        node_b = node_b->succ;
    }
    return ret;
}
friend List<T> operator*(List<T> &L1,List<T> &L2)
{
    if(L1.size()!=L2.size()) return List<T>();
    List<T> ret;
    ListItem<T> *node_a = L1.front();
    ListItem<T> *node_b = L2.front();
    while(node_a != L1._trailer){
        ret.insertAsLast(node_a->data*node_b->data);
        node_a = node_a->succ;
        node_b = node_b->succ;
    }
    return ret;
}
friend List<T> operator/(List<T> &L1,List<T> &L2)
{
    if(L1.size()!=L2.size()) return List<T>();
    List<T> ret;
    ListItem<T> *node_a = L1.front();
    ListItem<T> *node_b = L2.front();
    while(node_a != L1._trailer){
        ret.insertAsLast(node_a->data/node_b->data);
        node_a = node_a->succ;
        node_b = node_b->succ;
    }
    return ret;
}
friend List<T> operator%(List<T> &L1,List<T> &L2)
{
    if(L1.size()!=L2.size()) return List<T>();
    List<T> ret;
    ListItem<T> *node_a = L1.front();
    ListItem<T> *node_b = L2.front();
    while(node_a != L1._trailer){
        ret.insertAsLast(node_a->data%node_b->data);
        node_a = node_a->succ;
        node_b = node_b->succ;
    }
    return ret;
}

};

/*****接口的实现*****/
template <typename T>
void List<T>::copyNodes(ListItem<T> *node, size_t n)
{
    clear();
    while(n--){
        insertAsLast(node->data);
        node = node->succ;
    }
}

template <typename T>
ListItem<T>* List<T>::nodeAt(int index) const
{
    ListItem<T> *node = front();
    while(index--){
        node = node->succ;
    }
    return node;
}

template <typename T>
size_t List<T>::size() const
{
    return _size;
}

template <typename T>
bool List<T>::empty() const
{
    return _size==0;
}

template <typename T>
void List<T>::clear()
{
    while(!empty()) erase(0);
}

template <typename T>
ListItem<T>* List<T>::front() const
{
    return _header->succ;
}

template <typename T>
ListItem<T>* List<T>::last() const
{
    return _trailer->pred;
}

template <typename T>
void List<T>::insertAsFirst(const T &e)
{
    ++_size;
    _header->insertAsSucc(e);
}

template <typename T>
void List<T>::insertAsLast(const T &e)
{
    ++_size;
    _trailer->insertAsPred(e);
}

template <typename T>
int List<T>::erase(int lo, int hi)
{
    int n = hi-lo;
    while(n--){
        erase(lo);
    }
    return n;
}

template <typename T>
void List<T>::erase(int index)
{
    ListItem<T> *node = nodeAt(index);
    node->pred->succ = node->succ;
    node->succ->pred = node->pred;
    delete node;
    --_size;
}

template <typename T>
int List<T>::findFirst(const T &e)
{
    int index = 0;
    ListItem<T> *node = front();
    while(node!=_trailer){
        if(node->data==e) return index;
        ++index;
    }
    return -1;
}

template <typename T>
int List<T>::findLast(const T &e)
{
    int tmp_index = 0;
    int index = -1;
    ListItem<T> *node = front();
    while(node!=_trailer){
        if(node->data==e) index = tmp_index;
        ++tmp_index;
    }
    return index;
}


#endif // LIST_H
