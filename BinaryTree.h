#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include "Queue.h"
#include "Vector.h"
#define find_end(p) p?p->height:-1
using std::size_t;
using std::cout;
using std::endl;
using std::max;

template <typename T>
struct Node{
    size_t size()
    {
        int _size = 1;
        if(lChild) _size += lChild->size();
        if(rChild) _size += rChild->size();
        return _size;
    }
    Node<T>* insertAsLc(const T &e)
    {
        return lChild = new Node<T>(e,this);
    }
    Node<T>* insertAsRc(const T &e)
    {
        return rChild = new Node<T>(e,this);
    }
    T data;
    size_t height;
    Node<T> *parent,*lChild,*rChild;
    Node(T _data = T(),Node<T> *_parent = nullptr,Node<T> *_lChild = nullptr,Node<T> *_rChild = nullptr):
        data(_data),
        height(0)
    {
        parent = _parent;
        lChild = _lChild;
        rChild = _rChild;
    }

};

template <typename T>
class BinaryTree{
protected:
    size_t _size;
    Node<T> *_root;

/*****辅助函数*****/
protected:
    int updateHeight(Node<T> *node);
    void updateHeightAbove(Node<T> *node);
    template<typename VST> void travLevel_aux(Queue<Node<T>* >queue,VST &visit);


/*****构造函数和析构函数*****/
public:
    BinaryTree(Node<T> *root = new Node<T>())
    {
        _root = root;
        _size= 0;
    }
    ~BinaryTree()
    {
        Queue<Node<T>* > queue;
        queue.enqueue(root());
        Vector<Node<T>* >vec;
        while(!queue.empty()){
            Node<T> *node = queue.dequeue();
            vec.push_back(node);
            if(node->lChild) queue.enqueue(node->lChild);
            if(node->rChild) queue.enqueue(node->rChild);
        }
        for(int i=0;i<vec.size();++i) delete vec[i];
    }

/*****接口的声明*****/
public:
    size_t size() const;
    size_t height() const;
    bool empty() const;
    Node<T>* root();
    Node<T> *insertAsLc(Node<T> *node,const T &e);
    Node<T> *insertAsRc(Node<T> *node,const T &e);
    template<typename VST> void travPre(Node<T> *node,VST &visit);
    template<typename VST> void travLevel(VST &visit);
};

/*****接口的实现*****/
template <typename T>
int BinaryTree<T>::updateHeight(Node<T> *node)
{
    return node->height = 1+max(find_end(node->lChild),find_end(node->rChild));
}

template <typename T>
void BinaryTree<T>::updateHeightAbove(Node<T> *node)
{
    while(node){
        updateHeight(node);
        node = node->parent;
    }
}

template <typename T>
size_t BinaryTree<T>::size() const
{
    return _size;
}

template <typename T>
size_t BinaryTree<T>::height() const
{
    return _root->height;
}

template <typename T>
bool BinaryTree<T>::empty() const
{
    return _size==0;
}

template <typename T>
Node<T>* BinaryTree<T>::root()
{
    return _root;
}

template <typename T>
Node<T>* BinaryTree<T>::insertAsLc(Node<T> *node, const T &e)
{
    _size += node->size();
    node->insertAsLc(e);
    updateHeightAbove(node);
    return node->lChild;
}

template <typename T>
Node<T>* BinaryTree<T>::insertAsRc(Node<T> *node, const T &e)
{
    _size += node->size();
    node->insertAsRc(e);
    updateHeightAbove(node);
    return node->rChild;
}

template <typename T>
template <typename VST>
void BinaryTree<T>::travPre(Node<T> *node,VST &visit)
{
    if(!node) return;
    visit(node->data);
    travPre(node->lChild,visit);
    travPre(node->rChild,visit);
}

template <typename T>
template <typename VST>
void BinaryTree<T>::travLevel(VST &visit)
{
    Queue<Node<T>* > queue;
    queue.enqueue(root());
    while(!queue.empty()){
        Node<T> *node = queue.dequeue();
        visit(node->data);
        if(node->lChild) queue.enqueue(node->lChild);
        if(node->rChild) queue.enqueue(node->rChild);
    }
}


#endif // BINARYTREE_H
