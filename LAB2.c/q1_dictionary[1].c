/*
 * DAA Lab-02, Q1: Dictionary operations on 6 structures.
 * Implements Search and Insert (the two operations whose costs most
 * clearly separate the structures) on:
 *   1. Unsorted array
 *   2. Sorted array
 *   3. Singly linked unsorted list
 *   4. Singly linked sorted list
 *   5. Doubly linked unsorted list
 *   6. Doubly linked sorted list
 *
 * For each structure and each n, we:
 *   - build a dictionary of n random keys
 *   - time SEARCH_TRIALS searches for random (mostly-absent) keys
 *   - time INSERT_TRIALS insertions of new random keys
 * and print average time per operation (microseconds) to results.csv.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SEARCH_TRIALS 200
#define INSERT_TRIALS 200

/* ---------- timing helper ---------- */
static double now_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;
}

/* =========================================================
   1. UNSORTED ARRAY   -> Search O(n), Insert O(1)
   ========================================================= */
int arr_search(int *a, int n, int key) {
    for (int i = 0; i < n; i++) if (a[i] == key) return i;
    return -1;
}
int arr_insert_unsorted(int *a, int n, int key) {
    a[n] = key;
    return n + 1;
}

/* =========================================================
   2. SORTED ARRAY     -> Search O(log n), Insert O(n)
   ========================================================= */
