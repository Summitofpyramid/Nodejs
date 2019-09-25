#include <iostream>
#include <vector>
//#include <map>
#include <string>
//#include <iomanip>

using namespace std;

bool yellow = false, red = false;

bool DFS(const vector<vector<char>> &board,int i,int j,int last=-1,int count=1){
    if(count==4) return true;
    vector<pair<int,int>> dirs{{0,1},{1,0},{1,1},{1,-1}};
    size_t m = board.size(),n = board[0].size();
    if(last==-1){
        for(int k = 0;k<4;++k){
            int x = i+dirs[k].first,y = j+dirs[k].second;
            if(x>=0&&x<m&&y>=0&&y<n&&board[i][j]==board[x][y]&&DFS(board,x,y,k,count+1))
                return true;
        }
    }
    else{
        int x1 = i+dirs[last].first,y1 = j+dirs[last].second;
        if(x1>=0&&x1<m&&y1>=0&&y1<n&&board[i][j]==board[x1][y1]&&DFS(board,x1,y1,last,count+1))
            return true;
    }
    return false;
}

int main(){
    vector<vector<char>> board{
        {'R','Y','R','Y','B','Y','B'},
        {'R','R','R','E','B','Y','E'},
        {'R','Y','Y','E','Y','E','B'},
        {'R','Y','R','Y','B','Y','B'},
        {'R','E','R','E','B','E','B'},
        {'E','Y','R','Y','B','Y','Y'},
    };
    //vector<vector<char>> mark(6,vector<char>(7,'0'));
    for(int i = 0;i<6;i++){
        for(int j = 0;j<7;++j){
            if(board[i][j]=='E')
                continue;
            else if(!yellow&&board[i][j]=='Y')
                yellow = DFS(board,i,j,-1,1);
            else if(!red   &&board[i][j]=='R')
                red    = DFS(board,i,j,-1,1);
        }
    }
    
    if (!yellow&&!red)
        cout<<"N"<<endl;
    else if(!yellow&&red)
        cout<<"R"<<endl;
    else if(yellow&&!red)
        cout<<"Y"<<endl;
    else
        cout<<"B"<<endl;
    return 0;
}
//
//using namespace std;
//int main(){
//    string date,num,IdName;
//    //int num=0;
//
//    map<string,map<string,int>> dict;
//    //while(cin>>date>>num>>IdName)
//    string s;
//    getline(cin,s);
//    while
//
//    for(auto x:dict){
//        int tmp=0;
//
//        for( auto y:x.second){
//            tmp+= y.second;
//        }
//        double ave=double(tmp/(x.second.size()));
//
//        cout<<x.first<<" "<<tmp<<" "<<setw(4)<<ave<<" "<<x.second.size()<<endl;
//    }
//}
//
//
//
//
////class node{
////public:
////    char c;
////    bool isLeaf;
////    node* sons[26];
////    node(){c = '0';isLeaf = false;};
////    node(char input){c = input;isLeaf = false;}
////};
////class trie{
////public:
////node* root;
////    void create(vector<string> strs){
////        node* cur = root;
////        for(auto x:strs){
////            for(int i = 0;i<x.size();++i){
////                if(cur->sons[x[i]-'A'])
////                    cur = cur->sons[x[i]-'A'];
////                else
////                    cur = new node();
////            }
////        }
////    }
////
////
////};
////
////int main(){
////    string tmp;
////    vector<string> strs;
////
////    while(cin>>tmp)
////        strs.push_back(tmp);
////    trie T;
////    T.create(strs);
////    T.search();
////    return 0;
////}
//
//
//
//
//
//
//
//
////
////#include <iostream>
////#include <vector>
////#include <string>
////
////using namespace std;
/////*template<typename Comparable>
////int partition(vector<Comparable> a,int l,int r){
////    int i=l-1;
////    int tmp = a[r];
////    for(int j=l;j<r;++j)
////            if(a[j]<tmp) swap(a[++i], a[j]);
////    swap(a[i+1], tmp);
////    return i+1;
////}*/
////
////
////template<typename Comparable>
////void quickSort(vector<Comparable> &a,int l,int r){
////    if(l<r){
////        int i=l-1;
////        int tmp = a[r];
////        for(int j=l;j<r;++j)
////            if(a[j]<=tmp) swap(a[++i], a[j]);
////        swap(a[i+1],a[r]);
////        quickSort(a,l,i);
////        quickSort(a,i+2,r);
////    }
////}
////
////
////
////void type(const vector<int> b)
////{
////    for(int i = 0;i<b.size();++i)
////        cout<<b[i]<<endl;
////}
////
////int main(){
////
////    string s,t,p;
////    cin>>s>>t>>p;
////    cout<<s<<endl;
////    cout<<t<<endl;
////    cout<<p<<endl;
////
//////    string a = "11110011";
//////    string b = "11011";
//////    char x = a[1];
//////    char y = b[1];
//////    char z = x+y+x-'0'-'0';
//////    cout<<z<<endl;
////
////
////
////
////}
//
//
////bool test(int m,int q){
////    string tmp = to_string(m);
////    for(int i=0;i<tmp.size();++i)
////        if(tmp[i]==q+'0')
////            return true;
////    return false;
////}
////
////int main(){
////    int N,p,q;
////    cin>>N>>p>>q;
////    for(int i=1;i<=N;++i){
////        if(i%p==0&&!test(i,q))
////            cout<<"OUT";
////        else if(i%p!=0&&test(i,q))
////            cout<<"THINK";
////        else if(i%p==0&&test(i,q))
////            cout<<"OUTTHINK";
////        else
////            cout<<to_string(i);
////        if(i!=N)
////            cout<<",";
////    }
////}
//
//
//
