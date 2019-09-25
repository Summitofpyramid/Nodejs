//
//  main.cpp
//  ProjectZero
//
//  Created by Johnson Johnson on 2017-11-11.
//  Copyright © 2017 Johnson Johnson. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <stack>
#include <list>
#include <queue>
#include <stack>
#include <thread>
#include <vector>

using namespace std;

enum Direction{UP,DOWN};
enum State{MOVING, STOPPED};
enum Door{OPEN, CLOSED};


class Elevator{
private:

    int id;
    Direction direction = Direction::UP;
    State state = MOVING;
    Door door = CLOSED;
    Elevator(int id, Direction d, State s, Door door){
        this->id = id;
        this->direction = d;
        this->state = s;
        this->door = door;
    }
    
    
};
void quickSort(vector<int> &a,int l,int r){
    if(l<r){
        int i=l-1;
        int tmp = a[r];
        for(int j=l;j<r;++j)
            if(a[j]<=tmp)
                swap(a[++i], a[j]);
        swap(a[i+1], a[r]);
        quickSort(a,l,i);
        quickSort(a,i+2,r);
    }
}

void print_element(const vector<int>& v){
    for(auto x:v)
        cout<<x<<endl;
}
struct cmp{
    bool operator()(int a, int b){
        return a > b;
    }
};
bool myfunc(int a, int b){
    return a>b;
}

void print_queue( priority_queue<int> Q){
    while(!Q.empty()){
        cout<<Q.top()<<endl;
        Q.pop();
    }
}
int main()
{
    //cout<<sizeof(void*);
    vector<int> v = {1,3,4,5,10,0,-1,9};
    sort(v.begin(),v.end(),myfunc);
    print_element(v);
    cout<<endl;
    int x = 1;
    int y = move(x);
    
    
    priority_queue<int> Q;
    priority_queue<int,vector<int>,cmp>Q2;
    for(auto x:v)
        Q.push(x), Q2.push(x);
    print_queue(Q);
    cout<<endl;
    while(!Q2.empty()){
        cout<<Q2.top()<<endl;
        Q2.pop();
    }
    
    
        
    
    
//    string s = "1";
//    int n=4;
//
//    for(int i=0;i<n;++i){
//        char tmp=s[0];
//        int count=0;
//        string cur;
//        for(int j=0;j<s.size();++j){
//            if(s[j]==tmp){
//                count++;
//            }else{
//                cur+=to_string(count)+tmp;
//                tmp = s[j];
//                count=1;
//            }
//        }
//        cur+=to_string(count)+tmp;
//        s = cur;
//        cur.clear();
//    }
//    cout<<s<<endl;
//    vector<int> r;
//    vector<int>nums ={4,1,2,8,0,11,31,21,14,5};
//    quickSort(nums, 0, nums.size()-1);
//    int res = 1;
//    int i=0;
//    while(i<nums.size()){
//        int tmp = nums[i], next = i+nums[i]+1;
//        while(--tmp>=0){
//            i++;
//            res =res<<8|nums[i];
//        }
//        r.push_back(res);
//        res = 0;
//        i=next;
//    }
//    for(auto x:nums)
//        cout<<x<<" ";
//    vector<pair<int, int>> points{{1,2},{2,3},{0,4},{-1,6},{-3,2},{-4,5},{-10,0}};
//    sort(points.begin(), points.end());
//    for(auto x:points)
//        cout<<x.first<<" "<<x.second<<endl;
//    int a = 1;
//    int* pb = new int;
//    int* pc = pb;
//    //int* pc = nullptr;
//    //pc = pb;
//
//    *pb = 2;
//
//    printf("%d\n", a );
//    printf("%d\n", *pb );
//    printf("%d\n", *pc );
//
//    *pc = 5;
//    a += *pb;
//    *pb = a + *pc;
//
//    printf("%d\n", a );
//    printf("%d\n", *pb );
//    printf("%d\n", *pc );
}

