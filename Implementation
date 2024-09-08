// in implementation of bst i have an array having some eklements which we have to use while creating the bst .. so we will basiclly traverse the array and insert those elements into the bst one by one
//while inserting we will use recursion to do that..... but why??? what is the intution of recursion???

//currently as i can understand that : - when the first element will come fro insertion that wil be obviously the root node and the function used for inserting will create that node and return te address of that node....
// the when again another element will go then that element will be compared with the root node to find its correct position...and when it will find its correct position then it will gett created but think that where do its address will be stored ??? obviously in its parents left or right field ... this means everytime a node get created it returns its address to its parent
//so we will do it with recursion

#include<bits/stdc++.h>
using namespace std;


class Node 
{
    public:
    int data;
    Node * left;
    Node * right;

    Node(int value){
      data=value;
      left=right=NULL;
    }

};

Node * insertElement (Node * root,int value){
    if(!root){
        Node * temp = new Node(value);
        return temp;
    }
    if(value < root->data){
       root->left =  insertElement(root->left, value);
    }
    else{
        root->right = insertElement(root->right, value);
    }

    return root;

}

void inorder (Node * root) {
    if(!root){
        return;
    }

    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int main () {
    //array which will be implemnted as the bst
    int arr[] = {3,6,1,9,4,10,16,11,7};

    Node * root = NULL;

    for(int i = 0;i<9;i++){
      root = insertElement(root,arr[i]);
    }

    cout<< "root of the whole binary search tree which got created form the given array is:-"<<root<<endl;

    cout<<"printing the tree in inorder traversal:- "<<endl;
    inorder(root);//in order traversal of the bst always produces elements in increasing order or sorted elements in increasing order

    return 0;
}
