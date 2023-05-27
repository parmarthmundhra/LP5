#include <iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;

void bubble_sort(int *, int);
void swap(int &,int &);

void bubble_sort(int *a, int n)
{
    # pragma omp parallel for shared(a,first)
    for(int i=0;i<n;i++)
    {
        int first=i%2;
        for(int j=first;j<n-1;j+=2)
        {
            if(a[j]>a[ j+1 ])
            {
                swap(a[j],a[j+1]);
            }
        }
    }
}
void swap(int &a,int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}

int main()
{
    int *a,n;
    cout<<"\n Enter total number of element =>";
    cin>>n;
    a= new int[n]; 
    cout<<"\n Enter the elements =>";
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    
    bubble_sort(a,n);
    
    cout<<"\n Sorted Array is =>\n";
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<endl;
    }
    return 0;
}