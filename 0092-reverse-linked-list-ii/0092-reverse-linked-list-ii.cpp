/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:

    ListNode* reverseList(ListNode* start,int count, ListNode* prev){
        ListNode* curr = start;
        ListNode* next = start->next;

        while(count--){
            curr->next = prev;
            prev = curr;
            curr = next;
            if(curr){
                next = curr->next;
            }
        }

        return prev;
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(left==right){
            return head;
        }

        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* leftptr=dummy;
        ListNode* rightptr=dummy;

        int count = right-left+1;

       while(right--){
         rightptr = rightptr->next;
         if(left > 1){
            leftptr = leftptr->next;
            left--;
         }

       }

        leftptr->next = reverseList(leftptr->next, count, rightptr->next);

        return dummy->next;
    }
};