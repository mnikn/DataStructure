#ifndef LISTTEST_H
#define LISTTEST_H

#include "List.h"
#include <cassert>

//测试列表节点
void test_case1()
{
    ListItem<int> *a = new ListItem<int>(3);
    assert(a->data==3);
    a->insertAsPred(5);
    a->insertAsSucc(6);
    assert(a->pred->data==5);
    assert(a->pred->succ->data==3);
    assert(a->succ->data==6);
    assert(a->succ->pred->data==3);
}

//测试列表的构造和析构函数
void test_case2()
{
    List<int> a;
    a.insertAsFirst(3);
    a.insertAsFirst(5);
    a.insertAsFirst(7);

    List<int> b(a);
    assert(b.size()==3);

    List<int> c = {1,2,3,5};
    assert(c.size()==4);

    List<int> d;
    d = {1,2,3};
    assert(d.size()==3);
}

//测试列表的插入和删除操作
void test_case3()
{
    List<int> a;
    a.insertAsFirst(3);
    a.insertAsFirst(5);
    a.insertAsFirst(7);
    assert(a[0]==7&&a[1]==5&&a[2]==3);
    assert(a.size()==3);

    a.erase(1);
    assert(a[0]==7&&a[1]==3);
    a.erase(0,2);
    assert(a.empty());

    List<int> b;
    b.insertAsLast(3);
    b.insertAsLast(5);
    b.insertAsLast(7);
    assert(b[0]==3&&b[1]==5&&b[2]==7);
    assert(b.size()==3);

    b.erase(1);
    assert(b[0]==3&&b[1]==7);
    b.erase(0,2);
    assert(b.empty());

}

//测试列表寻找操作
void test_case4()
{
    List<int> a = {1,2,3,4};
    assert(a.findFirst(1)==0&&a.findFirst(2)==1);
    assert(a.findLast(1)==0&&a.findLast(2)==1);

    List<int> b = {1,1,2,2,3,3,4,4};
    assert(b.findFirst(1)==0&&b.findFirst(2)==2);
    assert(b.findLast(1)==1&&b.findLast(2)==3);
}

void test_all()
{
    test_case1();
    test_case2();
    test_case3();
    test_case4();
}

#endif // LISTTEST_H
