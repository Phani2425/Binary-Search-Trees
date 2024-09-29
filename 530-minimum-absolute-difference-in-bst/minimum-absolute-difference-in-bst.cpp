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
//  */
// class Solution {
// public:
//     int getMinimumDifference(TreeNode* root) {
//         stack<TreeNode*> st;
//         int minSum = INT_MAX;

//         while(root){
//             st.push(root);
//             root = root->left;
//         }

//         while(!st.empty()){
//             TreeNode* temp = st.top();
//             st.pop();
//             if(temp->right){
//                 TreeNode* rightNode = temp->right;
//                 while(rightNode){
//                     st.push(rightNode);
//                     rightNode = rightNode->left;
//                 }
//             }

//             if(!st.empty()){
//                 minSum = min(minSum, st.top()->val - temp->val);
//             }
//         }

//         return minSum;
        
//     }
// };

//SOLVING THE QUESTION WITHOUT ANY EXTRA SPACE
//WE WILL DO IT BY MAINTAINING A PREV VALUE WHICH WILL STORE THHE PREVIOUS VALUE OF A NODE IN INORDER TRAVERSAL
 
class Solution {
public:

    void helperFunction(TreeNode* root,TreeNode* & prev, int & minDiff){
        if(!root){
            return;
        }

        helperFunction(root->left, prev, minDiff);
        if(prev==NULL){
            prev = root;
        }
        else{
            minDiff = min(minDiff, (root->val - prev->val));
            prev = root;
        }
        helperFunction(root->right, prev, minDiff);


    }

    int getMinimumDifference(TreeNode* root) {
       
       int minDiff = INT_MAX;
       TreeNode * prev = NULL;
       helperFunction(root,prev,minDiff);

       return minDiff;
        
    }
};