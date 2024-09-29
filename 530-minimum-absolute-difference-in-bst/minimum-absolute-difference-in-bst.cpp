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
    int getMinimumDifference(TreeNode* root) {
        stack<TreeNode*> st;
        int minSum = INT_MAX;

        while(root){
            st.push(root);
            root = root->left;
        }

        while(!st.empty()){
            TreeNode* temp = st.top();
            st.pop();
            if(temp->right){
                TreeNode* rightNode = temp->right;
                while(rightNode){
                    st.push(rightNode);
                    rightNode = rightNode->left;
                }
            }

            if(!st.empty()){
                minSum = min(minSum, st.top()->val - temp->val);
            }
        }

        return minSum;
        
    }
};