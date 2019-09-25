#include "iostream"
#include<vector>
#include<map>
#include<set>
#include<unordered_set>
#include<unordered_map>
#include<queue>
#include<stack>
#include<list>
#include<deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Base
{
public:
    Base( )        { printf("Base::Base\n"); }
   virtual ~Base( )    { printf("Base::~Base\n"); }
    
    
    virtual void F1()    { printf("Base::F1\n"); }
    void F2()    { printf("Base::F2\n"); }
};


class Sub : public Base
{
public:
    Sub( )        { printf("Sub::Sub\n"); }
    ~Sub( )        { printf("Sub::~Sub\n"); }
    
    
    void F1()    { printf("Sub::F1\n"); }
    void F2()    { printf("Sub::F2\n"); }
};
//--------------
class Polygon{
protected:
    int width,height;
public:
    void set_values(int a,int b){width = a,height = b;}
    virtual int area(){return 0;}
    
};

class Triangle:public Polygon
{
public:
    int area(void){return width*height/2;}
};


class Rectangle:public Polygon{

public:
    int area(void){return width*height;}
};

bool myCmp(pair<int,int>a,pair<int,int>b){
    return sqrt(a.first*a.first+a.second*a.second)<sqrt(b.first*b.first+b.second*b.second);
}

bool myCmp2(int a, int b){
    return a<b;
}

bool myCmp3(string a, string b){
    return a.length()<b.length();
}



/////// self implemented hashtable---------------------------------------------------------
class Entry{
private:
    string key;
    int val;
    Entry* next;
public:
    Entry(string k, int v):key(k),val(v){};
    string getKey(){return key;}
    int getValue(){return val;}
    Entry* getNext(){return next;}
    void setNext(Entry* next){
        Entry* curNext = getNext();
        this->next = next;
        next->next = curNext;
    }
};

class HashTable{
private:
    vector<Entry*> table;
    int element_size;
    int table_size=1000;
public:
    HashTable():table(NULL),element_size(0){
        for(int i=0;i<table_size;++i)
            table.push_back(NULL);
    };
    bool equal(string k1, string k2){
        return k1==k2;
    }
    int hash(string k){
        int res=0;
        for(auto c:k)
            res+=c-'A';
        return res;
    }
    void insert(string k, int v){
        Entry* entry = new Entry(k,v);
        int index = hash(k)%table_size;
        if(table[index]==NULL)
            table[index] = entry;
        else{
            entry->setNext(table[index]);
        }
        element_size++;
    }
    
    int getValue(string k){
        int index = hash(k);
        if(table[index]==NULL)
            return NULL;
        else{
            Entry* head = table[index];
            while(head){
                if(equal(k, head->getKey()))
                    return head->getValue();
                head = head->getNext();
            }
        }
        return 0;
    }
    
    void erase(string k){
        int index = hash(k)%table_size;
        if(table[index]==NULL)
            return;
        else{
            Entry* prev = table[index];
            Entry* cur = prev;
            if(equal(k, cur->getKey())){
                delete cur;
                return;
            }
            while(cur){
                if(equal(k, cur->getKey())){
                    Entry* next = cur->getNext();
                    delete cur;
                    prev->setNext(next);
                }
                prev = cur;
                cur = cur->getNext();
            }
        }
    }
    
    
    
};
/////// self implemented hashtable---------------------------------------------------------



