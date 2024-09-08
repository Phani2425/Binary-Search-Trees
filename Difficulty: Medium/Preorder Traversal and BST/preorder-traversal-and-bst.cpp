//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++


class Solution {
  public:
  
  //APPROACH - 1
  //THIS APPROACH IS CORRECT BUT STILL IT WILL GIVE US SEGMENTATION FAULT.... WE ENCOUNTER SEG FAULT WHEN WE TRYBTO ACESS THAT MEMEORY LOACTION WHICH WE ARE NOT ALLOWED TO..
  //SO ARE WE ACCESSING ANY SUCH MEM LOC HERE???? YES BUT NOT IN OUR PROGRAM .. ACTUALLY IT GAVE SEG FAULT FOR A TEXT CASE OF 1 LAKH NODES AND THAT MIGHT BE NODE OF A ONE SIDED TREE
  //SO AS WE ARE USING RECURSION AND FOR RECURSION SPACE IS ALLOCATED IN STACK MEMORY SO DUE TO SUCH LAREGE AMOUNT OF NODES AND MAY BE DUE TO ONE SIDED TREE THERE ARE 1 LAKH RECURSIVE CALLS
  //WHICH WANT TO TAKE SPACE IN STACK AND STACK DOES NOT HAVE SUCH LARGE SPACE SO WE GOT SEGMENTATION FAULT...
  
  //THIS PROGRAM SOLVES THE QUESTION WITH A T.C OF O(N) AND S.C OF O(N) BUT ONLY DUE TO LARGE NO OF RECURSIVE CALL WE GOT SEGMENTATION FAULT
  
    // void BSTconstructor(int arr[], int N, int& index, int Lower, int Upper){
    //     if(index == N || arr[index] < Lower || arr[index] > Upper){
    //         return;
    //     }
        
    //   int value = arr[index++];
        
    //   BSTconstructor(arr,N,index,Lower,value);
    //   BSTconstructor(arr,N,index,value,Upper);
        
    // }
  
    // int canRepresentBST(int arr[], int N) {
    //     int index = 0;
    //     BSTconstructor(arr,N, index, INT_MIN, INT_MAX);
        
    //     if(index < N){
    //         return 0;
    //     }
    //     return 1;
    // }
    
    
    
    //APPROACH - 2
    //IN THIS APPROACH WE WILL USE ITERATIVE APPROACH WHICH WE HAVE LEARNT IN TREE CHAPTER WHERE WE WERE USING STACK FOR PREORDER,INORDER AND POSTORDER TRAVERSAL OF THE TREE
    //AS STACK IS USED HEER AND STACK TAKES MEMORY IN HEAP SO THERE IS NO CHANCE OF SEGMENTATION FAULT
    
    int canRepresentBST(int arr[], int N) {
       stack<int> lower,upper;
       int lowerBound,upperBound;
       lower.push(INT_MIN);
       upper.push(INT_MAX);
       
       for(int i=0;i<N;i++){
           if(arr[i] < lower.top()){
               return 0;
           }
           
           while(arr[i] > upper.top()){
               lower.pop();
               upper.pop();
           }
           
           lowerBound = lower.top();
           lower.pop();
           upperBound = upper.top();
           upper.pop();
           
           //pushing limit for right child of the currnt node
           lower.push(arr[i]);
           upper.push(upperBound);
           //pushing limits of the left child of the current node
           lower.push(lowerBound);
           upper.push(arr[i]);
           
       }
       
       
       return 1;
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        int arr[N];
        for (int i = 0; i < N; i++) cin >> arr[i];
        Solution ob;
        cout << ob.canRepresentBST(arr, N) << endl;
    }
    return 0;
}
// } Driver Code Ends