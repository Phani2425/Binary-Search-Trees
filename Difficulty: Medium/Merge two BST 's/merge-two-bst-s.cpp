//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

// Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to Build Tree
Node* buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N')
        return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;)
        ip.push_back(str);

    // Create the root of the tree.....
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


// } Driver Code Ends
/*
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/
class Solution {
  public:
    // Function to return a list of integers denoting the node
    // values of both the BST in a sorted order.
    vector<int> merge(Node *root1, Node *root2) {
        
        stack<Node *> s1,s2;
        vector<int> ans;
        
        //initialising the stacks for starting the traversal
        while(root1){
            s1.push(root1);
            root1=root1->left;
        }
        while(root2){
            s2.push(root2);
            root2 = root2->left;
        }
        
        while(!s1.empty() && !s2.empty()){
            //both top are same
            if(s1.top()->data == s2.top()->data){
                ans.push_back(s1.top()->data);
                ans.push_back(s2.top()->data);
                
                root1 = s1.top()->right;
                s1.pop();
                root2 = s2.top()->right;
                s2.pop();
            }
            //s1 top is smaller
            else if(s1.top()->data < s2.top()->data){
                ans.push_back(s1.top()->data);
                
                root1 = s1.top()->right;
                s1.pop();
                
            }
            //s2 top is smaller
            else{
                ans.push_back(s2.top()->data);
                
                root2 = s2.top()->right;
                s2.pop();
            }
            
            //updating the stack after popping
        while(root1){
            s1.push(root1);
            root1=root1->left;
           }
        while(root2){
            s2.push(root2);
            root2 = root2->left;
           }
        }
        
        while(!s1.empty()){
            ans.push_back(s1.top()->data);
            root1 = s1.top()->right;
            s1.pop();
            while(root1){
            s1.push(root1);
            root1=root1->left;
           }
        }
        
        while(!s2.empty()){
            ans.push_back(s2.top()->data);
            root2 = s2.top()->right;
            s2.pop();
            while(root2){
            s2.push(root2);
            root2 = root2->left;
           }
        }
        
        return ans;
        
    }
};

//HERE WE WILL USE THE SAME APPROACH AS WE USED I THE QUEDTION OF FINDING COMMON NODES IN 2 GIVEN BST OR FINDINNG INTERSECTIONN BETWEEN 2 BST

//THERE THE ONLY IDEA WE GOT IS THAT WE HAVE TO FIRST TRAVERSE THEM BOTH THEN WHAT EVER RESULT WE WILL GET FROM TRAVERSAL OF BOTH WE WERE COMPARINNG THEM BOTH AND GETTING THE COMMON NODES BETWEE THEM
//FOR THAT WE CAN USE TWO POINTERS TO DO SO

//SO FOR TRAVERSING THE TREE WE HAVE TO CHOOSE A WAY .... WHICH WILL BE INORDER FOR SURE WHY???? BECAUSE INORDER TRAVERSAL WILL GIVE US THE SORTED ARRAY IN WHICH IT IS VERY EASY TO PERFORM COMPARISION BETWEEN TOW ARRAY WHEN THEY ARE SORTED
//INSTED OF PERFORMING COMPARISISON IN UNSORTED ARRAY

//OK SO WE WILL TRAVERSE IN INORDER TRAVERSAL... SO WHAT ARE THEWAYS WE HAVE FOR INORDER TRAVERSAL??????

//1. RECURSION
//2. ITERATIVE
////2.1 USING STACK (USED FOR PRINNTING INORDER TRAVERSAL)(HERE WE CAN NOT PERFORM ANY OPERATION LIKE COMPARISION WHITH OTHER ARRAY)(BECAUSE IN THIS WE DONT KNOW WHEN THE NEXT ELEMENT IN THE INORDER ARRAY WILL COME TO TOP OF THE STACK)
////2.2 BUT IF WE WANT TO GET INORDER TRAVERSAL IN WHICH AFTER EVERY OPERATION I KNOW THAT MY NEXT ELEMENT IN THE INORDER TRAVERSAL WILL BE SURE AT THE TOP OF THE STACK

//SO HERE I WILL DONT USE RECURSION FOR TRAVERSAL BECAUSE USING RECURSION I CAN'T CONTROL THE TRAVERSAL AS HERE CONTROLL IS HIGHLY REQUIRED IF I WANT TO DO TRAVERSING AND COMPARISION SIMULTANEOUSLY
//YES IF I WANT TO TRAVERSE AND STORE THE INORDER TRAVERSAL OF BOTH AND TEHN COMPARE THEN I CAN USE RECURSION

//HERE I WILL USE SECOND TYPE OF ITERATIVE APPROACH WHERE I CAN COMPARE THE ELEMENT WHICH WILL COME NEXT IN THE INORDER ARRAY IN BOTH TREE AS IN THAT WAY I KNOW THAT THE NEXT ELEMENT COMIING IN THE INORDER TRAVERSE WILL BE AT TOP OF RESOECTIVE STACK FOR SURE
//SO BY COMPARING THEM I CAN CREATE THE ANS VECTOR EASILY AND ALSO I DON'T HAVE TO STORE THE TRAVERSAL AS I AM COMPARING ALONG WITH TRAVERSING

//{ Driver Code Starts.
int main() {

    int t;
    string tc;
    getline(cin, tc);
    t = stoi(tc);
    while (t--) {
        string s;
        getline(cin, s);
        Node* root1 = buildTree(s);

        getline(cin, s);
        Node* root2 = buildTree(s);

        // getline(cin, s);
        Solution obj;
        vector<int> vec = obj.merge(root1, root2);
        for (int i = 0; i < vec.size(); i++)
            cout << vec[i] << " ";
        cout << endl;
        /// cout<<"~"<<endl;
    }
    return 0;
}
// } Driver Code Ends