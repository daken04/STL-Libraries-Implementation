#include <iostream>
using namespace std;

using namespace std;
template <typename T>
class MyDeque{
	public:
            
        T *point;
        int start = -1;
        int end = -1;
        int siz = 0;
        int cap = 0;
        
        MyDeque()
        {
            siz = 0;
            cap = 0;
        }
        
        MyDeque(int n)
        {
            point = new T[n];
            siz=0;
            cap =n;
        }
        
        MyDeque(int n,T x)
        {
            point = new T[n];
            for(int i=0;i<n;i++)
            {
                point[i] = x;
            }
            
            start=0;
            end=n-1;
            siz =n;
            cap = n;
        }
        
        bool push_back(T x)
        {
            if(cap==0)
            {
            	T* temppoint = new T[1];
            	cap = 1;
            	siz = 1;
            	start = 0;
            	end = 0;
            	delete[] point;
                point = temppoint;
                
                point[0] = x;
                return true;
            }
            
            if(siz==0)
            {
                start = 0;
                end = 0;
                point[0] = x;
                return true;
            }
                    
            if(siz<cap)
            {
                end = (end+1)%cap;
                if(start==-1)
                {
                    start=0;
                }
                point[end] = x;
                siz++;
                return true;
            }
            else if(siz==cap)
            {
                T* temppoint;
                temppoint = new T[2*cap];
                
                int i=0;
                int j=start;
                int tempsize=siz;
                
                while(tempsize--)
                {
                    temppoint[i] = point[j];
                    
                    i++;
                    j = (j+1)%cap;
                }
                
                delete[] point;
                point = temppoint;
                start = 0;
                end = siz-1;
                cap = 2*siz;
                end = (end+1)%cap;
                point[end] = x;
                siz++;
                return true;
            }
            else{
                return false;
            }
        }
        
        bool pop_back()
        {
            if(start==-1)
            {
                return false;
            }
            else if(end<=cap)
            {
                if(start==0 && end==0)
                {
                    start =-1;
                }
                end--;
                siz--;
                return true;
            }
            else
            {
                return false;
            }
        }
        
        bool push_front(T x)
        {
            if(cap==0)
            {
            	T* temppoint = new T[1];
            	cap = 1;
            	siz = 1;
            	start = 0;
            	end = 0;
            	delete[] point;
                point = temppoint;
                
                point[0] = x;
                return true;
            }
            
            if(siz==0)
            {
                start = 0;
                end = 0;
                point[0] = x;
                return true;
            }
            
            int index = start-1;
            
            if(index==-1)
            {
                index = cap-1;
            }
            
            if(index==end)
            {
                T* temppoint;
                temppoint = new T[2*cap];
                
                int i=0;
                int j=start;
                int tempsize=siz;
                
                while(tempsize--)
                {
                    temppoint[i] = point[j];
                    
                    i++;
                    j = (j+1)%cap;
                }
                
                delete[] point;
                point = temppoint;
                end = siz-1;
                cap = 2*siz;
                start = cap-1;
                point[start] = x;
                siz++;
                return true;
            }
            else
            {
                point[index]=x;
                siz++;
                start = index;
                return true;
            }
        }
        
        bool pop_front()
        {
            if(start==-1)
            {
                return false;
            }
            else
            {
                if(start==0 && siz==1)
                {
                    siz=0;
                    start=-1;
                    end=-1;
                }
                else
                {
                    start = (start+1)%cap;
                    siz--;
                }
                return true;
            }
        }
        
        T front()
        {
            T ele;
            if(start==-1)
            {
                return ele;
            }
            else
            {
                return point[start];
            }
        }
        
        T back()
        {
            T ele;
            if(end==-1)
            {
                return ele;
            }
            else
            {
                return point[end];
            }
        }
        
