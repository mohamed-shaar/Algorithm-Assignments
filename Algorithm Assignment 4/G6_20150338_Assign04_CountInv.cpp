// GROUP:   6
// ID:      20160338
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Mohamed Samy Sayed

#include <iostream>

using namespace std;


bool IsBeforeInt(int &a, int&b)
{
    return a < b;
}

template <class type>
long long Merge(type* a, int n, bool (*isBefore)(type&,type&))
{
    int mid = n/2;
    int i=0, j = mid;
    long long countinversion = 0;
    type *t = new type[n];
    for (int k = 0; k < n; k++)
    {
        if ( j==n || i < mid && isBefore(a[i], a[j]))
        {
            t[k] = a[i++];
        }
        else
        {
            countinversion += (mid-i);
            t[k] = a[j++];
        }
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = t[i];
    }
    delete[] t;
    return countinversion;
}

template <class type>
long long MergeSort(type *a, int n, bool (*isBefore)(type&, type&))
{
    int mid = n/2;
    if (n <= 1)
    {
        return 0;
    }

    long long counter = MergeSort<type>(a, mid, isBefore);
    counter += MergeSort<type>(a+mid, n-mid, isBefore);
    counter +=Merge<type>(a, n, isBefore);
    return counter;

}


int main()
{
    int n, temp;
    int *a;
    while (cin >> n && n)
    {
        a = new int[n];
        for (int i = 0; i < n; i++)
        {
            cin >> temp;
            a[i] = temp;
        }
        long long c = MergeSort<int>(a, n, IsBeforeInt);
        cout << c << endl;
    }
    return 0;
}