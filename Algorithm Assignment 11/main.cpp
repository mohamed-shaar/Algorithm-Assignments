// GROUP:   6
// ID:      20150338
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    Mohamed Samy Sayed
// UVA Username: m.shaar97

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int s(int n, int m)
{
    if (a[n-1]==b[m-1]) return 0;
    return 1;
}

int T1[81][81];
void Initialize()
{
    for (int i = 0; i < 81; i++)
    {
        for (int j = 0; j < 81; j++)
        {
            T1[i][j] = -1;
        }
    }
}

int EditDist1(int n, int m)
{
    if (n==0 && m==0)
    {
        T1[n][m] = 0;
        return 0;
    }
    if (T1[n][m] >= 0)
    {
        return T1[n][m];
    }
    if (n==0)
    {
        T1[n][m] = 1 + EditDist1(n, m-1);//a is done continue on b
        D[n][m] = 3;
        return T1[n][m];
    }
    if (m==0)
    {
        T1[n][m] = 1 + EditDist1(n-1, m);
        D[n][m] = 2;
        return T1[n][m];
    }
    if (s(n, m)==1)
    {
        T1[n][m] = 0;
        EditDist1(n-1, m-1);
    }
    int Delete, Insert, minimum;
    Insert = 1 + EditDist1(n, m-1);
    Delete = 1 + EditDist1(n-1, m);
    minimum = s(n, m) + EditDist1(n-1, m-1);
    D[n][m] = s(n, m);
    if (minimum > Delete)
    {
        minimum = Delete;
        D[n][m] = 2;
    }
    if (minimum > Insert)
    {
        minimum = Insert;
        D[n][m] = 3;
    }
    T1[n][m] = minimum;
    return T1[n][m];
}
int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M);
{
    Initialize();
    return EditDist1(N, M);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M) // Bottom-up, do not save space
{
    /*for (int n = 0; n <= N; n++)
    {
        for (int m = 0; m <= M; m++)
        {
            if(n==0)
            {
                T2[n][m] = 0;
                continue;
            }
            if (m==0)
            {
                T2[n][m] =  1 + T2[n-1][m];
                D[n][m] = 2;
            }
            if (s(n, m) == 1)
            {
                T2[n][m] = 0;
                D[n][m] = 0;
            }
            int Minimum, Insert, Delete;
            Minimum = s(n, m) + T2[n-1][m-1];
            Insert = 1 + T2[n][m-1];
            Delete = 1 + T2[n-1][m-1];
            if (Minimum > Insert)
            {
                Minimum = Insert;
                D[n][m] = 3;
            }
            if (Minimum > Delete)
            {
                Minimum = Delete;
                D[n][m] = 2;
            }
            T2[n][m] = Minimum;
        }
    }
    return T2[N][M];*/
    for (int n = 0; n <= N; n++)
    {
        for (int m = 0; m < M; m++)
        {
            if(n==0)
            {
                T2[n][m] = m;
            }
            if (m==0)
            {
                T2[n][m] = n;
            }
            if (s(n, m)==1)
            {
                T2[n][m] = T2[n-1][m-1];
            }
            int Minimum, Insert, Delete;
            Minimum = s(n, m) + T2[n-1][m-1];
            Insert = 1 + T2[n][m-1];
            Delete = 1 + T2[n-1][m];
            if (Minimum > Insert)
            {
                Minimum = Insert;
            }
            if (Minimum > Delete)
            {
                Minimum = Delete;
            }
            T2[n][m] = Minimum;
        }
    }
    return T2[N][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M); // Bottom-up, use two rows only

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M); // Bottom-up, save maximum space

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
    int n,m;
    int oper;
};

Oper opers[81];

void EditDistSol(int N, int M) // Print the solution using D[][]
{
    int n = N, m = M, counter = 0;
    while (true)
    {
        if (n == 0 && m==0)
        {
            break;
        }
        opers[counter].n = n;
        opers[counter].m = m;
        opers[counter].oper = D[n][m];
        if (opers[counter].oper == 0)
        {
            m--;
            n--;
        }
        if (opers[counter].oper == 1)
        {
            //cout << counter+1<<" Replace "<< opers[counter].n<<"," << a[opers[counter].n]<<endl;
            counter++;
            n--;
            m--;
        }
        if (opers[counter].oper == 2)
        {
            //cout<< counter+1<<" Delete "<< opers[counter].n<<endl;
            n--;
            counter++;
        }
        if (opers[counter].oper == 3)
        {
            //cout<<counter+1<<" Insert "<< opers[counter].m  <<","<<a[opers[counter].m]<<endl;
            m--;
            counter++;
        }
    }
    for (int i = 0; i < counter; i++)
    {
        if (opers[i].oper == 1)
        {
            cout << i+1<<" Replace "<< opers[i].n<<"," << b[opers[i].n]<<endl;
        }
        if (opers[i].oper ==2)
        {
            cout<< i+1<<" Delete "<< opers[i].n<<endl;
        }
        if (opers[i].oper == 3)
        {
            cout<<i+1<<" Insert "<< opers[i].m  <<","<<b[opers[i].m]<<endl;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
    //return ComputeEditDist1(N,M);
    return ComputeEditDist2(N,M);
    //return ComputeEditDist3(N,M);
    //return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
    a[0] = 'a';
    a[1] = 'a';
    a[2] = 'a';

    b[0] = 'a';
    b[1] = 'a';
    b[2] = 'b';
    b[3] = 'a';
    b[4] = 'a';
    b[5] = 'a';
    b[6] = 'a';
    cout <<ComputeEditDist(3, 7)<<endl;
    //EditDistSol(3, 7);
    /*int cas=0;
    while(true)
    {
        a[0]=0; b[0]=0;
        if(!fgets(a,82,stdin)) break; fgets(b,82,stdin);
        a[strlen(a)-1]=0;
        b[strlen(b)-1]=0;
        if(cas) cout<<endl; // print an empty line between test cases
        int N=strlen(a), M=strlen(b);
        ComputeEditDist(N,M);
        EditDistSol(N,M);
        cas++;
    }*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign11_00526.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
