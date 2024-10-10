class Solution {
public:

   void findSubsequences(vector<int>&candidates,int target,int index,vector<int>&temp,int sum,vector<vector<int>>&ans){

    //base caes
    if(index == candidates.size()){
        return;
    }
    if(sum>target){
        return;
    }
    if(sum==target){
        ans.push_back(temp);
        return;
    }

    //recursive case
    //TAKE
    temp.push_back(candidates[index]);
    sum += candidates[index];
    findSubsequences(candidates,target,index,temp,sum,ans);

    //NOT TAKE
    temp.pop_back();
    sum -= candidates[index];

    findSubsequences(candidates,target,index+1,temp,sum,ans);

   }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
      vector<vector<int>> ans;
      vector<int>temp;
      findSubsequences(candidates,target,0,temp,0,ans);  

      return ans;
    }
};