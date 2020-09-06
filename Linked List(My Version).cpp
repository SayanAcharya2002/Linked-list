#include <iostream>
using namespace std;
#define lsize unsigned int
template <class T>
class listy
{
private:
    lsize counter=0;
    struct node
    {
        struct node* p=nullptr;
        T data;
        node(T data_input)
        {
            data=data_input;
        }
    };
    node* starter=nullptr;
    node* ender=nullptr;
    auto get_pointer(lsize pos);
public:
    listy(T);
    listy();
    ~listy();
    void add(T);
    void add(T*,lsize);
    ostream& print();
    void pop();
    T at(lsize);
    void deletion(lsize=-1);
    void insert(lsize,T);
    void insert(lsize,T*,lsize);
    lsize size();

    T& operator[](lsize);
};
//template <class T>
//listy<T>::node

template <class T>
listy<T>::listy(T input)
{
    starter=new struct node(input);
    ender=starter;
    counter++;
}
template <class T>
listy<T>::listy(){}

template <class T>
void listy<T>::add(T input)
{
    if(counter==0)
    {
        starter=new struct node(input);
        ender=starter;
        counter++;
    }
    else
    {
        ender->p=new struct node(input);
        ender=ender->p;
        counter++;
    }
}
template <class T>
ostream& listy<T>::print()
{
    cout<<"[ ";
    struct node* temp=starter;
    for(lsize i=0;i<counter;i++)
    {
        cout<<temp->data<<" ";
        temp=temp->p;
    }
    cout<<"] size: "<<counter;
    return cout;
}
template <class T>
T listy<T>::at(lsize pos)
{
    struct node* temp=starter;
    for(lsize i=0;i<pos;i++)
    {
        temp=temp->p;
    }
    return temp->data;
}
template <class T>
T& listy<T>::operator[](lsize pos)
{
    struct node* temp=starter;
    for(lsize i=0;i<pos;i++)
    {
        temp=temp->p;
    }
    return temp->data;
}
//use of auto function because i could not compile listy<T>::node* for some reason
template <class T>
auto listy<T>::get_pointer(lsize pos)
{
    node* temp=starter;
    for(lsize i=0;i<pos;i++)
    {
        temp=temp->p;
    }
    return temp;
}
template <class T>
void listy<T>::pop()
{
    if(counter!=1)
    {
        node* temp=get_pointer(counter-2);
        delete ender;
        ender=temp;
        counter--;
    }
    else
    {
        delete starter;
        starter=nullptr;
        ender=nullptr;
    }
}
//THIS ONE MIGHT THROW TROUBLE IN FUTURE. BE CAREFUL//
template <class T>
void listy<T>::deletion(lsize pos)
{
    if(pos==-1&&counter==1)
    {
        delete starter;
        starter=nullptr;
        ender=nullptr;
        counter--;
    }
    else if(pos==-1)
    {
        node*temp=starter;
        node* temp1;
        for(lsize i=0;i<counter;i++)
        {
            temp1=temp;
            temp=temp->p;
            delete temp1;
        }
        starter=nullptr;
        ender=nullptr;
        counter=0;
    }
    else if(pos==0)
    {
        node * temp=starter;
        starter=starter->p;
        delete temp;
        counter--;
    }
    else if(pos!=counter-1)
    {
        node * temp=get_pointer(pos-1);
        node * temp1=temp->p;
        temp->p=temp->p->p;
        delete temp1;
        counter--;
    }
    else
    {
        ender=get_pointer(counter-2);
        delete ender->p;
        ender->p=nullptr;
        counter--;
    }
}
template <class T>
listy<T>::~listy()
{
    deletion();
}
template <class T>
void listy<T>::insert(lsize pos,T input)
{
    if(pos==counter)
        add(input);
    else if(pos==0)
    {
        node* temp=starter;
        starter=new node(input);
        starter->p=temp;
        counter++;
    }
    else
    {
        node* temp=get_pointer(pos-1);
        node* temp1=temp->p;
        temp->p=new  node (input);
        temp->p->p=temp1;
        counter++;
    }

}
template <class T>
void listy<T>::add(T* arr,lsize n)
{
    for(lsize i=0;i<n;i++)
        add(*(arr+i));
}

template <class T>
void listy<T>::insert(lsize pos,T*arr,lsize n)
{
    if(pos==0&&n>1)
    {
        node*temp=starter;
        node*temp1=starter;
        for(lsize i=0;i<n-1;i++)
        {
            if(i==0)
            {
                starter=new node(arr[0]);
                temp=starter;
                counter++;
                cout<<temp->data<<endl;
            }
            else
            {
                temp->p=new node(arr[i]);
                counter++;
                temp=temp->p;
                cout<<temp->data<<endl;
            }
        }
        temp->p=new node(arr[n-1]);
        temp->p->p=temp1;
        counter++;
        cout<<temp->data<<endl;
        cout<<counter<<endl;
    }
    else if(pos==0 && n==1)
    {
        insert(0,arr[0]);
    }
    else if(pos==counter && n!=0)
    {
        add(arr,n);
    }
    else if(n!=0)
    {
        node* temp=get_pointer(pos-1);
        node* temp1=temp->p;
        for(lsize i=0;i<n;i++)
        {
            temp->p=new node(arr[i]);
            counter++;
            temp=temp->p;
        }
        temp->p=temp1;
    }
}
template <class T>
lsize listy<T>::size()
{
    return counter;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{

    int* arr= new int [6];
    for(int i=0;i<6;i++)
        arr[i]=i+1;
    int arr1[]={12,13,14,15};
    listy<int> li(10);
    li.add(11);
    li.print()<<endl;
    li.add(arr1,4);
    li.print()<<endl;
    li.insert(4,123);
    li.print()<<endl;
    li.insert(3,arr,6);
    li.print()<<endl;
    li.deletion(6);
    li.print()<<endl;
    cout<<li.size()<<endl;
    li.deletion();
    li.print()<<endl;
    return 0;
}
