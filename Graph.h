#ifndef GRAPH_H
#define GRAPH_H

#include "Vector.h"
#include <cstddef>

enum VStatus{
    UNDISCOVERED,DISCOVERED,VISITED
};
enum EStatus{
    UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD
};


template <typename Tv>
struct Vertex{
    Tv data;
    int in_degree,out_degree;
    VStatus status;
    int dTime,fTime;
    int parent;
    int priority;
    Vertex(const Tv &_data):
        data(_data),
        in_degree(0),
        out_degree(0),
        status(UNDISCOVERED),
        dTime(-1),
        fTime(-1),
        parent(-1),
        priority(INT_MAX){}

};

template <typename Te>
struct Edge{
    Te data;
    int weight;
    EStatus status;
    Edge(const Te &_data,const int &_weight):
        data(_data),
        weight(_weight),
        status(UNDETERMINED){}
};

template <typename Tv,typename Te>
class Graph{
private:
    int _size;
    Vector<Vertex<Tv> > _vertex;
    Vector<Vector<Edge<Te>* > > _edge;


/*****构造函数和析构函数*****/
public:
    Graph():_size(0){}
    ~Graph()
    {
        for(int i=0;i<_size;++i){
            for(int j=0;j<_size;++j){
                delete _edge[i][j];
            }
        }
    }

/*****接口的声明*****/
public:
    //顶点操作
    Tv& vertex(int i) const;
    int inDegree(int i) const;
    int outDegree(int i) const;
    VStatus& vertex_status(int i) const;
    int& dTime(int i) const;
    int& fTime(int i) const;
    int& parent(int i) const;
    int& priority(int i) const;
    int size() const;
    int nextNbr(int i,int j) const;
    int firstNbr(int i) const;
    void insert_vertex(const Tv &data);

    //边操作
    Te& edge(int i,int j) const;
    int& weight(int i,int j) const;
    EStatus& edge_status(int i,int j) const;
    bool exists(int i,int j) const;
    void insert_edge(const Te &edge,int w,int i,int j);
    Te erase_edge(int i,int j);




};

template <typename Tv,typename Te>
Tv& Graph<Tv,Te>::vertex(int i) const
{
    return _vertex[i].data;
}

template <typename Tv,typename Te>
int Graph<Tv,Te>::inDegree(int i) const
{
    return _vertex[i].in_degree;
}

template <typename Tv,typename Te>
int Graph<Tv,Te>::outDegree(int i) const
{
    return _vertex[i].out_degree;
}

template <typename Tv,typename Te>
VStatus& Graph<Tv,Te>::vertex_status(int i) const
{
    return _vertex[i].status;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::dTime(int i) const
{
    return _vertex[i].dTime;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::fTime(int i) const
{
    return _vertex[i].fTime;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::parent(int i) const
{
    return _vertex[i].parent;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::priority(int i) const
{
    return _vertex[i].priority;
}

template <typename Tv,typename Te>
int Graph<Tv,Te>::size() const
{
    return _size;
}

template <typename Tv,typename Te>
bool Graph<Tv,Te>::exists(int i, int j) const
{
    return _edge[i][j]!=nullptr;
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::insert_edge(const Te &data, int w, int i, int j)
{
    if(exists(i,j)) return;
    _edge[i][j] = new Edge<Te>(data,w);
    ++_size;
    ++_vertex[i].out_degree;
    ++_vertex[j].in_degree;
}

template <typename Tv,typename Te>
Te Graph<Tv,Te>::erase_edge(int i, int j)
{
    if(!exists(i,j)) return;
    Te tmp = _edge[i][j];
    delete _edge[i][j];_edge[i][j] = nullptr;
    --_size;
    --_vertex[i].out_degree;
    --_vertex[j].in_degree;
    return tmp;
}

template <typename Tv,typename Te>
int Graph<Tv,Te>::nextNbr(int i, int j) const
{
    while(j>-1&&!exists(i,--j)){
        return j;
    }
}

template <typename Tv,typename Te>
int Graph<Tv,Te>::firstNbr(int i) const
{
    return nextNbr(i,_size);
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::insert_vertex(const Tv &data)
{
    for(int i=0;i<_size;++i){
        _edge[i].push_back(nullptr);
    }
    _edge.push_back(Vector<Edge<Te>* >(_size,nullptr));
    _vertex.push_back(Vertex<Tv>(data));
}

template <typename Tv,typename Te>
Te& Graph<Tv,Te>::edge(int i, int j) const
{
    return _edge[i][j]->data;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::weight(int i, int j) const
{
    return _edge[i][j]->weight;
}

template <typename Tv,typename Te>
EStatus& Graph<Tv,Te>::edge_status(int i, int j) const
{
    return _edge[i][j]->status;
}

#endif // GRAPH_H