struct PorkType{
    int type;
    int card[5];
    void setcard(int *p)
    {
        for(int i=0;i<5;i++)
        {
            card[i]=p[i];
        }
    }
    int operator -(PorkType & pt)
    {
        if(type!=pt.type)
            return type-pt.type;
        for(int i=0;i<5;i++)
        {
            if(card[i]!=pt.card[i])
                return card[i]-pt.card[i];
        }
        return 0;
    }
};
struct State{
    //high card 1, one pair 2, two pair 3,
    /*  1 High Card: Highest value card.
     2 One Pair: Two cards of the same value.
     3 Two Pairs: Two different pairs.
     4 Three of a Kind: Three cards of the same value.
     5 Straight: All cards are consecutive values.
     6 Flush: All cards of the same suit.
     7 Full House: Three of a kind and a pair.
     8 Four of a Kind: Four cards of the same value.
     9 Straight Flush: All cards are consecutive values of same suit.
     10 Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.*/
    static PorkType getType(int *pk,int *cl)
    {
        int cardNum[15]={0};
        bool Straight;
        bool Flush;
        PorkType pt;
        for(int i=0;i<5;i++)
        {
            cardNum[pk[i]]++;
        }
        Flush=true;
        for(int i=1;i<5;i++)
        {
            if(cl[i]!=cl[i-1])
            {
                Flush=false;
                break;
            }
        }
        sort(pk,pk+5,greater<int>());
        Straight=true;
        for(int i=1;i<5;i++)
            if(pk[i]!=pk[i-1]-1)
            {
                Straight=false;
                break;
            }
        pt.setcard(pk);
        if(Straight||Flush)
        {
            if(Straight&&Flush)
            {
                pt.type=9;
            }
            else if(Straight)
                pt.type=5;
            else
                pt.type=6;
            return pt;
        }
        // others
        int pairs[5]={0};
        for(int i=2;i<=14;i++)
        {
            pairs[cardNum[i]]++;
        }
        if(pairs[4]!=0)//四条
        {
            if(pk[0]!=pk[1]) // abbbb &&a>b
                swap(pk[0],pk[4]);
            pt.setcard(pk);
            pt.type=8;
        }
        else if(pairs[3]!=0)
        {
            int i;
            for(i=0;i<3;i++)
            {
                if(pk[i]==pk[i+1]&&pk[i+1]==pk[i+2])
                {
                    break;
                }
            }
            // i,i+1,i+2
            int buf[5];
            if(i==0)
                pt.setcard(pk);
            else if(i==1)
            {
                buf[0]=pk[1];
                buf[1]=pk[2];
                buf[2]=pk[3];
                buf[3]=pk[0];
                buf[4]=pk[4];
                pt.setcard(buf);
            }
            else
            {
                buf[0]=pk[2];
                buf[1]=pk[3];
                buf[2]=pk[4];
                buf[3]=pk[0];
                buf[4]=pk[1];
                pt.setcard(buf);
            }
            if(pairs[2]!=0)
                pt.type=7;
            else
                pt.type=4;
        }
        else if(pairs[2]!=0)
        {
            int buf[5];
            if(pairs[2]==2)
            {
                pt.type=3;
                if(pk[0]!=pk[1])
                {
                    buf[0]=pk[1];
                    buf[1]=pk[2];
                    buf[2]=pk[3];
                    buf[3]=pk[4];
                    buf[4]=pk[0];
                    pt.setcard(buf);
                }
                else if(pk[3]!=pk[4])//aabbc
                {
                    pt.setcard(pk);
                }
                else// aabcc->aaccb
                {
                    swap(pk[2],pk[4]);
                    pt.setcard(pk);
                }
                
            }
            else
            {
                pt.type=2;
                int i;
                for(i=0;i<4;i++)
                {
                    if(pk[i]==pk[i+1])
                        break;
                }
                buf[0]=pk[i];
                buf[1]=pk[i+1];
                int c=2;
                for(int j=0;j<i;j++)
                    buf[c++]=pk[j];
                for(int j=i+2;j<5;j++)
                    buf[c++]=pk[j];
                pt.setcard(buf);
            }
        }
        else //high card
        {
            pt.type=1;
            pt.setcard(pk);
        }
        return pt;
    }
};

int main()
{
    string a = "1A2453";
    cout<<a.find('A')<<endl;

//    vector<int> A = {0,0,1,1,1};
//    vector<int> B = {0,0,1,1,1};
////    do {
////        for (auto i : A)
////            std::cout << i << " ";
////        std::cout << std::endl;
////    } while (std::next_permutation(A.begin(), A.end()));
//    int types[10]={0};
//    string typeName[10]={"",
//        "杂牌",
//        "一对",
//        "两对",
//        "三条",
//        "顺子",
//        "同花",
//        "葫芦",
//        "四条",
//        "同花顺",
//    };
//    for(int t=0;t<1000000;t++)
//    {
//        int pk[5],color[5];
//        int card[52];
//
//        for(int i=0;i<52;i++)
//            card[i]=i;
//        //洗牌
//        for(int i=51;i>0;i--)
//        {
//            int j=rand()%(i+1);
//            swap(card[i],card[j]);
//        }
//        //取前五张
//        for(int i=0;i<5;i++)
//        {
//            pk[i]=card[i]%13; //0-12是点数
//            color[i]=card[i]/13;//0-3是花色
//        }
//        PorkType pt=State::getType(pk,color);
//        types[pt.type]++;
//    }
//    for(int i=1;i<=9;i++)
//    {
//        cout<<typeName[i]<<" 概率:"<<(double)types[i]/10000<<"%"<<endl;
//    }
    return 0;
   
}
    
    
    
//    HashTable h;
//    h.insert("John", 999);
//    h.insert("Mike", 666);
//    h.insert("Jason",13143);
//    h.erase("Mike");
//    cout<<h.getValue("John")<<endl;
//    cout<<h.getValue("Jason")<<endl;
//    cout<<h.getValue("John")<<endl;
    
    
    
    
//    string line;
//    string file = "/Users/JohnsonJohnson/Bubble.cpp";
//    ifstream f1;
//    f1.open(file);
//
//    while(getline(f1,line)){
//        cout<<line<<endl;
//    }
//    f1.close();
//
//    enum Date{MONDAY, TUEADAY};
//    Date date1 = MONDAY;
//    Date date2 = Date(1);
//    if(date2==TUEADAY){
//        cout<<date2<<endl;
//    }
//    string s;
//    string lines("fabfhd jabfkdja sfbdkjsa!$#%$!#$$#@!$#! -10 -100 -254 +4143!");
//    istringstream is(lines);
//    while(is>>s){
//        cout<<s<<endl;
//    }
    
