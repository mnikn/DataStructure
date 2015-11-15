#ifndef BINARYTREETEST_H
#define BINARYTREETEST_H

#include "BinaryTree.h"
#include <cassert>

//测试节点
void test_case1()
{
    auto a = new Node<int>(5);
    a->insertAsLc(4);
    a->insertAsRc(7);
    assert(a->size()==3&&a->lChild->data==4&&a->rChild->data==7);
}

//测试树的构造函数和析构函数
void test_case2()
{
    auto n = new Node<int>(6);
    BinaryTree<int> a(n);
    auto b = a.insertAsLc(n,3);
    auto c = a.insertAsRc(n,5);
    a.insertAsLc(b,7);
    a.insertAsLc(c,8);
    assert(a.size()==5);
}

//测试先序遍历
void test_case3()
{
    BinaryTree<int> a;
    auto x =a.insertAsLc(a.root(),4);
    a.insertAsRc(a.root(),6);
    a.insertAsLc(x,76);
    auto f = [](int &e){e += 10;};
    a.travPre(a.root(),f);
    assert(a.root()->data==10&&a.root()->lChild->data==14&&a.root()->rChild->data==16&&a.root()->lChild->lChild->data==86);
}

//测试中序遍历
void test_case4()
{
    BinaryTree<int> a;
    auto x =a.insertAsLc(a.root(),4);
    a.insertAsRc(a.root(),6);
    a.insertAsLc(x,76);
    auto f = [](int &e){e += 10;};
    a.travLevel(f);
    assert(a.root()->data==10&&a.root()->lChild->data==14&&a.root()->rChild->data==16&&a.root()->lChild->lChild->data==86);
}

void test_all()
{
    test_case1();
    test_case2();
    test_case3();
    test_case4();
}

#endif // BINARYTREETEST_H