int arr_binary_search(int *a, int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (a[mid] == key) return mid;
        else if (a[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
int arr_insert_sorted(int *a, int n, int key) {
    int i = n - 1;
    while (i >= 0 && a[i] > key) { a[i + 1] = a[i]; i--; }
    a[i + 1] = key;
    return n + 1;
}

/* =========================================================
   3 & 5. SINGLY / DOUBLY LINKED, UNSORTED -> Search O(n), Insert O(1) head
   ========================================================= */
typedef struct SNode { int key; struct SNode *next; } SNode;
typedef struct DNode { int key; struct DNode *next, *prev; } DNode;

SNode* snode_search(SNode *head, int key) {
    for (SNode *p = head; p; p = p->next) if (p->key == key) return p;
    return NULL;
}
SNode* snode_insert_front(SNode *head, int key) {
    SNode *n = malloc(sizeof(SNode));
    n->key = key; n->next = head;
    return n;
}
DNode* dnode_search(DNode *head, int key) {
    for (DNode *p = head; p; p = p->next) if (p->key == key) return p;
    return NULL;
}
DNode* dnode_insert_front(DNode *head, int key) {
    DNode *n = malloc(sizeof(DNode));
    n->key = key; n->next = head; n->prev = NULL;
    if (head) head->prev = n;
    return n;
}

/* =========================================================
   4 & 6. SINGLY / DOUBLY LINKED, SORTED -> Search O(n), Insert O(n)
   ========================================================= */
SNode* snode_insert_sorted(SNode *head, int key) {
    SNode *n = malloc(sizeof(SNode));
    n->key = key;
    if (!head || head->key >= key) { n->next = head; return n; }
    SNode *p = head;
    while (p->next && p->next->key < key) p = p->next;
    n->next = p->next; p->next = n;
    return head;
}
DNode* dnode_insert_sorted(DNode *head, int key) {
    DNode *n = malloc(sizeof(DNode));
    n->key = key; n->next = NULL; n->prev = NULL;
    if (!head || head->key >= key) {
        n->next = head; if (head) head->prev = n;
        return n;
    }
    DNode *p = head;
    while (p->next && p->next->key < key) p = p->next;
    n->next = p->next; if (p->next) p->next->prev = n;
    p->next = n; n->prev = p;
    return head;
}

void free_slist(SNode *h) { while (h) { SNode *t = h; h = h->next; free(t); } }
void free_dlist(DNode *h) { while (h) { DNode *t = h; h = h->next; free(t); } }

int main(void) {
    srand(42);
    int sizes[] = {500, 1000, 2000, 4000, 8000, 12000, 16000, 20000};
    int nsizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *out = fopen("results_q1.csv", "w");
    fprintf(out, "n,unsorted_arr_search,sorted_arr_search,sll_unsorted_search,sll_sorted_search,dll_unsorted_search,dll_sorted_search,"
                  "unsorted_arr_insert,sorted_arr_insert,sll_unsorted_insert,sll_sorted_insert,dll_unsorted_insert,dll_sorted_insert\n");

    for (int s = 0; s < nsizes; s++) {
        int n = sizes[s];
        int *ua = malloc((n + INSERT_TRIALS) * sizeof(int));
        int *sa = malloc((n + INSERT_TRIALS) * sizeof(int));

        for (int i = 0; i < n; i++) ua[i] = rand() % (n * 10);
        for (int i = 0; i < n; i++) sa[i] = i * 3;      /* already sorted, unique */

        SNode *sll_u = NULL, *sll_s = NULL;
        DNode *dll_u = NULL, *dll_s = NULL;
        for (int i = 0; i < n; i++) {
            sll_u = snode_insert_front(sll_u, ua[i]);
            sll_s = snode_insert_sorted(sll_s, sa[i]);
            dll_u = dnode_insert_front(dll_u, ua[i]);
            dll_s = dnode_insert_sorted(dll_s, sa[i]);
        }

        /* ---- SEARCH timing (search for random keys, mostly absent -> worst case) ---- */
        double t;
        double t_ua, t_sa, t_sllu, t_slls, t_dllu, t_dlls;

        t = now_us();
        for (int k = 0; k < SEARCH_TRIALS; k++) arr_search(ua, n, rand() % (n * 10) + n * 10);
        t_ua = (now_us() - t) / SEARCH_TRIALS;

        t = now_us();
        for (int k = 0; k < SEARCH_TRIALS; k++) arr_binary_search(sa, n, rand() % (n * 3) + n * 3);
        t_sa = (now_us() - t) / SEARCH_TRIALS;

        t = now_us();
        for (int k = 0; k < SEARCH_TRIALS; k++) snode_search(sll_u, rand() % (n * 10) + n * 10);
        t_sllu = (now_us() - t) / SEARCH_TRIALS;

        t = now_us();
        for (int k = 0; k < SEARCH_TRIALS; k++) snode_search(sll_s, rand() % (n * 3) + n * 3);
        t_slls = (now_us() - t) / SEARCH_TRIALS;

        t = now_us();
        for (int k = 0; k < SEARCH_TRIALS; k++) dnode_search(dll_u, rand() % (n * 10) + n * 10);
        t_dllu = (now_us() - t) / SEARCH_TRIALS;

        t = now_us();
        for (int k = 0; k < SEARCH_TRIALS; k++) dnode_search(dll_s, rand() % (n * 3) + n * 3);
        t_dlls = (now_us() - t) / SEARCH_TRIALS;

        /* ---- INSERT timing ---- */
        double i_ua, i_sa, i_sllu, i_slls, i_dllu, i_dlls;
        int cur_n;

        cur_n = n;
        t = now_us();
        for (int k = 0; k < INSERT_TRIALS; k++) cur_n = arr_insert_unsorted(ua, cur_n, rand());
        i_ua = (now_us() - t) / INSERT_TRIALS;

        cur_n = n;
        t = now_us();
        for (int k = 0; k < INSERT_TRIALS; k++) cur_n = arr_insert_sorted(sa, cur_n, rand() % (cur_n * 3 + 1));
        i_sa = (now_us() - t) / INSERT_TRIALS;

        t = now_us();
        for (int k = 0; k < INSERT_TRIALS; k++) sll_u = snode_insert_front(sll_u, rand());
        i_sllu = (now_us() - t) / INSERT_TRIALS;

        t = now_us();
        for (int k = 0; k < INSERT_TRIALS; k++) sll_s = snode_insert_sorted(sll_s, rand() % (n * 3));
        i_slls = (now_us() - t) / INSERT_TRIALS;

        t = now_us();
        for (int k = 0; k < INSERT_TRIALS; k++) dll_u = dnode_insert_front(dll_u, rand());
        i_dllu = (now_us() - t) / INSERT_TRIALS;

        t = now_us();
        for (int k = 0; k < INSERT_TRIALS; k++) dll_s = dnode_insert_sorted(dll_s, rand() % (n * 3));
        i_dlls = (now_us() - t) / INSERT_TRIALS;

        fprintf(out, "%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n",
                n, t_ua, t_sa, t_sllu, t_slls, t_dllu, t_dlls,
                i_ua, i_sa, i_sllu, i_slls, i_dllu, i_dlls);

        printf("n=%6d done\n", n);

        free(ua); free(sa);
        free_slist(sll_u); free_slist(sll_s);
        free_dlist(dll_u); free_dlist(dll_s);
    }
    fclose(out);
    printf("Wrote results_q1.csv\n");
    return 0;
}
