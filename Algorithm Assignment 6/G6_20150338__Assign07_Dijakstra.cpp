// GROUP:   6
// ID:      20150338
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   Mohamed Samy Sayed
// Name2:   XX SECOND STUDENT FULL NAME
// UVA Username: m.shaar97

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


template <class value>
struct Array
{
    int n, sz;
    value *arr;

    void Initialize()
    {
        sz = 1;
        n = 0;
        arr = new value[sz];
    }

    void Destroy()
    {
        n = 0;
        delete []arr;
    }

    void AddLast(value v)
    {
        if(n==sz)
        {
            sz *= 2;
            value *new_arr = new value[sz];
            for (int i = 0; i < n; i++)
            {
                new_arr[i] = arr[i];
            }
            delete []arr;
            arr = new_arr;
        }
        arr[n++] = v;
    }

    void RemoveLast()
    {
        if (n > 0)
        {
            n--;
        }
    }

    value &operator[](int i)
    {
        return arr[i];
    }

    void Print()
    {
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << endl;
        }
    }
};

template <class Elem>
struct Heap
{
    int *pos; // if a[i].v=v then pos[v]=i, otherwise pos[v]=-1, position of node in heap
    Array<Elem> a;
    bool (*isBefore)(Elem &a, Elem &b);

    void Initialize(bool (*_isBefore)(Elem &a, Elem &b), int n) // n is required to allocate and initialize pos[]
    {
        a.Initialize();
        isBefore = _isBefore;
        pos = new int[n];
        for (int i = 0; i < n; i++)
        {
            pos[i] = -1;
        }
    }

    void Destory()
    {
        a.Destroy();
    }

    void Print()
    {
        a.Print();
    }

    int Child(int i)
    {
        return (2*i)+1;
    }

    int Parent(int i)
    {
        return (i-1)/2;
    }

    void MoveUp(int ind)
    {
        int temp;
        while (isBefore(a[ind], a[Parent(ind)]))
        {
            temp = a[ind];
            a[ind] = a[Parent(ind)];
            a[Parent(ind)] = temp;
            ind = Parent(ind);
        }
    }

    void MoveDown(int ind)
    {
        while (Child(ind) < a.n)
        {
            int temp;
            if (Child(ind) + 1 < a.n && isBefore(a[Child(ind)+1], a[ind]) && isBefore(a[Child(ind) + 1], a[Child(ind)]) )
            {
                temp = a[ind];
                a[ind] = a[Child(ind)+1];
                a[Child(ind)+1] = temp;
                ind = Child(ind) + 1;
            }
            else if (isBefore(a[Child(ind)], a[ind]))
            {
                temp = a[ind];
                a[ind] = a[Child(ind)];
                a[Child(ind)] = temp;
                ind = Child(ind);
            }
            else
            {
                break;
            }
        }
    }

    void Add(Elem e)
    {
        a.AddLast(e);
        MoveUp(a.n -1 );
    }

    Elem GetFirst()
    {
        return a[0];
    }

    Elem RetrieveFirst()
    {
        Elem obj = a[0];
        a[0] = a[a.n - 1];
        a.RemoveLast();
        MoveDown(0);
        return obj;
    }
};

struct Edge
{
    int		v; //node
    int		w; //weight
};

struct Node
{
    Array<Edge> adj;

    void Initialize() { adj.Initialize();}
    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; i++)
        {
            nodes[i].Initialize();
        }
    }
    void Destroy()
    {
        for (int i = 0; i < n; i++)
        {
            nodes[i].Destroy();
        }
        delete []nodes;
    }
    /*void Add(Edge src, Edge dst)
    {
        nodes[src.v].adj.AddLast(dst);
        nodes[dst.v].adj.AddLast(src);
    }*/
};

bool IsBefore(Edge& a, Edge& b)
{
    return a.w<b.w;
}

int main()
{
    /*Heap<Edge> heap;
    heap.Initialize(IsBefore, 5);
    Edge edge;
    edge.v = 1;
    edge.w = 5;
    heap.Add(edge);
    heap.Destory();*/
    int N, n, m, S, T, edge1, edge2, edgeW;
    Edge edge;
    Heap<Edge> heap;
    Graph graph;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> n >> m >> S >> T;
        heap.Initialize(IsBefore, n);
        for (int j = 0; j < m; j++)
        {
            cin >> edge1 >> edge2 >> edgeW;
            edge.v = edge1;
            edge.w = edgeW;
            heap.Add(edge);
        }

    }
    return 0;
}

