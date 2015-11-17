#ifndef GRAPH_H
#define GRAPH_H

#include "Vector.h"
#include "Queue.h"
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
    Vertex(Tv _data = Tv()):
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
    Edge(Te _data = Te(),int _weight = int()):
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
    void BFS(int v,int &clock);


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
    Tv& vertex(int i);
    int inDegree(int i) const;
    int outDegree(int i) const;
    VStatus& vertex_status(int i);
    int& dTime(int i);
    int& fTime(int i);
    int& parent(int i);
    int& priority(int i);
    int size() const;
    int nextNbr(int i,int j) const;
    int firstNbr(int i) const;
    void insert_vertex(const Tv &data);
    Tv erase_vertex(int i);

    //边操作
    Te& edge(int i,int j) const;
    int& weight(int i,int j) const;
    EStatus& edge_status(int i,int j) const;
    bool exists(int i,int j) const;
    void insert_edge(const Te &edge,int w,int i,int j);
    Te erase_edge(int i,int j);

    //遍历
    void bfs(int v);
    void DFS(int v,int &clock);

};

template <typename Tv,typename Te>
Tv& Graph<Tv,Te>::vertex(int i)
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
VStatus& Graph<Tv,Te>::vertex_status(int i)
{
    return _vertex[i].status;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::dTime(int i)
{
    return _vertex[i].dTime;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::fTime(int i)
{
    return _vertex[i].fTime;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::parent(int i)
{
    return _vertex[i].parent;
}

template <typename Tv,typename Te>
int& Graph<Tv,Te>::priority(int i)
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
    ++_vertex[i].out_degree;
    ++_vertex[j].in_degree;
}

template <typename Tv,typename Te>
Te Graph<Tv,Te>::erase_edge(int i, int j)
{
    if(!exists(i,j)) return Te();
    Te tmp = _edge[i][j]->data;
    delete _edge[i][j];_edge[i][j] = nullptr;
    --_vertex[i].out_degree;
    --_vertex[j].in_degree;
    return tmp;
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::bfs(int s)
{
    int clock = 0,v = s;
    do{
        if(vertex_status(v) == UNDISCOVERED){
            BFS(v,clock);
        }
        ++v;
        v %= _size;
    }while(s != v);
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::BFS(int v, int &clock)
{
    Queue<int> Q;
    vertex_status(v) = DISCOVERED;
    Q.enqueue(v);
    while(!Q.empty()){
        int e = Q.dequeue();
        dTime(e) = ++clock;
        for(int u = firstNbr(e);u >= 0;u = nextNbr(e,u)){
            if(vertex_status(u) == UNDISCOVERED){
                vertex_status(u) = DISCOVERED;
                Q.enqueue(u);
                edge_status(e,u) = TREE;
                parent(u) = e;
            }
            else{
                edge_status(e,u) = CROSS;
            }
            vertex_status(e) = VISITED;
        }
    }
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::DFS(int v, int &clock)
{
    dTime(v) = ++clock;
    vertex_status(v) = DISCOVERED;
    for(int u = firstNbr(v);u>=0;u = nextNbr(v,u)){
        switch(vertex_status(u)){
            case UNDISCOVERED:
                vertex_status(u) = DISCOVERED;
                edge_status(v,u) = TREE;
                parent(u) = v;
                DFS(u,clock);
                break;
            case DISCOVERED:
                edge_status(v,u) = BACKWARD;
            default:
                edge_status(v,u) = dTime(v)<dTime(u)?FORWARD:CROSS;
                break;
        }
        vertex_status(v) = VISITED;
        fTime(v) = ++clock;
    }
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
    _vertex.push_back(Vertex<Tv>(data));
    for(int i=0;i<_size;++i){
        _edge[i][_size] = nullptr;
    }
    for(int i=0;i<_size;++i){
        _edge[_size].push_back(nullptr);
    }
    ++_size;
}

template <typename Tv,typename Te>
Tv Graph<Tv,Te>::erase_vertex(int i)
{
    Vertex<Tv> tmp = _vertex.erase(i);
    _edge.erase(i);
    for(int j=0;j<_size;++j){
        _edge[j].erase(i);
    }
    --_size;
    return tmp.data;
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
