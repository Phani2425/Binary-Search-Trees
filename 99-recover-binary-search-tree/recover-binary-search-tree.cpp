/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

//APPROACH - 1

// class Solution {
// public:

//    void findInorder(TreeNode* root, vector<TreeNode*>& inorder){ 
//       if(!root){
//         return;
//       }

//       findInorder(root->left, inorder);
//       inorder.push_back(root);
//       findInorder(root->right, inorder);
//    }

//     void recoverTree(TreeNode* root) {


//         vector<TreeNode*> inorder;
//         findInorder(root, inorder);

//         int first,second = -1;

//         for(int i=1;i<inorder.size();i++){
//            if(inorder[i]->val < inorder[i-1]->val){
//             if(first == -1){
//                 first = i-1;
//                 second = i;
//             }
//             else{
//                 second = i;
//             }
//            }
//         }

//         //swapping to recover original bst

//         if(first != -1){
//               int value = inorder[first]->val;
//             inorder[first]->val = inorder[second]->val;
//             inorder[second]->val = value;
//         }
        

//         return;
//     }
// };

//APPROACH:- WE CAN ONLY KNOW WHERE THE SWAPPING TOOK PLACE BY TRAVERSING THE TREE IN INORDER TRAVERSAL AS IF THE NODE ARE SWAPPED THEN THE INCRESING ORDER WE USED TO GET BY TRAVERSING THE TREE IN INORDER WILL BE HAMPERED

//SO WE WILL FIRST STORE THE INORDER TRAVERSAL OF THE BST ...BUT WE WILL NOT STORE THEM IN ARRAY OF INTEGER... WE WILL STORE THE ADDRESS OF NODES THAT WILL COME IN INORDER TRAVERSAL SO WHILE CHECKINH WHEN WE WILL GET THE POINT WHERE VALUES OF NODE GET SWAPPED THERE WE WILL SIMPLY SWAP THEM BACK TO RECOVER THE ACTUAL CORRECT BST

//THIS APPROAVVH USING A SPACE COMPLEXITY OF O(N) AS IT IS USING AN EXTTRA ARRAY TO STORE THE INORDER TRAVERSAL

//BUT THE QUESTION HAS A FOLLOW UP QUESTION WHICH IS TO SOLVE THE SAME WITH A CONSTANT SPACE COMPLEXITY

// APPROACH - 2

class Solution {
public:

   void findViolation(TreeNode* root, TreeNode* &prev, TreeNode* & first,  TreeNode* & second){ 
      if(!root){
        return;
      }
      
      findViolation(root->left,prev,first,second);

      if(prev != NULL && (prev->val > root->val)){
          if(first == NULL){
               first = prev;
               second = root;
          }
          else{
            second = root;
          }
      }

      prev = root;

      findViolation(root->right,prev,first,second);
     
   }

    void recoverTree(TreeNode* root) {

        TreeNode* firstViolation = NULL, *secondViolation = NULL, *prev = NULL;

        
        findViolation(root, prev,firstViolation, secondViolation);

        //swapping both node to recover the tree
        swap(firstViolation->val , secondViolation->val );

        return;


    }
};

//IN THIS APPROACH ALSO THE INTERVIEWER CAN SAY THAT YOU ARE USIONG RECURSION AND RECURSION STACK ALSO IS TAKING EXTRA SPACE [ALTHOUH WE DO NOT GENERRALLY CONSIDER THE RECURSION STACK SPACE] BUT STILL IF THE INTERVIEWER ASKS TO OPTIMISE IT MORE AND DONT USE THE RECURSION THEN WE CAN STILL MAKE INORDER TRAVERSAL BY MORRIS TRAVERSAL WHICH IS THE ITERATIVE WAY TO SOLEV THE PROBLEM