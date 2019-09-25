#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    string tmp;
    vector<string> result;
    vector<string> binaryTreePaths(TreeNode* root,string tmp) {
        if(root == NULL)
            return result;
        tmp.push_back((char)root->val);
        tmp.push_back('->');
        if((root->left==NULL)&&(root->right==NULL))
        {
            result.push_back(tmp);
        }
        else
        {
            binaryTreePaths(root->left,tmp);
            binaryTreePaths(root->right,tmp);
        }
        return result;
    }
};
//void PrintPath(node * root,vector<int> path)
//{
//    if (root)
//    {
//        path.push_back(root->self);
//        if (!root->left&&!root->right)
//            //if (root->self==find)
//        {
//            for (int i=0;i<path.size()-1;i++)
//            {
//                cout<<path[i]<<"->";
//            }
//            cout<<path.back()<<endl;
//            
//            return;
//        }
//        else
//        {
//            PrintPath(root->left,path);
//            PrintPath(root->right,path);
//        }
//    }
//}

    struct node{
        int self;
        node *left;
        node *right;
        node(int x) : self(x), left(NULL), right(NULL) {}
    
    
    };

int main()
{
    const int TREE_SIZE = 10;
    stack <node> visited, unvisited;
    vector<node*> nodes;
  //  node nodes[TREE_SIZE];
    
//    for( int i=0; i<10; i++) //初始化树
//    {
//        nodes[i].self = i;
//        int child = i*2+1;
//        if( child<TREE_SIZE ) //Left child
//            nodes[i].left = &nodes[child];
//        else
//            nodes[i].left = NULL;
//        child++;
//        if( child<TREE_SIZE ) //Right child
//            nodes[i].right = &nodes[child];
//        else
//            nodes[i].right = NULL;
//    }
    
    int a=1,b=3,c=4,v=5,m=7;
    pair<node*, int> p1(&a,a),p2(&b,b),p3(&c,c),p4(&v,v),p5(&m,m);
    set< pair<node*, int> > tree;
    tree.insert
    
    
    
    
    Solution solu;
    vector<int> path;
    solu.binaryTreePaths(nodes, path);
    
}