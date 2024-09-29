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
 
    void helperFun(TreeNode* root, int &prevSum){
        if(!root){
            return;
        }

        //doing traversal in right->node->left order for reverse inorder traversal

        helperFun(root->right, prevSum);

        root->val = root->val+prevSum;
        prevSum = root->val;

        helperFun(root->left, prevSum);
    }

    TreeNode* bstToGst(TreeNode* root) {
        int prevSum  = 0;
        helperFun(root, prevSum);
        return root;
    }
};