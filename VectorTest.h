#ifndef VECTORTEST_H
#define VECTORTEST_H

#include <cassert>
#include "Vector.h"

//测试构造函数和析构函数
void test_case1()
{

    /*****测试构造函数*****/
    Vector<int> a = {1,2,3};
    assert(a[0]==1);
    assert(a[1]==2);
    assert(a[2]==3);
    assert(a.size()==3);

    int array[] = {1,2,3};
    Vector<int> b(array);
    assert(b[0]==1);
    assert(b[1]==2);
    assert(b[2]==3);
    assert(b.size()==3);

    Vector<int> c(a);
    assert(c[0]==1);
    assert(c[1]==2);
    assert(c[2]==3);
    assert(c.size()==3);

    /*****测量赋值运算符*****/
    Vector<int> d;
    d = {1,2,3};
    assert(d[0]==1);
    assert(d[1]==2);
    assert(d[2]==3);
    assert(d.size()==3);

    int array_2[] = {1,2,3};
    Vector<int> e;
    e = array_2;
    assert(e[0]==1);
    assert(e[1]==2);
    assert(e[2]==3);
    assert(e.size()==3);

    Vector<int> f;
    f = e;
    assert(f[0]==1);
    assert(f[1]==2);
    assert(f[2]==3);
    assert(f.size()==3);
}

//测试push和pop函数
void test_case2()
{
    Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    assert(a[0]==1);
    assert(a[1]==2);
    assert(a[2]==3);

    a.pop_back();
    a.pop_back();
    a.pop_back();
    assert(a.empty());
}

//测试插入操作和删除操作
void test_case3()
{
    Vector<int> a = {1,2,3};

    /*****对插入操作的测试*****/
    a.insert(0,5);
    assert(a[0]==5);
    assert(a[1]==1);
    assert(a[2]==2);
    assert(a[3]==3);

    a = {1,2,3};
    a.insert(1,5);
    assert(a[0]==1);
    assert(a[1]==5);
    assert(a[2]==2);
    assert(a[3]==3);

    a = {1,2,3};
    a.insert(2,5);
    assert(a[0]==1);
    assert(a[1]==2);
    assert(a[2]==5);
    assert(a[3]==3);

    a = {1,2,3};
    a.insert(3,5);
    assert(a[0]==1);
    assert(a[1]==2);
    assert(a[2]==3);
    assert(a[3]==5);

    /*****对删除操作的测试*****/
    a = {1,2,3};
    a.erase(0);
    assert(a[0]==2);
    assert(a[1]==3);

    a = {1,2,3};
    a.erase(1);
    assert(a[0]==1);
    assert(a[1]==3);

    a = {1,2,3};
    a.erase(2);
    assert(a[0]==1);
    assert(a[1]==2);

    a = {1,2,3};
    a.erase(0,2);
    assert(a[0]==3);

    a = {1,2,3};
    a.erase(0,3);
    assert(a.empty());
}

/*****测试查找操作*****/
void test_case4()
{
    Vector<int> v = {1,2,3};
    assert(v.findFirst(1)==0);
    assert(v.findFirst(2)==1);
    assert(v.findFirst(3)==2);
    assert(v.findFirst(4)==-1);
    assert(v.findLast(1)==0);
    assert(v.findLast(2)==1);
    assert(v.findLast(3)==2);
    assert(v.findLast(4)==-1);
    assert(v.binarySearchFirst(1)==0);
    assert(v.binarySearchFirst(2)==1);
    assert(v.binarySearchFirst(3)==2);
    assert(v.binarySearchFirst(4)==-1);
    assert(v.binarySearchLast(1)==0);
    assert(v.binarySearchLast(2)==1);
    assert(v.binarySearchLast(3)==2);
    assert(v.binarySearchLast(4)==-1);

    Vector<int> a = {1,1,2,2,2,3,3};
    assert(a.findFirst(1)==0);
    assert(a.findFirst(2)==2);
    assert(a.findFirst(3)==5);
    assert(a.findFirst(4)==-1);
    assert(a.findLast(1)==1);
    assert(a.findLast(2)==4);
    assert(a.findLast(3)==6);
    assert(a.findLast(4)==-1);
    assert(a.binarySearchFirst(1)==0);
    assert(a.binarySearchFirst(2)==2);
    assert(a.binarySearchFirst(3)==5);
    assert(a.binarySearchFirst(4)==-1);
    assert(a.binarySearchLast(1)==1);
    assert(a.binarySearchLast(2)==4);
    assert(a.binarySearchLast(3)==6);
    assert(a.binarySearchLast(4)==-1);
}

void test_case5()
{
    Vector<int> a = {1,2,3};
    a.deduplicate();
    a.unique();
    assert(a.size()==3);
    assert(a == Vector<int>({1,2,3}));

    Vector<int> b = {1,1,1,1,2,2,3,3,3};
    b.unique();
    assert(b.size()==3);
    assert(b == Vector<int>({1,2,3}));
    b = {1,1,1,1,2,2,3,3,3};
    b.unique();
    assert(b.size()==3);
    assert(b == Vector<int>({1,2,3}));
}

void test_all()
{
    test_case1();
    test_case2();
    test_case3();
    test_case4();
    test_case5();
}

#endif // VECTORTEST_H
