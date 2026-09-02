#include <stdio.h>
#include "../Status.h"
#include "../Linear List/SqList1.h"

/* Comparison function: check if two elements are equal (used by LocateElem_Sq) */
Status equal(ElemType a, ElemType b) {
    return (a == b) ? TRUE : FALSE;
}

/* Visit function: print element value (used by ListTraverse_Sq) */
void printElem(ElemType &e) {
    printf("%d ", e);
}

/* Main test function */
int main() {
    SqList L;
    Status s;
    int i;
    ElemType e, pre, next;

    // ---------- 1. Initialization ----------
    printf("========== Initialize sequence list ==========\n");
    s = InitList_Sq(L);
    if (s == OK) {
        printf("Initialization successful, current length: %d, capacity (bytes): %d\n", L.length, L.listsize);
    } else {
        printf("Initialization failed!\n");
        return -1;
    }

    // ---------- 2. Insert elements ----------
    printf("\n========== Insert elements 1~10 ==========\n");
    for (i = 1; i <= 10; i++) {
        s = ListInsert_Sq(L, i, i * 2);   // insert values 2,4,6,...,20
        if (s != OK) {
            printf("Failed to insert element %d\n", i);
        }
    }
    printf("After insertion, length: %d\n", ListLength_Sq(L));
    printf("Elements: ");
    ListTraverse_Sq(L, printElem);
    printf("\n");

    // ---------- 3. Get element ----------
    printf("\n========== Get the 3rd element ==========\n");
    s = GetElem_Sq(L, 3, e);
    if (s == OK) {
        printf("The 3rd element value is: %d\n", e);
    } else {
        printf("Failed to get element!\n");
    }

    // ---------- 4. Locate element ----------
    printf("\n========== Locate element 10 ==========\n");
    i = LocateElem_Sq(L, 10, equal);
    if (i != 0) {
        printf("Element 10 is at position %d\n", i);
    } else {
        printf("Element 10 not found\n");
    }

    // ---------- 5. Predecessor and successor ----------
    printf("\n========== Find predecessor and successor of element 10 ==========\n");
    s = PriorElem_Sq(L, 10, pre);
    if (s == OK) {
        printf("Predecessor of 10 is: %d\n", pre);
    } else if (s == INFEASIBLE) {
        printf("10 is the first element, no predecessor\n");
    } else {
        printf("Element 10 not found\n");
    }

    s = NextElem_Sq(L, 10, next);
    if (s == OK) {
        printf("Successor of 10 is: %d\n", next);
    } else if (s == INFEASIBLE) {
        printf("10 is the last element, no successor\n");
    } else {
        printf("Element 10 not found\n");
    }

    // ---------- 6. Delete element ----------
    printf("\n========== Delete the 3rd element ==========\n");
    s = ListDelete_Sq(L, 3, e);
    if (s == OK) {
        printf("Deleted element value: %d\n", e);
        printf("After deletion, length: %d\n", ListLength_Sq(L));
        printf("Elements: ");
        ListTraverse_Sq(L, printElem);
        printf("\n");
    } else {
        printf("Deletion failed!\n");
    }

    // ---------- 7. Clear and check empty ----------
    printf("\n========== Clear the list ==========\n");
    s = ClearList_Sq(L);
    if (s == OK) {
        printf("Cleared successfully, length: %d\n", ListLength_Sq(L));
        printf("Is list empty? %s\n", ListEmpty_Sq(L) == TRUE ? "Yes" : "No");
    }

    // ---------- 8. Re-insert to test expansion ----------
    printf("\n========== Insert 101 elements (test expansion) ==========\n");
    for (i = 1; i <= 101; i++) {
        s = ListInsert_Sq(L, i, i);
        if (s != OK) {
            printf("Failed to insert element %d\n", i);
            break;
        }
    }
    printf("After inserting 101 elements, length: %d, capacity (bytes): %d\n", L.length, L.listsize);

    // ---------- 9. Destroy list ----------
    printf("\n========== Destroy the list ==========\n");
    s = DestroyList_Sq(L);
    if (s == OK) {
        printf("Destroyed successfully, elem = %p, length = %d, listsize = %d\n", L.elem, L.length, L.listsize);
    }

    return 0;
}
