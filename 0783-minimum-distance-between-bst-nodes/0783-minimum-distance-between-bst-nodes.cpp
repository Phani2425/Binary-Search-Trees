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
    int minDiff = INT_MAX;
    int prevValue = -1;

    void inorder(TreeNode * root){
        if(!root){
            return;
        }
        
        inorder(root->left);

        if(prevValue == -1){
            prevValue = root->val;
        }
        else{
            minDiff = min(minDiff, abs(root->val - prevValue));
            prevValue = root->val;
        }

        inorder(root->right);

    }


    int minDiffInBST(TreeNode* root) {
        inorder(root);
        return minDiff;
    }
};