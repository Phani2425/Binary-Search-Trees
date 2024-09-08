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



   //APPROACH - 2
    //THIS HAS A TIME COMMPLEXITY OF O(N) WHILE THE PREVIOUS METHODD HAVE TIME COMLEXITY OF O(LOGN)

        TreeNode * helperFunction (vector<int>& preorder, int & index, int Lower, int Upper){
            //base case
            if(index == preorder.size() || preorder[index] < Lower || preorder[index] > Upper){
                return NULL;
            }

            TreeNode * temp = new TreeNode(preorder[index++]);

            temp->left = helperFunction(preorder, index, Lower, temp->val);
            temp->right = helperFunction(preorder,index,  temp->val, Upper);


            return temp;

        }


        TreeNode* bstFromPreorder(vector<int>& preorder) {
            int index = 0;
       
       return helperFunction (preorder, index , INT_MIN, INT_MAX );
    }
};
