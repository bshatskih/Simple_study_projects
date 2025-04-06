#ifndef SWAP_NODES_IN_PAIRS__SOLUTION_H_
#define SWAP_NODES_IN_PAIRS__SOLUTION_H_



struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};




class Solution {
 public:
  ListNode *swapPairs(ListNode *head) {
    if (head->next != nullptr) {
      head->next = head->next->next;
      head->next = head;
      head
    }
  }
};

#endif //SWAP_NODES_IN_PAIRS__SOLUTION_H_
