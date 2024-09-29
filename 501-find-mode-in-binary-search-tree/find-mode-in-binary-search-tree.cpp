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

    void helperFunction(TreeNode * root, pair<TreeNode*, int> &prev, vector<int>& ans, int &maxFreq){
        if(!root){
            return;
        }

        helperFunction(root->left, prev, ans, maxFreq);
        if(prev.first != NULL){
            if(prev.first->val == root->val){
                prev.second++;
            }
            else{
                if(prev.second == maxFreq){
                    ans.push_back(prev.first->val);
                }
                else if(prev.second > maxFreq){
                    maxFreq = prev.second;
                    while(ans.size()>0){
                       ans.pop_back();
                    }
                    ans.push_back(prev.first->val);
                }
                prev.first = root;
                prev.second = 1;
            }
        }
        else{
            prev.first = root;
            prev.second = 1;
        }

        helperFunction(root->right,prev, ans, maxFreq);

    }

public:
    vector<int> findMode(TreeNode* root) {
        pair<TreeNode* ,int> prev (NULL,0);
        vector<int> ans;
        int maxFreq = 1;

        helperFunction(root, prev, ans, maxFreq);

        if(prev.second == maxFreq){
                    ans.push_back(prev.first->val);
                }
        else if(prev.second > maxFreq){
                    maxFreq = prev.second;
                    while(ans.size()>0){
                       ans.pop_back();
                    }
                    ans.push_back(prev.first->val);
                }

        return ans;
        
    }
};

//BRUTE FORCE APPROACH:- WE CAN TRAVERSE THE TREE AND STOR ETHE FREQUENCY OF THE NODES IN A MAP THEN BY TRAVERSINNG THE MAP WE CAN FIND OUT THE NODES HAVINNG MAXIMUM FREQUENCY 

//BETTER APPROACH:- BUT INSTEAD OF USING MAP WE CAN STILL SOLVE THIS WITH A TIME COMPLEXITY OF 0[1] SO LETS DO THAT