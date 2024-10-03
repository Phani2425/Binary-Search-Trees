#include<bits/stdc++.h>
using namespace std;

class Node {
  public:
  int data;
  Node* left;
  Node* right;
  int height;

  Node(int value){
    data = value;
    left = right = NULL;
    height = 1; // new node is initially added at height 1
  }
};

//function for displaying the AVL tree
void display(Node * root){
    if(root == NULL){
        cout<<"Tree is empty... Insert some Node..."<<endl;
        return;
    }
    else{
        queue<Node*> q;
        q.push(root);
         while(!q.empty()){
            if(q.front() == NULL){
                cout<<"Null"<<" "<<endl;
                q.pop();
            }
            else{
            Node* temp = q.front();
            q.pop();
            cout<<temp->data<<" ";

              q.push(temp->left);
              q.push(temp->right);
            }
         }
    }

    return;
}

int getHeight (Node* root){
    if(!root){
        return 0;
    }else{
        return root->height;
    }
}

//functions for rotations
Node* leftRotation(Node * root){

    Node * child = root->right;
    Node* temp = child->left;
    child->left = root;
    root->right = temp;
    //height update karna to me bhul hi gaya tha
    //kyu ki root aur uski right node ki place change hui hai {hmm aur kisiska height change nehi hua gaur se dekho} to hame unka height update karna padega

    //aur ek imp baat height updation ka bhi ek order hai means first root ka height update hoga jo abhi niche agay hai then jake child ka height update hoga jo ki abhi root ka parent banagay hai 
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    child->height = 1 + max(getHeight(child->left), getHeight(child->right));

    return child;

}

Node* rightRotation(Node * root){
    Node * child = root->left;
    Node* temp =  child->right;
    child->right = root;
    root->left = temp;

    //yaha pe bhi simillarly height update hoga

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    child->height = 1 + max(getHeight(child->left), getHeight(child->right));

    return child;
}

