// GROUP:   6
// ID:      20150338
// Assign:  13
// Assign:  8queens
// UVA:     11195
// Name:    Mohamed Samy Sayed
// UVA Username: m.shaar97

#include <iostream>

#define MAX_SIZE 16

using namespace std;

int num_sols;
int n;
//bool col_taken[MAX_SIZE];
char board[MAX_SIZE][MAX_SIZE];
bool fdiagonal_taken[MAX_SIZE];
bool bdiagonal_taken[MAX_SIZE];

int F[MAX_SIZE+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_SIZE+1]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
    int i;
    for(i=0;i<n;i++) F[i]=i+1; F[n]=0;
    for(i=n;i>0;i--) B[i]=i-1; B[0]=n;
}

void Backtrack(int r)
{
    if (r==n)
    {
        num_sols++;
        return;
    }
    for (int c = F[0]; c != 0 ; c = F[c])
    {
        if(!fdiagonal_taken[r-c + (n -1)] && !bdiagonal_taken[r+c] && board[r][c-1]!='*')
        {
            fdiagonal_taken[r-c + (n -1)] = true;
            bdiagonal_taken[r+c] = true;
            Remove(c);
            Backtrack(r + 1);
            Restore(c);
            fdiagonal_taken[r-c + (n -1)] = false;
            bdiagonal_taken[r+c] = false;
        }
    }
}
void ComputeCore()
{
    num_sols = 0;
    InitDancingLinks(n);
    Backtrack(0);
}

void Compute()
{
    int counter = 1;
    while(true)
    {
        cin >> n;
        if (n == 0)
        {
            break;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> board[i][j];
            }
        }
        ComputeCore();
        cout << "Case :" << counter++ << " " << num_sols << endl;
    }
}
int main()
{
    Compute();
    return 0;
}