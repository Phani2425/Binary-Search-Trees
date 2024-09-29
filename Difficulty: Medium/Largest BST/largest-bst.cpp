//{ Driver Code Starts
//Initial Template for C++


#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

// Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Utility function to create a new Tree Node
Node* newNode(int val) {
    Node* temp = new Node;
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}


// Function to Build Tree
Node* buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N') return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;) ip.push_back(str);

    // Create the root of the tree
    Node* root = newNode(stoi(ip[0]));

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
            currNode->left = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size()) break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current node
            currNode->right = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}


// } Driver Code Ends
/* Tree node structure  used in the program

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};*/

// class Box {
    
//     public:
//     bool bst;
//     int size;
//     int max;
//     int min;
    
//     Box (int value){
//         bst = 1;
//         size = 1;
//         max = value;
//         min = value;
//     }
    
// };

// class Solution{
//     public:
    
//     Box * find(Node * root, int & SizeofLargestBst){
//         //if current root is a leaf node
//         if(!root->left && !root->right){
//             return new Box(root->data);
//         }
//         //if current node have only left side subtree
//         else if(!root->right){
//             Box * head = find(root->left, SizeofLargestBst);
//             if(head->bst && root->data > head->max){
//                 head->size++;
//                 head->max = root->data;
//                 SizeofLargestBst = max(SizeofLargestBst, head->size);
//                 return head;
//             }
//             else{
//                 head->bst = 0;
//                 return head;
//             }
//         }
        
//         //if current node have only right subtree
//         else if(!root->left){
//             Box * head = find(root->right, SizeofLargestBst);
//             if(head->bst && root->data < head->min){
//                 head->size++;
//                 head->min = root->data;
//                 SizeofLargestBst = max(SizeofLargestBst, head->size);
//                 return head;
//             }
//             else{
//                 head->bst = 0;
//                 return head;
//             }
//         }
        
//         //if current node have both side subtrees
//         else{
//             Box * leftHead = find(root->left, SizeofLargestBst);
//             Box * rightHead = find(root->right, SizeofLargestBst);
            
//             if(leftHead->bst && rightHead->bst && root->data > leftHead->max && root->data < rightHead->min){
//                 leftHead->size = leftHead->size + rightHead->size + 1;
//                 SizeofLargestBst = max(SizeofLargestBst, leftHead->size);
//                 leftHead->max = rightHead->max;
//                 return leftHead;
                
//             }
//             else{
//                 leftHead->bst = 0;
//                 return leftHead;
//             }
//         }
//     }
    
//     /*You are required to complete this method */
//     // Return the size of the largest sub-tree which is also a BST
//     int largestBst(Node *root)
//     {
//         // i have taken it 1 because in any case the size of largest bst will be 1 which will be the leaf node size as leaf node will be the bst in all cases
//     	int SizeofLargestBst = 1;
//     	find (root, SizeofLargestBst);
    	
//     	return SizeofLargestBst;
//     }
// };




//IN THE PREVIOUS WAY WE WERE HANDLING 4 CASES:-
// 1. LEAF NODE
// 2. ONLY LEFT EXIST
// 3. ONLY RIGHT SIDE EXISTS
// 4. BOTH SIDE EXISTS

//AND WE HAVE TO HANDLE ALL THESE CASESS BECAUSE WE ARE NOT HANDLING THE NULL NODE CORRECTLY SO IF WE WILL HANDLE THE NULL NODE CORRECTLY THEN WE DO NOT HAVE TO HANDLE FIRST 3 CASESS SEPARATELY 
//BECAUSE ALL OF THEM WILL BE HANDLED AUTOMATICALLY IN A SINGLE CASE

//SO WAY-2 [HERE WE WILL HANDLE THE NULL NODE OPTIMALLY]


class Box {
    
    public:
    bool bst;
    int size;
    int max;
    int min;
    
    Box (){
        bst = 1;
        size = 0;
        max = INT_MIN;
        min = INT_MAX;
    }
    
};

class Solution{
    public:
    
    Box * find(Node * root, int & SizeofLargestBst){
           //ROOT DOESN'T EXIST
           if(!root){
               return new Box();
           }
           
           //ROOT EXISTS
           Box * leftHead = find(root->left, SizeofLargestBst);
           Box* rightHead = find(root->right, SizeofLargestBst);
           
           if(leftHead->bst && rightHead->bst && root->data > leftHead->max && root->data < rightHead->min){
               Box* head= new Box();
               head->size = leftHead->size + rightHead->size + 1;
               head->min = min(root->data, leftHead->min);
               head->max = max(root->data, rightHead->max);
               
               SizeofLargestBst = max(SizeofLargestBst, head->size);
               return head;
               
           }
           else{
               leftHead->bst = 0;
               return leftHead;
           }
    }
    
    /*You are required to complete this method */
    // Return the size of the largest sub-tree which is also a BST
    int largestBst(Node *root)
    {
        // i have taken it 1 because in any case the size of largest bst will be 1 which will be the leaf node size as leaf node will be the bst in all cases
    	int SizeofLargestBst = 0;
    	find (root, SizeofLargestBst);
    	
    	return SizeofLargestBst;
    }
};




//{ Driver Code Starts.

/* Driver program to test size function*/

  

int main() {

   
    int t;
    scanf("%d ", &t);
    while (t--) {
        string s, ch;
        getline(cin, s);
        
        Node* root = buildTree(s);
        Solution ob;
        cout << ob.largestBst(root) << endl;
    }
    return 0;
}

// } Driver Code Ends