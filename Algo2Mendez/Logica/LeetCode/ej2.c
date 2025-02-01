#include <stdlib.h>

// You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
	struct ListNode *result =
		(struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *current = result;
	int carry = 0;

	while (l1 != NULL || l2 != NULL) {
		int sum = carry;

		if (l1 != NULL) {
			sum += l1->val;
			l1 = l1->next;
		}

		if (l2 != NULL) {
			sum += l2->val;
			l2 = l2->next;
		}

		carry = sum / 10;
		current->val = sum % 10;

		if (l1 != NULL || l2 != NULL) {
			current->next = (struct ListNode *)malloc(
				sizeof(struct ListNode));
			current = current->next;
		}
	}

	if (carry > 0) {
		current->next =
			(struct ListNode *)malloc(sizeof(struct ListNode));
		current = current->next;
		current->val = carry;
	}

	current->next = NULL;

	return result;
}