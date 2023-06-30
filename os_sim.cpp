#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct node
{
    int id;
    int priority;
    int arrival;
    int burst;
};

bool compare(node a, node b)
{
    if(a.priority<b.priority) return true;
    if(a.priority>b.priority) return false;
    if(a.arrival<b.arrival) return true;
    return false;
}

bool sortcompare(node a, node b)
{
    if(a.arrival<b.arrival) return true;
    if(a.arrival>b.arrival) return false;
    
    if(a.priority<b.priority) return true;
    return false;
}

void swap(node &a, node &b)
{
    node t = a;
    a = b;
    b = t;

    return;
}

void kshitiz_sort(node* arr, int n)
{
    for(int ii=0; ii<n; ii++)
    {
        int jj=ii, prev = arr[ii].arrival, min=arr[ii].priority, minIndex = ii;

        while(jj<n)
        {
            if(arr[jj].arrival!=prev)
            {
                break;
            }
            if(arr[jj].priority<min)
            {
                min = arr[jj].priority;
                minIndex = jj;
            }
            jj++;
        }
        
        node temp = arr[minIndex];
        
        for(int kk = minIndex; kk>ii; kk--)
        {
            arr[kk] = arr[kk-1];
        }
        arr[ii] = temp;
        
        ii = jj-1;
        
    }
    
    return;
}

void removeMin(vector <node> &pq)
{
    int index = 1;
   
    while(2*index <= pq.size())
    {
        int nextIn = 2*index;
       
        if(nextIn+1 <=pq.size())
        {
            if(!compare(pq[nextIn-1], pq[nextIn])) nextIn++;
        }
       
       pq[index-1] = pq[nextIn-1];

       index = nextIn;
    }

    if(index<pq.size())
    {
        pq[index-1] = pq[index];
    }

    pq.pop_back();

    return;
   
}

void hinsert(vector <node> &pq, node x)
{
    pq.push_back(x);
    int index= pq.size();

    while(index>1)
    {
        if(compare(pq[index/2 -1], pq[index-1])) break;
        else
        {
            swap(pq[index/2 -1], pq[index-1]);
        }

        index/=2;
    }

    return;
}

void preorder_print(vector <node> &pq, int index)
{
    if(2*index>pq.size())
    {
        cout<<pq[index-1].id<<" ";
        return;
    }

    cout<<pq[index-1].id<<" ";
    preorder_print(pq, 2*index);
    if(2*index+1<=pq.size())
    {
        preorder_print(pq, 2*index + 1);
    }

    return;
}

int main()
{
    int n, t=0;
    cin>>n;
   
    bool free = true;
   
    node arr[n], current;
   
    vector <node> pq;
    vector <int> pid, ptime;
   
    for(int ii=0; ii<n; ii++)
    {
        cin>>arr[ii].id>>arr[ii].priority>>arr[ii].arrival>>arr[ii].burst;
    }

    kshitiz_sort(arr, n);
    // ;)
   
    for(int ii=0; ii<n; ii++)
    {
        if(pq.size()==0 && free)
        {
            t = arr[ii].arrival;
            current = arr[ii];
            free = false;
            pid.push_back(current.id);
        }
        else if(pq.size()==0 && !free)
        {
            if(t+current.burst <=arr[ii].arrival)
            {
                t+=current.burst;
                ptime.push_back(t);
               
                t = arr[ii].arrival;
                current = arr[ii];
                pid.push_back(current.id);
            }
            else
            {
                if(compare(current, arr[ii]))
                {
                    pq.push_back(arr[ii]);
                }
                else
                {
                    current.burst = t+current.burst - arr[ii].arrival;
                    t = arr[ii].arrival;
                    ptime.push_back(t);
                
                    pq.push_back(current);
                    current = arr[ii];
                    pid.push_back(current.id);
                }
            }
        }
        else
        {
            if(t+current.burst <arr[ii].arrival)
            {
                t+=current.burst;
                ptime.push_back(t);
               
                
                current = pq[0];
                preorder_print(pq, 1);
                cout<<endl;
                removeMin(pq);
                pid.push_back(current.id);
                ii--;
                continue;
            }
            else if(t+current.burst == arr[ii].arrival)
            {
                hinsert(pq, arr[ii]);
                t+=current.burst;
                ptime.push_back(t);

                current = pq[0];
                preorder_print(pq, 1);
                cout<<endl;
                removeMin(pq);
                pid.push_back(current.id);
            }
            else
            {
                if(compare(current, arr[ii]))
                {
                    hinsert(pq, arr[ii]);
                }
                else
                {
                    current.burst = t+current.burst - arr[ii].arrival;
                    t = arr[ii].arrival;
                    ptime.push_back(t);
                
                    hinsert(pq, current);
                    current = arr[ii];
                    pid.push_back(current.id);
                }
            }
        }
    }

    if(!free)
    {
        t+=current.burst;
        ptime.push_back(t);
    }

    while(pq.size())
    {
        current = pq[0];
        pid.push_back(current.id);
        preorder_print(pq, 1);
        cout<<endl;
        removeMin(pq);

        t+=current.burst;
        ptime.push_back(t);
    }

    for(int ii=0; ii<pid.size(); ii++) cout<<pid[ii]<<" ";
    cout<<endl;
    for(int ii=0; ii<ptime.size(); ii++) cout<<ptime[ii]<<" ";
    cout<<endl;
    return 0;
}
