#ifndef GRAPHTEST_H
#define GRAPHTEST_H

#include "Graph.h"
#include <cassert>
#include <iostream>
using namespace std;

//测试构造函数和插入节点
void test_case1()
{
    Graph<int,char> a;
    a.insert_vertex(6);
    a.insert_vertex(7);
    a.insert_edge('a',0,0,1);
    assert(a.size()==2&&a.inDegree(1)==1&&a.outDegree(0)==1);
}

//测试删除节点和删除边
void test_case2()
{
    Graph<int,char> a;
    a.insert_vertex(6);
    a.insert_vertex(10);
    a.insert_edge('a',0,0,1);
    a.erase_edge(0,1);
    assert(a.inDegree(1)==0&&a.outDegree(0)==0);

    a.erase_vertex(0);
    assert(a.size()==1);
}

void test_all()
{
    test_case1();
    test_case2();
}

#endif // GRAPHTEST_H
