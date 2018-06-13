// GROUP:   6
// ID:      20150338
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    Mohamed Samy Sayed
// UVA Username: m.shaar97

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    int i=0, j = mid;
    Type *t = new Type[n];
    for (int k = 0; k < n; k++)
    {
        if ( j==n || i < mid && IsBefore(a[i], a[j]))
        {
            t[k] = a[i++];
        }
        else
        {
            t[k] = a[j++];
        }
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = t[i];
    }
    delete[] t;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    if (n <= 1)
    {
        return ;
    }
    MergeSort<Type>(a, mid, IsBefore);
    MergeSort<Type>(a+mid, n-mid, IsBefore);
    Merge<Type>(a, n, IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v;
    int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Obj& a, Obj& b) // return true if unit value of a is greater than unit value of b
{
    double x = a.v/(double)a.w;
    double y = b.v/(double)b.w;
    return x > y;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int best_val; // the best total value found until now

int Bound(int i, int w) // upper bound on the total value of items [i..n-1] that can fit in w
{
    int tempweight = 0, tempvalue = 0;
    for (int j = i; j < n; j++)
    {
        if (tempweight+a[j].w <= w)
        {
            tempweight += a[j].w;
            tempvalue += a[j].v;
        }
        else
        {
            double fractionValue = a[j].v/(double)a[j].w;
            int diff = w - tempweight;
            tempweight += diff;
            tempvalue += (int)(diff*fractionValue);
        }
        if (tempweight == w){ break;}
    }
    return tempvalue;
}
void BackTrack(int i, int w, int cur_val) // starting from item i, remaining weight w, cur_value of objects[0..i-1]
{
    if (i==n)
    {
        if (best_val < cur_val)
        {
            best_val = cur_val;
        }
        return;
    }
    if (Bound(i, w)+cur_val < best_val)
    {
        return;
    }
    if (a[i].w <= w)
    {
        BackTrack(i+1, w-a[i].w, cur_val+a[i].v);
    }
    BackTrack(i+1, w, cur_val);
}
int ComputeKnapsack(int N, int W) // solve knapsack of N objects and W weight
{
    n = N;
    best_val = 0;
    BackTrack(0, W, 0);
    return best_val;
}
void Compute()
{
    int testcases, e, G, MW, result = 0;
    cin >> testcases;
    for (int i = 0; i < testcases; i++)
    {
        cin >> e;
        for (int j = 0; j < e; j++)
        {
            cin >> a[j].v;
            cin >> a[j].w;
        }
        MergeSort(a, e, IsBefore);
        cin >> G;
        for (int k = 0; k < G; k++)
        {
            cin >> MW;
            result += ComputeKnapsack(e, MW);
        }
        cout << result << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign12_10130.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
