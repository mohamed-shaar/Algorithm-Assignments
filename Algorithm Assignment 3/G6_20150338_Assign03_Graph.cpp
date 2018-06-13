// GROUP:   6
// ID:      20150338
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Mohamed Samy Sayed

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

struct Node
{
	Array<int> adj;

	void Initialize()
    {
        adj.Initialize();
    }
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
    void Add(int src, int dst)
    {
        nodes[src].adj.AddLast(dst);
    }
};


template <class Type>
struct Queue
{
	int f, n;
	Type* elems;

	void Initialize(int size)
    {
        n = 0;
        f = 0;
        elems = new Type[size];
    }

	void Destroy()
    {
        delete[] elems;
    }

	void Add(Type t)
    {
        elems[n++] = t;
    }

	Type Pop()
    {
        Type t = elems[f];
        f++;
        return t;
    }

	Type Peek()
    {
        return elems[f];
    }

	int Num()
    {
        return n-f;
    }
};

void BFS(Graph& g, int s)
{
    Queue<int> q;
    q.Initialize(g.n);
    int* vis=new int[g.n];
    int* pre=new int[g.n];
    memset(vis, 0, ((sizeof(int))*g.n));
    memset(pre, -1, ((sizeof(int))*g.n));
    vis[s]=1;
    q.Add(s);
    if ( g.nodes[s].adj.n == 0)
    {
        cout << "0" << endl;
        return;
    }
    int day = 0, max = 0, counter = 0, maxday= 0;

    while(q.Num())
    {
        day++;
        int currSi = q.Num();
        counter = 0;
        while(currSi--) {
            int cur = q.Pop();
            for (int i = 0; i < g.nodes[cur].adj.n; i++) {
                int x = g.nodes[cur].adj[i];
                if (!vis[x]) {
                    vis[x] = 1;
                    pre[x] = cur;
                    q.Add(x);
                    counter++;
                }
            }
            if (counter > max)
            {
                max = counter;
                maxday = day;
            }
        }
    }
    cout << max << " "  << maxday << endl;

}

int main()
{
    int numberofworkers, numberoffriends, temp, numberoftests;
    cin >> numberofworkers;
    Graph a;
    //Array<int> arr;
    //arr.Initialize();
    a.Initialize(numberofworkers);
    for (int i = 0; i < numberofworkers; i++)
    {
        cin >> numberoffriends;
        for (int j = 0; j < numberoffriends; j++)
        {
            cin >> temp;
            a.Add(i, temp);
        }
    }
    cin >> numberoftests;
    for (int k = 0; k < numberoftests; k++)
    {
        cin >> temp;
        BFS(a, temp);
    }
    a.Destroy();
    return 0;
}
