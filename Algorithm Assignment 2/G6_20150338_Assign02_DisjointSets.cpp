// Group:   6
// ID:      20150338
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Mohamed Samy Sayed
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

int main() {
    DisjointSets a;
    Array<int> total;
    int number = 0, N = 0, M = 0, input1 = 0, input2 = 0, temp = 0;
    total.Initialize();
    cin >> number;
    for (int i = 0; i < number; i++)
    {
        cin >> N >> M;
        a.Initialize(N);
        for (int j = 0; j < M; j++)
        {
            cin >> input1 >> input2;
            a.Union(input1-1, input2-1);
        }
        temp = a.num_nodes[0];
        for (int j = 1; j <  N; j++)
        {
                if (a.num_nodes[j] > temp) {temp = a.num_nodes[j];}
        }
        total.AddLast(temp);
        a.Destroy();
    }
    total.Print();
    total.Destroy();
    return 0;
}