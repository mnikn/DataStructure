#ifndef QUEUETEST_H
#define QUEUETEST_H

#include "Queue.h"
#include <cassert>

//测试队列enqueue和dequeue
void test_case1()
{
    Queue<int> q;
    q.enqueue(4);
    q.enqueue(6);
    assert(q.size()==2&&q.front()==4);

    q.dequeue();
    assert(q.size()==1&&q.front()==6);
    q.dequeue();
    assert(q.empty());
}

//测试队列的构造函数
void test_case2()
{
    Queue<int> a;
    a.enqueue(4);
    a.enqueue(6);

    Queue<int> b(a);
    assert(b.front()==4&&b.size()==2);
}

void test_all()
{
    test_case1();
    test_case2();
}

#endif // QUEUETEST_H
