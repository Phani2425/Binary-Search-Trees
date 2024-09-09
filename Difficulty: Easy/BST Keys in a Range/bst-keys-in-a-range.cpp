//{ Driver Code Starts
//Initial template for C++

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to Build Tree
Node* buildTree(string str)
{   
    // Corner Case
    if(str.length() == 0 || str[0] == 'N')
            return NULL;
    
    // Creating vector of strings from input 
    // string after spliting by space
    vector<string> ip;
    
    istringstream iss(str);
    for(string str; iss >> str; )
        ip.push_back(str);
        
    // Create the root of the tree
    Node* root = new Node(stoi(ip[0]));
        
    // Push the root to the queue
    queue<Node*> queue;
    queue.push(root);
        
    // Starting from the second element
    int i = 1;
    while(!queue.empty() && i < ip.size()) {
            
        // Get and remove the front of the queue
        Node* currNode = queue.front();
        queue.pop();
            
        // Get the current node's value from the string
        string currVal = ip[i];
            
        // If the left child is not null
        if(currVal != "N") {
                
            // Create the left child for the current node
            currNode->left = new Node(stoi(currVal));
                
            // Push it to the queue
            queue.push(currNode->left);
        }
            
        // For the right child
        i++;
        if(i >= ip.size())
            break;
        currVal = ip[i];
            
        // If the right child is not null
        if(currVal != "N") {
                
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
//User function template for C++

class Solution {
  public:
  
  void find(Node * root, int low, int high ,vector<int>& ans){
      if(!root){
          return;
      }
      
      if(root->data > low && root->data >high){
          find(root->left,low,high,ans);
      }
      else if(root->data < low && root->data < high){
          find(root->right,low,high,ans);
      }
      else{
          //doing inorder traversal for the node as it comes in the given range
          //it is not only inorder traversal it is also detecting the nodes which comes in the range or not
          find(root->left,low,high,ans);
          ans.push_back(root->data);
          find(root->right,low,high,ans);
          
      }
  }
  
    vector<int> printNearNodes(Node *root, int low, int high) {
        vector<int> ans;
        find(root,low,high,ans);
        
        return ans;
    }
};


//APPROACH

//SO WE CAN SOLVE IT VERY EASILY WITH INORDER TRAVERSAL BUT FOR THAT WE HAVE TPP TRAVERSE THE WHOLE
// TREE TO FIND OOUT THE NODES WHICH COMES UNDER THE RANGE

//SO CAN WE SOLVE THIS WITHOUT TRAVESRING THE WHOLE TREE...???? OF COURSE YES WE CAN DO IT...

//USING THE CONCEPT OF RANGE COMPARISION WHERE AME GOTE NODE PAKAHKU JAIKI CHECK KARU KN AMA RANGE RA EXTREME SE NODE THU BADA NA CHOTA
//JADI BADA THEN AMRA SE NODE KOU  KAMA KU NUHA AU AME SE NODE RA RIGHT SIDE KU  PALEI JAU AU JADI BOTH EXTREEME ARE SMALL THE TOO SE NODE AMARA 
// KOU KAMA KU NUHA SO AME LEFT SIDE KU JAU BUT EI 2 TA CASE  SATUSFY HELANI MEANS EI NODE AMA RANGE BHITARE ASUCHI

//ACHA JADI EI NODE AMA RANGE BHITARE ASUCHI THEN AKU TA AMAKU STORE KARIBAKU PADIBA AU ARA LEFT AU RIGHT SIDE RA NODE MANANKARA BI POSSIBILITY ACHI KI SEMANE BI AMA RANGE BHITARE ASIPARIBE... HELE QUES TA KAHICHI KI SORTED ORDWER RE STORE KARA SO AMAKU
// SORTED ORDER RE ELEMENTS KEMITI MILIBA???

//OBVIOUSLY THIS IS BST SO INORDER TRAVERSAL KARIDELE AMAKU SORTED ORDER RE ELEMENTS MILIJIBA

//SO MU KN KARIBI NA JEHETU MU BAHUT CHALAKH SETHIPAIN JOU NODE MO RANGE RE MILILA MU TA PAIN LEFT RE THARE RECURSION CALL KARIBI TO CHECK WHEATHER NODES AT ITS LEEFT ARE IN THE RANGE OR NOT AND IF THEY ARE THEN PUSH THEM IN ANS VECTOR
//AND THEN PUSHING THE VALUE OF NODE WHICH I AM CURRENTLY ON 
//AND AT LAST LIKE LEFT SIDE I WILL MAKE RECURSIVE CALL TO THE RIGHT SIDE TO FIND OUT WHEATHER THERE ARE NODES WHICH ARE IN THE RANGE AND IF I FOUND OUT THEN STORING THEM IN THE ANS VECTOR

//AU EMEIT MATE ARAMRE SABU NODE WITHIN THE RANGE MILI BI JIBA AU VECTOR RE SORTED HEIKI STORE BI HEIJIBA

//what will be the time complexity????? 


//{ Driver Code Starts.

int main()
{

    int t;
	scanf("%d ",&t);
    while(t--)
    {
        int k1 , k2;
        string s;
		getline(cin,s);
		scanf("%d ", &k1);
		scanf("%d " , &k2);
		Solution ob;
        Node* root = buildTree(s);
        vector <int> res = ob.printNearNodes(root, k1 ,  k2);
        for (int i=0;i<res.size();i++) cout << res[i] << " ";
        cout<<endl;
    }
    return 1;
}

// } Driver Code Ends