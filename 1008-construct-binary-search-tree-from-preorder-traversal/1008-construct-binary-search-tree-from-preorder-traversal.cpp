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

     int findIndexOfNewNodeInInorder(int val, vector<int>& inorder,int inStart, int inEnd){
        for(int i=inStart; i<=inEnd;i++){
            if(inorder[i] == val){
                return i;
            }
        }
        return -1;
     }

    TreeNode* bstConstructor(vector<int> & preorder, vector<int> inorder, int currIndex ,int inStart, int inEnd){
        if(inStart > inEnd){
            return NULL;
        }

        TreeNode * temp = new TreeNode(preorder[currIndex]);
        int index = findIndexOfNewNodeInInorder(preorder[currIndex],inorder,inStart,inEnd);

        temp->left = bstConstructor(preorder, inorder, currIndex+1, inStart, index-1);
        temp->right = bstConstructor(preorder,inorder, currIndex +( index-inStart+1), index+1, inEnd);

        return temp;
    }

    TreeNode* bstFromPreorder(vector<int>& preorder) {
        vector<int> preorderCpy = preorder;
         sort(preorder.begin(),preorder.end());
        return bstConstructor (preorderCpy,preorder ,0 , 0, preorder.size()-1);
    }
};