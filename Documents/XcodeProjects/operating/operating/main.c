#include <iostream>
#include <vector>
using namespace std;

struct node
{
    int self; //数据
    node *left; //左节点
    node *right; //右节点
};

void PrintPath(node * root,vector<int> path,int length)
{
    vector<int> path;
    if (root)
    {
        
        path.push_back(root->self);
        if (!root->left&&!root->right)
            //if (root->self==find)
        {
            for (int i=0;i<path.size();i++)
            {
                cout<<path[i]<<",";
            }
            cout<<endl;
            return;
        }
        else
        {
            PrintPath(root->left,path,length+1);
            PrintPath(root->right,path,length+1);
        }
    }
}

void main()
{
    const int TREE_SIZE = 10;
    std::stack <node*> visited, unvisited;
    node nodes[TREE_SIZE];
    
    for( int i=0; i<TREE_SIZE; i++) //初始化树
    {
        nodes[i].self = i;
        int child = i*2+1;
        if( child<TREE_SIZE ) //Left child
            nodes[i].left = &nodes[child];
        else
            nodes[i].left = NULL;
        child++;
        if( child<TREE_SIZE ) //Right child
            nodes[i].right = &nodes[child];
        else
            nodes[i].right = NULL;
    }
    
    vector<int> path;
    PrintPath(nodes,path,0);
    
}