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
class Solution {
public:

   void findInorder(TreeNode* root, vector<TreeNode*>& inorder){ 
      if(!root){
        return;
      }

      findInorder(root->left, inorder);
      inorder.push_back(root);
      findInorder(root->right, inorder);
   }

    void recoverTree(TreeNode* root) {


        vector<TreeNode*> inorder;
        findInorder(root, inorder);

        int first,second = -1;

        for(int i=1;i<inorder.size();i++){
           if(inorder[i]->val < inorder[i-1]->val){
            if(first == -1){
                first = i-1;
                second = i;
            }
            else{
                second = i;
            }
           }
        }

        //swapping to recover original bst

        if(first != -1){
              int value = inorder[first]->val;
            inorder[first]->val = inorder[second]->val;
            inorder[second]->val = value;
        }
        

        return;
    }
};

//APPROACH:- WE CAN ONLY KNOW WHERE THE SWAPPING TOOK PLACE BY TRAVERSING THE TREE IN INORDER TRAVERSAL AS IF THE NODE ARE SWAPPED THEN THE INCRESING ORDER WE USED TO GET BY TRAVERSING THE TREE IN INORDER WILL BE HAMPERED

//SO WE WILL FIRST STORE THE INORDER TRAVERSAL OF THE BST ...BUT WE WILL NOT STORE THEM IN ARRAY OF INTEGER... WE WILL STORE THE ADDRESS OF NODES THAT WILL COME IN INORDER TRAVERSAL SO WHILE CHECKINH WHEN WE WILL GET THE POINT WHERE VALUES OF NODE GET SWAPPED THERE WE WILL SIMPLY SWAP THEM BACK TO RECOVER THE ACTUAL CORRECT BST