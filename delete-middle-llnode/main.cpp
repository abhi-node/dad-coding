#include <vector>
#include <iostream>

using namespace std;

struct LLNode {
    int value;
    LLNode* next;
    LLNode(int v) {
        value = v;
        next = nullptr;
    }
    LLNode(int v, LLNode* n) {
        value = v;
        next = n;
    }
};

void deleteMiddle(LLNode*& head) { // Pass a reference to the pointer in the single node case
    if (!head) return; // Handle empty list case
    LLNode* fast = head; // Init our fast pointer
    LLNode* slow = head; // Init our slow pointer
    LLNode synth = LLNode(0, head); // Our "prev" pointer - a synthetic node we use to track the node before the middle.
    // Synth is a stack var, so it will auto cleanup after its out of scope. No need for a delete here.
    LLNode* prev = &synth;
    while (fast->next && fast->next->next) {
        fast=fast->next->next;
        slow=slow->next;
        prev = prev->next;
    }

    if (fast->next) { // The even case; If the list is even, the fast pointer will be the node before the final one.
        LLNode* tmp = slow->next; // value to be removed
        slow->next=slow->next->next;
        delete tmp;
    } else { // Odd case; fast->next is always null in the odd case
        prev->next = slow->next;
        if (slow == head) {
            head = nullptr; // If the list is only 1 node long, we will delete the underlying struct the head is pointing to
            // Letting that happen would cause undefined behavior from the caller - just set it to null here
            // This is why we passed the "&" suffix - passes a direct ref to the variable, so we can adjust it here.
        }
        delete slow;
    }
}

// Logic - we can use a fast pointer (iterates two nodes at a time) and a slow pointer to lock the middle node.
// For the odd case, the slow pointer will be initialized to the middle node - create a synthetic prev node
// prev node lets us track the node before the middle for removal.
// Ex:
// 1, 2, 3, 4, 5 -> f=1, f=3, f=5 -> s=1, s=2, s=3 -> p=SYNTH, p=1, p=2 END;
// use remove s by using p->next = s->next; delete the node s represents.
// Finally, delete the synthetic node we created.
//
// For the even case, the slow pointer will be initialized to the last node of the first half of the list.
// It's straightforward here - slow->next=slow->next->next, delete the node between them
// Ex:
// 1, 2, 3, 4 -> f=1, f=3 -> s=1, s=2 -> p=SYNTH, p=1 END;
// We don't need to care about p here.


// ---------------------------------------------------------
// Helper Functions for Testing - This is NOT SOLUTION CODE
// DON'T COPY THE CODE BELOW IF YOU ARE SENDING IT
// THIS IS LLM GENERATED TESTING CODE, NOT ALGORITHM SOLUTION
// ---------------------------------------------------------

// Helper to create a linked list from a vector of integers
LLNode* createList(const vector<int>& vals) {
    if (vals.empty()) return nullptr;
    LLNode* head = new LLNode(vals[0]);
    LLNode* current = head;
    for (size_t i = 1; i < vals.size(); ++i) {
        current->next = new LLNode(vals[i]);
        current = current->next;
    }
    return head;
}

// Helper to print the linked list visually
void printList(LLNode* head) {
    if (!head) {
        cout << "Empty";
    }
    while (head) {
        cout << head->value << (head->next ? " -> " : "");
        head = head->next;
    }
    cout << "\n";
}

// Helper to free memory after tests to prevent leaks
void freeList(LLNode* head) {
    while (head) {
        LLNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// ---------------------------------------------------------
// Main Function with Test Cases
// ---------------------------------------------------------

int main(void) {
    // Define our test scenarios
    vector<vector<int>> testCases = {
        {},                 // 1. Empty list
        {1},                // 2. Single node (Edge case)
        {1, 2},             // 3. Two nodes (Even edge case)
        {1, 2, 3},          // 4. Three nodes (Odd case)
        {1, 2, 3, 4},       // 5. Four nodes (Even case)
        {1, 2, 3, 4, 5},    // 6. Five nodes (Odd case)
        {1, 2, 3, 4, 5, 6}  // 7. Six nodes (Even case)
    };

    int testNum = 1;
    for (const auto& testValues : testCases) {
        cout << "Test Case " << testNum++ << ":\n";
        LLNode* head = createList(testValues);

        cout << "  Original : ";
        printList(head);

        deleteMiddle(head);

        cout << "  After    : ";
        printList(head);
        cout << "--------------------------------\n";

        freeList(head); // Clean up memory
    }

    return 0;
}
