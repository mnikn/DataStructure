#ifndef STACKTEST_H
#define STACKTEST_H

#include "Stack.h"
#include <cassert>

//测试栈的push和pop
void test_case1()
{
    Stack<int> a;
    a.push(5);
    a.push(3);
    a.push(6);
    assert(a.top()==6);

    a.pop();
    assert(a.top()==3);
    a.pop();
    assert(a.top()==5);
    a.pop();
    assert(a.empty());
}

//测试栈的构造函数
void test_case2()
{
    Stack<int> a;
    a.push(4);
    a.push(7);

    Stack<int> b(a);
    assert(b.top()==7&&b.size()==2);
}

void test_all()
{
    test_case1();
    test_case2();
}

#endif // STACKTEST_H