Node* insert (Node* root,int value){
    if(!root){
        return new Node(value);
    }

    if(root->data > value){
        root->left = insert(root->left,value);
    }
    else if(root->data < value) {
        root->right = insert(root->right, value);
    }
    else{
        return root;//in case when there is duplicate elemnt we will not add them
    }

    //now as a new node added so we will now backtrack and while this we will travel through all nodes we have travelled for adding this node
    //so what we will do is update their height and check wheather they are balanced or not if not then try to balance them and after balancing them return the address of root of balanced subtree if already balanced then just return their address [i.e root] which will go and stored in their parents left or right pointer

    //updating the height first

    //so height of each node will be updated as max(height of left subtree, height of right subtree)
    //but the issue here is if we directly try to access root->left->height then we might get error as their might be a chance where the root dont have left or right side so accessing them will give error
    //to tackle this we have to use multiple if else cases where we have to check either both are present if only one is present then which side is present and many more which will make my code more complex so i will avoid that 
    
    //to simplyfy this more i got an idea that if i had a function which will return the height if certain side exist or return 0 if that side dont exist then that will be great ....

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    //now with the same function i will check either the current root is balanced or not

    int balanced = getHeight(root->left) - getHeight(root->right);

    //checking imbalanceness
    if(balanced > 1){

        if(value < root->left->data){
            return rightRotation(root);
        }
        else{
           root->left =  leftRotation(root->left);
            return rightRotation(root);
        }

    }
    else if(balanced < -1){

        if(value < root->right->data){
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
        else{
            return leftRotation(root);
        }

    }else{
        return root;
    }


    
}

//FUNNCTION FOR DELETING NODE FROM THE AVL TREE 
Node *deleteNode(Node *root, int value)
{

    bool flag = 0; // this is the flag that will tell me if  the value passed as atribute is deleted from the tree or absent in the tree

    if (!root)
    {
        return NULL;
    }

    if (root->data == value)
    {
        flag = 1;

        // delete the node and return the updated node address which might be NULL or address of some other node and this returned address will get stored in the parent of the target node

        // NODE HAVE BOTH CHILD
        if (root->left && root->right)
        {
            Node* temp = root->right;

            while(temp->left != NULL){
                temp = temp->left;
            }
            int valueToBeReplaced = temp->data;

            root->right = deleteNode(root->right,temp->data);//recursive call

            root->data = valueToBeReplaced;

            return root;


            //NOW AN EDGE CASE ARRIVES THAT WHEN WE WERE DELETING NODE HAVING SINGLE CHILD OR LEAF NODE THEN WE NEED NOT TO UPDATE ANY HEIGHT BECAUSE HEIGHT MIGHT CHANGE ONLY FOR PARENT OF THE TARGET NODE NOT OTHER NODES AND THAT UPDATION OF HEIGHT OF PARENT NODE WE ARE DOING WH9ILE BACKTRACKING

            //BUT WHEN A NODE HAVE BOTH  CHILD THEN NOTICE THAT EITHER THE MAX VALUE NODE IN LEFT SUBTREE OR THE MIN VALUE NODE OF THE RIGHT SUBTREE I S GETTING DELETED WHICH MEANS HERE NOT ONLY HEIGHT OF PARENT OF TARGET NODE MIGHT GET CHANGED BUT ALSO THE HEIGHT OF NODES OF LEFTSUBTREE (IN CASE WHEN WE REPLACE THE TARGET NODE WITH MAX OF LEFT SUBTREE OF TARGET NODE) OR HEIGHT OF NODES OF RIGHT SUBTREE (IN CASE WHEN WE REPLACE THE TARGET NODE WITH THE MIN OF RIGHT SUBTREE OF TATRGET NODE) WILL ALSO CHANGE DOE TO NODE DELETION FROM THEM

            //SO I THOUGHT I WILL CREATE A FUNCTION TO UPDATE THEM AND AFTER DOING THAT ONLY WE WILL RETURN THE ROOT NODE TO ITS PARENT FROM WHERE FURTHUR HEIGHT UPDATION AND BALANCE CHECKING WILL HAPPEN ->>>>>>>>>>> WRONG!!!!WRON!!!!WRONG!!!!!

            //BECAUSE THINK THAT IF HEIGHT OF THEM CHANGES THE OBVIOUSLY ANY OF THEM MIGHT GET UNBALACED TOO HOW CAN WE SKIP CHECKING THEIR BALANCING ????

            //BASICALLY WHEN WE TRY TO DELETE ANY NODE HAVING BOTH CHILD THEN ACTULLY THE MAX NODE OF THE LEFT TREE OF TARGET NODE OR MIN NODE OF THE RIGHT SUBTREE OF TARGET NODE GETS DELETED BUT BEFORE THAT ITS VALUE IS COPIED TO TARGET NODE WHICH SEEMS THAT THE TARGET NODE GOT DELETED  ....

            //FOR THIS REASON ALL THE NODE ABOVE THE ACTUAL NODE THAT GOT DELETED ARE AFFECTED SO UPDATING THEEIR HEIGHT AND CHHECKING THEIR BALANCENESS THEN BALANCING THEM BECOMES NECESSARY

            //BUT IF WE THINK TO DO THEM MANUALLY BY AFUNCTION THEM THAT BECOMES HIGHLY COMMPLEX AND IN THAT FUNCTION WE HAVE TO WRITE SAME THING AS WE ARE WRITING IN THIS FUNCTION.........WHAT???? REALLY???? YES >>>>>>>>>> JUST NOTICE THAT IN THIS CASE WE ARE ALSO DELETING A NODE ONLY CHANGE IS HERE THE TARGET NODE IS THE ROOT NODE AND THE MIN OF RIGHT SUBTREE OF THAT TARGET NODE OR MAX OF LEFT SUBTREE OF THAT TARGET NODE BECOMES TARGET

            //SO WE CAN RECURSIVELY CALL THIS DELETEnODE FUNCTION WHICH WILL DELETE THAT NODE ... ALSO IT WILL UPDATE HEIGHT OF ALL NODES ABOVE IT ALSO CHECK BALANCENESS ALSO BALANCE THEM ...SO OUR WORK WILL BE DONE SIMPLY

            //BUT BEFORE DELETINNG THAT WE HAVE TO STORE ITS DATA AS WE HAVE TO REPLACE THAT WITH THE DATA OF OUR ACTUAL TARGET NODE WHICH WE GOT ORDER TO DELETE ACTUALYY.... AND AFTER DELETING THE 2ND TARGET NODE [WHICH WE WILL DECIDE:- EITHER THAT WILL BE  MAX NODE OF THE LEFT TREE OF TARGET NODE OR MIN NODE OF THE RIGHT SUBTREE OF TARGET NODE] WE WILL REPLACE THE COPIED VALUE INTO THE 1ST TARGET NODE AND RETURN ITS ADDRESS

        }

        // NODE HAVE SINGLE CHILD
        else if(root->left){
            Node * temp = root->left;
            delete root;
            return temp;

        }
        else if(root->right){
            Node* temp = root->right;
            delete root;
            return temp;

        }

        // NODE IS LEAF
        else{
            delete root;
            return NULL;
        }

        
    }

    if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }

    // updating the height before returning // I GOT THE DOUDT ABOUT CAN WE UPDATE THE HEIGHT AFTER CHECKING THE BALANCING ??? ->>>> OFCOURSE WWE CANN DO THAT.... NO ISSUE
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // checking if the node is balanced or not
    int balanced = getHeight(root->left) - getHeight(root->right);

    if (balanced > 1)
    {
        if (getHeight(root->left->left) > getHeight(root->left->right))
        {
            // means LL rotation:- because balanced >1 hua matlab left side ka height jyada hai to 1st character L hoagaya ab ham root ka left node se pata laga sakte hein ki next character kya hoga???
            // agar root ka leftNode ka left height right height se jyada hua iska matlab ye hai ki root ka left subtree ka height wohi decide kar raha hai to agar ham usko kam karden to hamara root balanced ho jayega ...aur usko kam karne keliye hame LL roatation lagana padega

            return rightRotation(root);
        }
        else
        {
            // means LR rotation -> because agar root ka left node ka right side jyada heiight ka hai to root ka leftnode ka height uska right side decide kar raha hai because height to dono side ke maximum se banta hai na to yaha pe LR roation hoga

            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    else if (balanced < -1)
    {

        if (getHeight(root->right->left) > getHeight(root->right->right))
        {
            // RL
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
        else
        {
            // RR
            return leftRotation(root);
        }
    }

    // REMEMBER A CASE IF AFTER GETTING THE FIRST CHARCTER WHEN WE COMPARE THE LEF AND RIGHT SUBTREE OF LEFT OR RIGHT CHILD OF THE NODE AND BOTH SIDE HAVE SAME HEIGHT THEN BOTH CONTRIBUTE TO THE HEIGHT OF THAT SIDE AS BOTH HAVE SAME HEIGHT SO ANY ROTAION I.E LL OR LR (IN CASE WHEN BALANCED > 1) AND RR OR RL (IN CASE WHEN BALANCED < -1) WILL MAKE THE TREE BALANCED

    // THIS MEANS WHEN BOTH GETHEIGHT CALL RETURN SAME HEIGHT THEN THAT CASE WILL BE HANDLED BY ELSE CASE......... TRY DRY RUNNING SUCH CASE

    //              80
    //          70      85
    //      65     75  N   89
    //   60   68 74   78        => THIS CASE WHEER WE HAVE TO DELETE 89 THEN 80 WILL BE UNBALANCED AND IN THIS CASE BOTH LL AND LR CAN BALANCE THE TREE...

    return root;
}


int main() {

    Node* root = NULL;

    int choice;
    cout<<"Enter your Choice..."<<endl;
    cout<<"1. Insertion"<<endl;
    cout<<"2. Deletion"<<endl;
    cout<<"3. Display Tree"<<endl;
    cout<<"4. Exit"<<endl;

    while(1){
        cout<<"Enter choice:-";
        cin>>choice;

        switch(choice){
            case 1:
            cout<<"Enter a node data to be inserted:-" <<endl;
            int value;
            {cin>>value;
                root = insert(root,value);
                break;}
            case 2:
              {cout<<"no function written yet...."<<endl;
                break;}
            case 3:
                {display(root);
                break;}
            case 4:
                {exit(0);
                break;}
            default:
                cout<<"Invalid Choice!";
        }
    }

    return 0;
}


//    I DID IT ON MY OWN BABE [YOU CAN DO ANYTHING JUST BELIVE IN YOURSELF]
