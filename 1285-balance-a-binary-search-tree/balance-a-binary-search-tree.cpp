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

    void inorder(TreeNode* root, vector<int>& arr){
        if(!root){
            return;
        }

        inorder(root->left, arr);
        arr.push_back(root->val);
        inorder(root->right, arr);
    }

    TreeNode* buildBalanced(vector<int>& arr, int start,int end){
        if(start>end){
            return NULL;
        }
        int mid = start+(end-start)/2;
        TreeNode* temp = new TreeNode(arr[mid]);

        temp->left = buildBalanced(arr,start,mid-1);
        temp->right = buildBalanced(arr,mid+1,end);
         
        return temp;
    }

    TreeNode* balanceBST(TreeNode* root) {
        vector<int> arr;
        inorder(root,arr);
        return buildBalanced(arr,0,arr.size()-1);
    }
};


//APPROACH IS WE WILL CONVERT THE TREE INTO AN ARRAY BY TRAVERSING THE ARRAY WITH INORDER TRAVERSAL THEN AS WE WILL HAVE THE NODES OF THE TREE IN SORTED ORDER SO WE CAN CREATE A BALANCED BST FROM THAT ARRAY

//WE CAN DO THAT BY SPLITING THE ARRAY FROM MIDDLE EVERY TIME AND CREATING A NODE FORM MIDDLE ELEMENT