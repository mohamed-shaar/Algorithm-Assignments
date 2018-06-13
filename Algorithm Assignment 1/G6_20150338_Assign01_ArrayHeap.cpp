// GROUP:   6
// ID:      20150338
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Mohamed Samy Sayed

#include <iostream>
#include <cmath>

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
    Array<Elem> a;
    bool (*isBefore)(int &a, int &b);

    void Initialize(bool (*_isBefore)(int &a, int &b))
    {
        a.Initialize();
        isBefore = _isBefore;
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
        //cout << a[0] << endl;
        Elem obj = a[0];
        a[0] = a[a.n - 1];
        a.RemoveLast();
        MoveDown(0);
        return obj;
    }
};

bool IsBeforeInt(int &a, int&b)
{
    return a < b;
}

int main() {
    int size, input;
    Array<int> CostArray;
    CostArray.Initialize();
    while (true)
    {
        cin >> size;
        Heap<int> inputheap;
        inputheap.Initialize(IsBeforeInt);
        if (size == 0)
        {
            inputheap.Destory();
            break;
        }

        for (int i = 0; i < size; i++)
        {
            cin >> input;
            inputheap.Add(input);
        }
        int temp1, temp2, sum, totalcost = 0;
        for (int j = 0; j < size - 1; j++)
        {
            temp1 = inputheap.RetrieveFirst();
            temp2 = inputheap.RetrieveFirst();

            sum = temp1 + temp2;
            totalcost += sum;

            inputheap.Add(sum);
        }
        CostArray.AddLast(totalcost);
    }
    CostArray.Print();
    CostArray.Destroy();
    return 0;
}