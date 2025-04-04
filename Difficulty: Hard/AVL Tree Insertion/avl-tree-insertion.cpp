//{ Driver Code Starts
//

#include <bits/stdc++.h>
#define MAXN 2000
using namespace std;

struct Node
{
    int data, height;
    Node *left, *right;
    
    Node(int x)
    {
        data=x;
        left=right=NULL;
        height=1;
    }
};

bool isBST(Node *n, int lower, int upper)
{
	if(!n) return 1;
	if( n->data <= lower || n->data >= upper ) return 0;
	return isBST(n->left, lower, n->data) && isBST(n->right, n->data, upper) ;
}

pair<int,bool> isBalanced(Node* n)
{
	if(!n) return pair<int,bool> (0,1);

	pair<int,bool> l = isBalanced(n->left);
	pair<int,bool> r = isBalanced(n->right);

	if( abs(l.first - r.first) > 1 ) return pair<int,bool> (0,0);

	return pair<int,bool> ( 1 + max(l.first , r.first) , l.second && r.second );
}

bool isBalancedBST(Node* root)
{
	if( !isBST(root, INT_MIN, INT_MAX) )
		cout<< "BST voilated, inorder traversal : ";

	else if ( ! isBalanced(root).second )
		cout<< "Unbalanced BST, inorder traversal : ";

	else return 1;
	return 0;
}

void printInorder(Node* n)
{
	if(!n) return;
	printInorder(n->left);
	cout<< n->data << " ";
	printInorder(n->right);
}


// } Driver Code Ends
/* The structure of the Node is
struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;
};
*/

class Solution{
  public:
  
    int getHeight (Node* root){
    if(!root){
        return 0;
    }else{
        return root->height;
    }
}

//functions for rotations
Node* leftRotation(Node * root){

    Node * child = root->right;
    Node* temp = child->left;
    child->left = root;
    root->right = temp;
    //height update karna to me bhul hi gaya tha
    //kyu ki root aur uski right node ki place change hui hai {hmm aur kisiska height change nehi hua gaur se dekho} to hame unka height update karna padega

    //aur ek imp baat height updation ka bhi ek order hai means first root ka height update hoga jo abhi niche agay hai then jake child ka height update hoga jo ki abhi root ka parent banagay hai 
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    child->height = 1 + max(getHeight(child->left), getHeight(child->right));

    return child;

}

Node* rightRotation(Node * root){
    Node * child = root->left;
    Node* temp =  child->right;
    child->right = root;
    root->left = temp;

    //yaha pe bhi simillarly height update hoga

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    child->height = 1 + max(getHeight(child->left), getHeight(child->right));

    return child;
}
  
  
    /*You are required to complete this method */
    Node* insertToAVL(Node* root, int value)
    {
        if(!root){
        return new Node(value);
    }

    if(root->data > value){
        root->left = insertToAVL(root->left,value);
    }
    else if(root->data < value) {
        root->right = insertToAVL(root->right, value);
    }
    else{
        return root;//in case when there is duplicate elemnt we will not add them
    }

    //now as a new node added so we will now backtrack and while this we will travel through all nodes we have travelled for adding this node
    //so what we will do is update their height and check wheather they are balanced or not if not then try to balance them and after balancing them return the address of root of balanced subtree if already balanced then just return their address [i.e root] which will go and stored in their parents left or right pointer

    //updating the height first

    //so height of each node will be updated as max(height of left subtree, height of right subtree)
    //but the issue here is if we directly try to access root->left->height then we might get error as their might be a chance where the root dont have left or right side so accessing them will give error
    //to tackle this we have to use multiple if else cases where we have to check either both are present if only one is present then which side is present and many more which will make my code more complex so i will avoid that 
    
    //to simplyfy this more i got an idea that if i had a function which will return the height if certain side exist or return 0 if that side dont exist then that will be great ....

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    //now with the same function i will check either the current root is balanced or not

    int balanced = getHeight(root->left) - getHeight(root->right);

    //checking imbalanceness
    if(balanced > 1){

        if(value < root->left->data){
            return rightRotation(root);
        }
        else{
           root->left =  leftRotation(root->left);
            return rightRotation(root);
        }

    }
    else if(balanced < -1){

        if(value < root->right->data){
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
        else{
            return leftRotation(root);
        }

    }else{
        return root;
    }


    
    }
};

//{ Driver Code Starts.

int main()
{
	int ip[MAXN];
    
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        
        for(int i=0; i<n; i++)
            cin>> ip[i];
        
        Node* root = NULL;
        Solution obj;
        for(int i=0; i<n; i++)
        {
            root = obj.insertToAVL( root, ip[i] );
            
            if ( ! isBalancedBST(root) )
                break;
        }
        
        printInorder(root);
        cout<< endl;
    }
    return 0;
}
// } Driver Code Ends