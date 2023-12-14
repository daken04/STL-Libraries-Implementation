#include<iostream>
using namespace std;

bool choice = true; //for max heap

class priority_queue{
    public:
    int* point;
    int cap = 0;
    int siz = 0;

    priority_queue()
    {
        siz = 0;
        cap = 0;
    }

    void implementmin()
    {
        int index = siz-1;

        if(index==0)
        {
            return;
        }

        int parent = (index-1)/2;

        while(index!=0 && point[index]<point[parent])
        {
            int temp = point[index];
            point[index] = point[parent];
            point[parent] = temp;

            index = parent;
            parent = (index-1)/2;
        }

        return;
    }

    void implementmax()//max heap
    {
        int index = siz-1;

        if(index==0)
        {
            return;
        }

        int parent = (index-1)/2;

        while(index!=0 && point[index]>point[parent])
        {
            int temp = point[index];
            point[index] = point[parent];
            point[parent] = temp;

            index = parent;
            parent = (index-1)/2;
        }

        return;
    }

    void pop()
    {
        if(cap==0)
        {
            cout<<endl;
            cout<<"capacity is 0"<<endl;
            return;
        }

        if(siz==0)
        {
            cout<<"No elements in heap"<<endl;
            return;
        }

        point[0] = point[siz-1];
        siz--;

        if(choice)
        {
            int parent = 0;

            while((2*parent+1<siz && point[parent]<point[2*parent+1]) || (2*parent+2<siz && point[parent]<point[2*parent+2]))
            {
                int index = 2*parent+1;

                if(2*parent+2 < siz && point[2*parent+1]<point[2*parent+2])
                {
                    index = 2*parent+2;
                }

                int temp = point[parent];
                point[parent] = point[index];
                point[index] = temp;

                parent = index;
            }
        }
        else
        {
            int parent = 0;

            while((2*parent+1<siz && point[parent]>point[2*parent+1]) || (2*parent+2<siz && point[parent]>point[2*parent+2]))
            {
                int index = 2*parent+1;

                if(2*parent+2 < siz && point[2*parent+1]>point[2*parent+2])
                {
                    index = 2*parent+2;
                }

                int temp = point[parent];
                point[parent] = point[index];
                point[index] = temp;

                parent = index;
            }
        }

        return;
    }

    void push(int x)
    {
        if(cap==0)
        {
            int* temppoint = new int[1];
            cap = 1;
            siz = 1;
            point = temppoint;

            point[0] = x;
            return;
        }

        if(siz==0)
        {
            siz++;
            point[0] = x;
            return;
        }

        if(siz<cap)
        {
            point[siz] = x;
            siz++;
        }
        else if(siz==cap)
        {
            int* temppoint;
            temppoint = new int[2*cap];

            int i = 0;
            int tempsize = siz;
            while(tempsize--)
            {
                temppoint[i] = point[i];
                i++;
            }

            delete[] point;
            point = temppoint;
            cap = 2*siz;
            point[siz] = x;
            siz++;
        }

        if(choice)
        {
            implementmax();
        }
        else
        {
            implementmin();
        }
        
    }

    int size()
    {
        return siz;
    }

    int top()
    {
        if(siz==0)
        {
            cout<<"size is zero"<<endl;
            return 0;
        }
        return point[0];
    }

    bool empty()
    {
        if(siz==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};

int main()
{
    priority_queue p;

    cout<<"Options to implement priority queue:"<<endl;
    cout<<"Press 0 for min heap"<<endl;
    cout<<"Press 1 for max heap"<<endl;
    cout<<"Enter:";
    int input;
    cin>>input;

    cout<<endl;

    if(input==0)
    {
        choice = false;
    }

    while(1)
    {
        int option;
        cin>>option;

        if(option==0)
        {
            break;
        }
        else if(option==1)
        {
            cout<<"Current size is:"<<p.size()<<endl;
        }
        else if(option==2)
        {
            int x;
            cin>>x;

            p.push(x);
        }
        else if(option==3)
        {
            cout<<"Top element is:"<<p.top()<<endl;
        }
        else if(option==4)
        {
            cout<<"Top element has been poped out of the priority queue"<<endl;
            p.pop();
        }
        else if(option==5)
        {
            cout<<boolalpha<<p.empty()<<endl;
        }
        else
        {
            cout<<"Invalid Input"<<endl;
        }
    }
}