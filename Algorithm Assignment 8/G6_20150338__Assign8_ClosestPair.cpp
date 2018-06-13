// GROUP:   6
// ID:      20150338
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name1:   Mohamed Samy Sayed
// Name2:   XX SECOND STUDENT FULL NAME
// UVA Username: m.shaar97

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
#include <iomanip>

using namespace std;


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

struct Point
{
	double x,y;
};

bool IsBeforeX(Point& a, Point& b){ return a.x > b.x;}
bool IsBeforeY(Point& a, Point& b){ return a.y > b.y;}

double dist(Point& a, Point& b){ return sqrt(( (b.x - a.x)*(b.x - a.x) ) + ( (b.y - a.y)*(b.y - a.y) ));}

double BruteForce(Point *p, int n)
{
    double min = 10000;
    double NewDist;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            NewDist = dist(p[i], p[j]);             //stored distance in a variable
            if (NewDist < min){ min = NewDist;}
        }
    }
    return min;
}

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
    if (n <= 3){ return BruteForce(p, n);}
    int mid = n/2, j = 0;
    Point *strip;
    strip = new Point[n]; //changed
    Point midpoint = p[mid];
    double dl = ClosestPair(p, mid);
    double dr = ClosestPair(p + mid, n-mid);
    double d = dl > dr ? dr:dl;
    for (int i = 0; i < n; i++)
    {
        if(abs(p[i].x - midpoint.x) < d){ strip[j++] = p[i];}
    }
    MergeSort(strip, j, IsBeforeY);
    double d2 = BruteForce(strip, j);
    delete[] strip;
    return d2 > d ? d : d2;
}


int main()
{
	int n;
    double a, b, d;
    Point *points;
    Point temp;
    while (true)        //changed while condition from (cin >> n && n)
    {
        cin >> n;
        if (n == 0) break;
        points = new Point[n];
        for (int i = 0; i < n; i++)
        {
            cin >> a >> b;
            temp.x = a;
            temp.y = b;
            points[i] = temp;
        }
        MergeSort(points, n, IsBeforeX);
        d = ClosestPair(points, n);
        if (d < 10000) {cout << fixed << setprecision(4) << d  << endl;}
        else { cout << "INFINITY" << endl;}
    }
    delete[] points; // added delete points
    return 0;
}
