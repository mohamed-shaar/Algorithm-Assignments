// GROUP:   6
// ID:      20150338
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Mohamed Samy Sayed
// UVA Username: m.shaar97

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
void initialize(int N, int W)
{
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            T1[i][j] = -1;
        }
    }
}
int Knapsack1(int N, int W)
{
    if(N==0)
    {
        T1[N][W] = 0;
        return 0;
    }
    if (T1[N][W] >= 0)
    {
        return T1[N][W];
    }
    int ret = Knapsack1(N-1, W);
    int cv = a[N-1].v, cw = a[N-1].w;
    if (cw <= W)
    {
        int r = cv + Knapsack1(N-1, W-cw);
        if (r >  ret) { ret = r;}
    }
    T1[N][W] = ret;
    return ret;
}
int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
    initialize(N, W);
    return Knapsack1(N, W);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W)// Bottom-up, do not save space
{
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (i==0)
            {
                T2[i][j] = 0;
                continue;
            }
            int ret = T2[i-1][j];
            int cv = a[i-1].v;
            int cw = a[i-1].w;
            if (cw <= j)
            {
                int r = cv + T2[i-1][j-cw];
                if (r > ret)
                {
                    ret = r;
                }
            }
            T2[i][j] = ret;
        }
    }
    return T2[N][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
    int temp = 0;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (i == 0)
            {
                T3[temp][j] = 0;
                continue;
            }
            T3[temp][j] = T3[1-temp][j];
            int cv = a[i-1].v;
            int cw = a[i-1].w;
            if (cw <= j)
            {
                int r = cv + T3[1-temp][j-cw];
                if (r > T3[temp][j])
                {
                    T3[temp][j] = r;
                }
            }
        }
        temp = 1 - temp;
    }
    return T3[1-temp][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
    for (int n = 0; n <= N; n++)
    {
        for (int w = W; w >= 0 ; w--)
        {
            if (n == 0)
            {
                T4[w] = 0;
                continue;
            }
            //T4[w] = T4[w];
            int cv = a[n-1].v;
            int cw = a[n-1].w;
            if (cw <= w)
            {
                int r = cv + T4[w-cw];
                if (r >T4[w])
                {
                    T4[w] = r;
                }
            }
        }
    }
    return T4[W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
    //return ComputeKnapsack1(N,W);
    //return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
    return ComputeKnapsack4(N,W);
}

void Compute() // Get input and call ComputeKnapsack() whenever needed
{
    int n, e, P, W, G, MW, result;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        result = 0;
        cin >> e;
        for (int j = 0; j < e; j++)
        {
            cin >> P >> W;
            a[j].v = P;
            a[j].w = W;
        }
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
    Compute();
    return 0;
}