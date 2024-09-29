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

class Box {

    public:
    bool Bst;
    int sum;
    int min;
    int max;

    Box(){
      Bst = 1;
      sum = 0;
      min = INT_MAX;
      max = INT_MIN;
    }

};

class Solution {
public:

    Box* find(TreeNode* root, int & maxsum){

        //CURRENT ROOT IS NULL
        if(!root){
           return new Box();
        }

        //CURRENT ROOT EXISTS

        Box* leftBox = find(root->left, maxsum);
        Box* rightBox = find(root->right, maxsum);

        if( leftBox->Bst && rightBox->Bst && root->val > leftBox->max && root->val < rightBox->min ){
            leftBox->sum = leftBox->sum + rightBox->sum + root->val;
            leftBox->min = min(leftBox->min, root->val);
            leftBox->max = max(rightBox->max, root->val);

            maxsum = max(maxsum, leftBox->sum);
            return leftBox;
        }
        else{
            leftBox->Bst = 0;
            return leftBox;
        }

    }


    int maxSumBST(TreeNode* root) {

        int maxsum = 0;
        find(root, maxsum);
        return maxsum;
        
    }
};