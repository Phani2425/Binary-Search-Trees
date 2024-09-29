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

class BstIterator {

    stack<TreeNode*> myStack;
    bool reverse;
    
    public:
    BstIterator(TreeNode* root,bool isReverse){
     reverse = isReverse;
      pushAll(root);
    }

    int next(){
       TreeNode* temp = myStack.top();
       myStack.pop();
       if(!reverse && temp->right){
        pushAll(temp->right);
       }
       else if(reverse && temp->left){
        pushAll(temp->left);
       }

       return temp->val;
    }

    private:
    void pushAll(TreeNode* root){
        while(root){
            myStack.push(root);
        if(reverse){
            root = root->right;
        }
        else{
            root = root->left;
        }
        }
    }

};


class Solution {
public:
    bool findTarget(TreeNode* root, int k) {

        BstIterator * l = new BstIterator(root,false);
        BstIterator* r = new BstIterator(root,true);

        int i = l->next();
        int j= r->next();

        while(i < j){
            if(i + j == k){
                return true;
            }
            else if(i + j < k){
                i = l->next();
            }
            else{
                j = r->next();
            }
        } 

        return false;
        
    }
};


//APPROACH:-

//WHAT WE CAN DO IS TRAVERSE THE BST IN INORDERR TRAVERSAL, STORE IT IN AN ARRAY OR VECTOR AND THE WE CAN USE A TWO POINTER APPROACH [WHICH IS THE BEST APPROACH TO SOLE PROBLEMS LIKE TWO SUM , THREE SUM ETC] SO IN THIS APPROACH T.C WILL BE 0(N) WHILE SPACE COMPLEXITY WILL BE 0(N) DUE TO EXTRA SPACE TAKEN BY STORING THE INORDER TRAVERSAL OF BST

//BUT WE CAN OPTIMISE THE SPACE COMPLEXITY BY CONCURRENT TRAVERSAL AND COMPARISION WHERE WE STORE THE TRAVERSAL IN THE STACK WHICH GENERALLY TAKES A TIME COMPLEXITY OF O(H) {H=HEIGHT OF THE TREE}

//SO WHAT WE WILL DO IS :- WE WILL CREATE TWO STACK ONE WILL HAVE INORDER TRAVERSAL AND ANOTHER WILL HAVE THAT IN REVERSE MANNER AND FOR COMPARISION INSTEAD OF USING  POINTERS LIKE WE WERE DOING IN NORMAL ARRAY WE WILL COMPARE THE ELEMENT PRESENT AT TOP OF THE BOTH STACK.

//WHEN ELEMENT AT TOP OF BOTH STACK CROSS EACH OTHER THEN WE WILL STOP THE COMPARISION LIKE WE WERE DOING IN TWO POINTER CONCEPT IN NORMAL ARRAY

//SO FOR CREATING THOSE TWO STACKS AND ITERATING OVER THEM WE WILL CREATE "BSTITERATOR" CLASS LIKE WE HAVE DID IN ONE SUCH QUESTION I SOLVED NAMED:-LEETCODE:- 173