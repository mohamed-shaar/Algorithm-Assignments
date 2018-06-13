// GROUP:   6
// ID:      20150338
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Mohamed Samy Sayed
#include <iostream>

using namespace std;

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n)
    {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];
        for (int i = 0; i < n; i++)
        {
            parent[i] = -1;
            num_nodes[i] = 1;
        }
    }
    void Destroy()
    {
        delete[] parent;
        delete[] num_nodes;
    }

    int Find(int i)
    {
        /*int p = i;
        while (parent[p] != i)
        {
            p = parent[p];
        }
        return p;*/
        if (parent[i]==-1){ return i;}
        return Find(parent[i]);
    }

    bool Union(int i, int j)
    {
        int a=Find(i), b=Find(j);
        if(a==b)
        {
            return false;
        }
        if(num_nodes[a] >= num_nodes[b])
        {
            parent[b]=a;
            num_nodes[a]+=num_nodes[b];
        }
        else
        {
            parent[a]=b;
            num_nodes[b]+=num_nodes[a];
        }
        return true;
    }
};

template<class Type>
void Merge(Type* a, int n, bool (*isBefore)(Type& a, Type& b))
{
    int mid = n/2;
    int i=0, j = mid; //countinversion = 0;
    Type *t = new Type[n];
    for (int k = 0; k < n; k++)
    {
        if ( j==n || i < mid && isBefore(a[i], a[j]))
        {
            t[k] = a[i++];
        }
        else
        {
            //countinversion += (mid-i);
            t[k] = a[j++];
        }
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = t[i];
    }
    delete[] t;
    //return countinversion;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*isBefore)(Type& a, Type& b))
{
    int mid = n/2, counter = 0;
    if (n <= 1)
    {
        return ;
    }
    MergeSort<Type>(a, mid, isBefore);
    MergeSort<Type>(a+mid, n-mid, isBefore);
    Merge<Type>(a, n, isBefore);
}

struct Edge
{
    int u, v;   // nodes
    int w;      //weight
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
    return a.w<b.w;
}

bool IsBeforeInt(int &a, int&b)
{
    return a < b;
}

int main() {
    int n, m, input1, input2, input3, totalcost = 0 , newcost = 0;
    bool CycleCheck = false;
    while (cin >> m >> n && m) {
        DisjointSets disjointSets;
        disjointSets.Initialize(m);
        Edge edges[n];
        Edge temp;
        for (int i = 0; i < n; i++)
        {
            cin >> input1 >> input2 >> input3;
            temp.u = input1;
            temp.v = input2;
            temp.w = input3;
            edges[i] = temp;
            totalcost += input3;
        }
        MergeSort<Edge>(edges, n, IsBeforeEdge);
        for (int j = 0; j < n - 1; j++)
        {
            CycleCheck = disjointSets.Union(edges[j].u, edges[j].v);
            if (CycleCheck) { newcost += edges[j].w ;}
        }
        cout << totalcost - newcost << endl;
        totalcost = newcost = 0;

    }
    return 0;
}