//    int arr[] = {1,2,4};
//    int *p = &arr[0];
//    while(p++)
//        cout<<*p<<endl;
//    list<int> l3;
//
//    vector<int> l1={134,431,343,143,15,54,6,6542,454,54,14,314,314,46,509,764,87};
//    vector<int> l2 = {43,5413,5487,143,43143,431,87658,98,65,425,542,1340,431,4311,87};
////    for(auto x:l1)
////        l3.push_back(x);
////    l3.sort();
////    for(auto x:l3)
////        cout<<x<<endl;
//
//    int target=6583;
//    int diff=INT_MAX;
//    int m=-1,n=-1;
//    sort(l1.begin(),l1.end());
//    sort(l2.begin(),l2.end());
//        for(auto x:l1)
//            cout<<x<<" ";
//        cout<<endl;
//        for(auto x:l2)
//            cout<<x<<" ";
//        cout<<endl;
//
//
//    int i=0,j=l2.size()-1;
//    while(i<l1.size()&&j>=0){
//        if(target-l1[i]-l2[j]>=0&&target-l1[i]-l2[j]<=diff){
//            diff = target-l1[i]-l2[j];
//            m=i,n=j;
//        }
//        cout<<"i: "<<i<<" l1[i]: "<<l1[i]<<" j: "<<j<<" l2[j]: "<<l2[j]<<" sum: "<<l1[i]+l2[j]<<" current diff: "<<target-l1[i]-l2[j]<<" diff: "<<diff<<endl;
//        if(l1[i]+l2[j]>target)
//            j--;
//        else if(l1[i]+l2[j]<target)
//            i++;
//        else break;
//
//    }
//    cout<<"m:"<<m<<" n:"<<n<<" cloestSum: "<<l1[m]+l2[n]<<endl;
    
//    map<int,int> m;
//    unordered_map<int,int> um;
//    set<int> s;
//    unordered_set<int> us;
//    list<int> l;
//    stack<int> st;
//    queue<int> q;
//    deque<int> dq;
//
//
//    priority_queue<int,vector<int>, greater<int>> pq;
//    vector<int> nums = {14,50,1,321,32,123,43,12,43,98};
//    vector<string> strs = {"afda","tghi","this","father","sin","bakery"};
//    sort(nums.begin(),nums.end(),less<int>());
//    sort(strs.begin(), strs.end(), myCmp3);
//
//    for(auto x:nums)
//        cout<<x<<endl;
//    cout<<"------"<<endl;
//
//    for(auto x:strs)
//        cout<<x<<endl;
//    cout<<"------"<<endl;
//
//    for(auto x:nums)
//        pq.push(x);
//    while(!pq.empty()){
//        cout<<pq.top()<<endl;
//        pq.pop();
//    }
//
//
//    m.insert({1,1});
//    um.insert({1,2});
//    um.insert({1,3});
//    st.push(1);
//
    //    Triangle triangle;
    //    Rectangle rectangle;
    //    triangle.set_values(4,6);
    //    rectangle.set_values(4,6);
    //    cout<<triangle.area()<<endl;;
    //    cout<<rectangle.area()<<endl;;
    //    return 0;
    //

    
//    vector<pair<int,int>> vec={make_pair(1,3),make_pair(2,6),make_pair(4,8),make_pair(7,2),make_pair(-1,-4),make_pair(2,5),make_pair(10,9),make_pair(9,-1)};
//    sort(vec.begin(), vec.end(),myCmp);
//    for(auto x:vec)
//        cout<<x.first<<","<<x.second<<" distance: "<<sqrt(x.first*x.first+x.second*x.second)<<endl;
//
//
    
    
    
    
    
    
//    Base* pA = new Base;
//    //Base* pB = (Base*) new Sub;
//    Base* pB = new Sub;
//
//    pA->F1( );
//    pB->F1( );
//
//
//    pA->F2( );
//    pB->F2( );
//
//
//    delete pA;
//    delete pB;


//
//
//#include <iostream>
//#include <cmath>
//using namespace std;
//
//class A
//{
//public:
//    A(){cout << "Construct A" << endl;}
//    ~A(){cout << "Destruct A" << endl;}
//};
//
//class C
//{
//public:
//    C(){cout << "Construct C" << endl;}
//    ~C(){cout << "Destruct C" << endl;}
//
//};
//
//class B: public A, public C
//{
//public:
//    B(){cout << "Construct B" << endl;}
//    ~B(){cout << "Destruct B" << endl;}
//};
//
//int main(int argc, char const *argv[])
//{
//    B b;
//    return 0;
//}