        T &operator[](int n)
        {
            T ele;
            if(n>=0)
            {
                if(n>=siz)
                {
                    return ele;
                }
                else
                {
                    int index = start;
                    
                    while(n--)
                    {
                        index = (index+1)%cap;
                    }
                    
                    return point[index];
                }
            }
            else
            {
                int t = cap+n;
                
                if(t<0)
                {
                    return ele;
                }
                else
                {
                    int index = start;
                    
                    while(t--)
                    {
                        index = (index+1)%cap;
                    }
                    
                    return point[index];
                }
            }
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
        
        int size()
        {
            return siz;
        }
        
        int capacity()
        {
            return cap;
        }
        
        void resize(int n)
        {
            T* temppoint;
            temppoint = new T[n];
            
            int i=0;
            int j=start;
            int tempsize;
            
            if(n>siz)
            {
                tempsize = siz;
            }
            else
            {
                tempsize = n;
            }
            
            while(tempsize--)
            {
                temppoint[i] = point[j];
                
                i++;
                j = (j+1)%cap;
            }
            
            delete[] point;
            point = temppoint;
            start = 0;
            end = n-1;
            cap = n;
            siz=n;
        }
        
        void resize(int n,T d)
        {
            T* temppoint;
            temppoint = new T[n];
            
            int i=0;
            int j=start;
            int tempsize;
            bool need = false;
            int trav;
            
            if(n>siz)
            {
                tempsize = siz;
                need=true;
                trav=siz;
            }
            else
            {
                tempsize = n;
            }
            
            while(tempsize--)
            {
                temppoint[i] = point[j];
                
                i++;
                j = (j+1)%cap;
            }
            
            if(need)
            {
                for(int k=trav;k<n;k++)
                {
                    temppoint[k] = d;
                }
            }
            
            delete[] point;
            point = temppoint;
            start = 0;
            end = n-1;
            cap = n;
            siz=n;
        }
        
        void reserve(int n)
        {
            if(n<=cap)
            {
                return;
            }
            
            T* temppoint;
            temppoint = new T[n];
            
            int i=0;
            int j=start;
            int tempsize=siz;
            
            while(tempsize--)
            {
                temppoint[i] = point[j];
                
                i++;
                j = (j+1)%cap;
            }
            
            delete[] point;
            point = temppoint;
            start = 0;
            end = siz-1;
            cap = n;
        }
        
        void shrink_to_fit()
        {
            T* temppoint;
            temppoint = new T[siz];
            
            int i=0;
            int j=start;
            int tempsize=siz;
            
            while(tempsize--)
            {
                temppoint[i] = point[j];
                
                i++;
                j = (j+1)%cap;
            }
            
            delete[] point;
            point = temppoint;
            start = 0;
            end = siz-1;
            cap = siz;
        }
        
        void clear()
        {
            start = -1;
            end = -1;
            siz = 0;
        }
};

int main()
{
    MyDeque<string> dq;//here
    string s;//here
    
    while(1)
    {
        int input;
        cin>>input;
        
        if(input==0)
        {
            break;
        }
        else if(input==1)
        {
            dq = MyDeque<string>();//here
        }
        else if(input==2)
        {
            int n;
            cin>>n;
            
            dq = MyDeque<string>(n); //here
        }
        else if(input==3)
        {
            int n;
            cin>>n;
            cin>>s;
            
            dq = MyDeque<string>(n,s); //here
        }
        else if(input==4)
        {
            cin>>s;
            
            cout<< boolalpha <<dq.push_back(s)<<endl;
        }
        else if(input==5)
        {
            cout<< boolalpha <<dq.pop_back()<<endl;
        }
        else if(input==6)
        {
            cin>>s;
            
            cout<<boolalpha<<dq.push_front(s)<<endl;
        }
        else if(input==7)
        {
            cout<<boolalpha<<dq.pop_front()<<endl;
        }
        else if(input==8)
        {
            cout<<dq.front()<<endl;
        }
        else if(input==9)
        {
            cout<<dq.back()<<endl;
        }
        else if(input==10)
        {
            int n;
            cin>>n;
            cout<<endl;
            
            cout<<dq[n]<<endl;
        }
        else if(input==11)
        {
            cout<<boolalpha<<dq.empty()<<endl;
        }
        else if(input==12)
        {
            cout<<dq.size()<<endl;
        }
        else if(input==13)
        {
            int n;
            cin>>n;
            dq.resize(n);
        }
        else if(input==14)
        {
            int n;
            cin>>n;
            cin>>s;
            
            dq.resize(n,s);
        }
        else if(input==15)
        {
            int n;
            cin>>n;
            
            dq.reserve(n);
        }
        else if(input==16)
        {
            dq.shrink_to_fit();
        }
        else if(input==17)
        {
            dq.clear();
        }
        else if(input==18)
        {
            cout<<dq.capacity()<<endl;
        }
        
    }       
    
}
