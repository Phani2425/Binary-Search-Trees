//{ Driver Code Starts
//

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

Node* buildTree(string str)
{
    // Corner Case
    if (str.length() == 0 || str[0] == 'N')
        return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str; )
        ip.push_back(str);

    // Create the root of the tree
    Node* root = new Node(stoi(ip[0]));

    // Push the root to the queue
    queue<Node*> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node* currNode = queue.front();
        queue.pop();

        // Get the current node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current node
            currNode->left = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size())
            break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current node
            currNode->right = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}

bool isBST(Node* n, int lower, int upper)
{
    if (!n) return true;
    if ( n->data <= lower || n->data >= upper ) return false;
    return (  isBST( n->left, lower, n->data )  &&  isBST( n->right, n->data, upper )  );
}

bool compare( Node* a, Node* b, vector<pair<int, int>> &mismatch )
{
    if ( !a && !b ) return true;
    if ( !a || !b ) return false;

    if ( a->data != b->data )
        mismatch.push_back( pair<int, int> (a->data, b->data) );

    return ( compare( a->left, b->left, mismatch ) && compare( a->right, b->right, mismatch ) );
}


// } Driver Code Ends
/*
struct Node
{
    int data;
    Node *left, *right;
    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
};
*/


class Solution {
  public:
  
  //THIS APPROCH HAVE A TIME COMPLEXITY OF O(N) AND SPACE COMPLESITY OF O(N) [DUE TO THE STACK]
  
    void correctBST( struct Node* root )
    {
        Node *first = NULL, *sec = NULL;
        stack<Node *> st;
        
        //initialising the stack
        while(root){
            st.push(root);
            root=root->left;
        }
        
        Node* prevNode = st.top(); //basically this is the previous node of each node in the inorder traversal of the tree
        //we are initialising it with first node of inorder traversal
        //when a node will be smaller that the prev node there we will know that here is something wronng as in inorder traversal elements are in ascending order
        //so at that point i will update my first and sec node which i will use for swapping in later stage
        //if you want to know the concept of first and second node then see the 5th lecture of rohit negi of bst else think how can you swap the misarranged numbers in an ascending ordered array
        //mis arrangement or swapping can be between adjecent elements and non adjacent elements then how can you handle both cases
        //first think how can you do it using 4 pointers then optimise it by thinking that if actually in need two pointers which will be pointng to the two swapped number which i will again swap to make the order correct
        //then why will i use 4 pointers ..... i will solve this using 2 pointers only where i have use my mind a little bit so that i can update them on the basis of some condition [updating both when i got first gadbad the updating only sec variable when i will get 2nd gadbad] i
        // in this way i can handle both the cases of missarangement
        //but how can i know i am getting 1st gadbad or getting 2nd gadbad...... initialise the both pointers to a value if they have that value then i will know i never updated them
        // means i am getting 1st gadbad but if they dont have that value means i am getting 2nd gadbad as in 1st time i must had updated them for which they dont have the value they were initialised with
        
        
        while(!st.empty()){
            
            if(st.top()->data < prevNode->data){
                if(first == NULL){// i am getting the first gadbad that is why the first had not updated yet and havv ethe initialised value
                    first = prevNode;
                    sec = st.top();// i am storing the sec because it might be the case of swapping where the adajacent node were swapped so to make it corrrect i have to swap them back
                    // in this case there will not be any second gadbad as adjacent node got swapped so i am storing both at last i will just swap them
                }
                else{// i am getying the second gadbad as the value of first is updated 
                    sec = st.top();//here i will only update the value of sec as i only need that to swap that with first pointer
                }
            }
            
            prevNode = st.top();
            root = st.top()->right;
            st.pop();
            
            while(root){
                st.push(root);
                root = root->left;
            }
            
        }
        
        //now i will hav ethe address of swapped node so  i will re swap them to make the bst correct
        int firstData = first->data;
        first->data = sec->data;
        sec->data = firstData;
    }
    
    
    
    // SOLVING THIS WITH A TIME COMPLEXITY OF O(N) BUT WITH A OPTIMISED SPACE COMPLEXITY OF O(1)
    
    
    ///DEKH BHAI E PROBLEM SOLVE KARIBA PAIN TATE FOR SURE INORDER TRAVERSAL KARIBAKU HNI PADIBA AU EMITI KOU METHOID ACHI JOUTA O(1) S.C RE 
    // INORDER TRAVERSAL KARIPARIBA????  NOT RECURSION, NOT STACK AGAR RECURSION ME KIS TARAH HO BHI GAYA THEN ALSO SEMANANKU COMAPRE KARIBA PAIN STORE KARIBAKU PADIBA AU SETHIPAIN BI SPACE LAGIBA
    
    //ONLY WAY WHICH DOES INORDER TRAVERSAL WITH CONSTANT TIME COMPLEXITY IS TEH " MORRIS TRAVERSAL "
    //AB MORRIS TRAVERSAL KOI KESE BHUL SKATA HAI...😁😁😁😁
    
    void correctBST( struct Node* root )
    {
       Node* first = NULL, * sec = NULL;
       //now i will initalise the prevNode with the 1st node of inorder traversal or the leftmost node of the bst
       Node* temp = root;
       while(temp->left){
           temp=temp->left;//this temp will go and stop at the left most node of the BST
       }
       Node* prevNode = temp;
       
       //starting MORRIS TRVAERSAL
       while(root){//morris trversal setebela jae chaliba jetebela jae root null na heichi bcs at last after trversing all the node it will gte null by going to the right of the right most node of the tree according to the morrid traversal
           if(root->left){
               Node* dummy = root->left;
               while(dummy->right != NULL && dummy->right != root){
                   dummy = dummy->right;
               }
               if(dummy->right == NULL){
                   dummy->right = root;//connection made with node
                   root = root->left;//ab left me jao
                   continue;
               }
               else{
                   dummy->right = NULL; // i forgot to remove the link that is why i was getting wrong answer ... so i will never forget to remove link in morris traversal again
               }
           }
           
           if(root->data < prevNode->data){
               if(first == NULL){
                   first = prevNode;
                   sec = root;
               }
               else{
                   sec = root;
               }
           }
           
           prevNode = root;
           root=root->right;
       }
       
       int firstData = first->data;
       first->data = sec->data;
       sec->data = firstData;
       
    }
    
    
};


//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    getchar();

    while (t--)
    {
        string s;
        getline(cin, s);

        Node* root = buildTree(s);
        Node* duplicate = buildTree(s);

        Solution ob;
        ob.correctBST(root);

        // check 1: is tree now a BST
        if ( ! isBST(root, INT_MIN, INT_MAX) )
        {
            cout << "0\n";
            continue;
        }

        // check 2: comparing with duplicate tree

        vector<pair<int, int>> mismatch;
        // a vector to store data of mismatching nodes

        if ( ! compare( root, duplicate, mismatch) )
        {
            // false output from this function indicates change in structure of tree
            cout << "0\n";
            continue;
        }

        // finally, analysing the mismatching nodes
        if ( mismatch.size() != 2 || mismatch[0].first != mismatch[1].second || mismatch[0].second != mismatch[1].first )
            cout << "0\n";
        else cout << "1\n";
    }
    return 0;
}

// } Driver Code Ends
