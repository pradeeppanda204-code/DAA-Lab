# DAA Lab-02 — Solutions

## Question 1: Dictionary Operations

Worst-case asymptotic running times (n = number of elements currently in D).
Assumptions: for the linked-list structures a **head pointer** is kept; for the
**sorted doubly linked list** a **tail pointer** is also kept (a common, reasonable
convention — noted in the C code / plots below).

| Structure | Search | Insert | Delete* | Max | Min | Predecessor | Successor |
|---|---|---|---|---|---|---|---|
| Unsorted array | O(n) | O(1) | O(1)** | O(n) | O(n) | O(n) | O(n) |
| Sorted array | O(log n) | O(n) | O(n) | O(1) | O(1) | O(1) | O(1) |
| Singly linked, unsorted | O(n) | O(1) | O(n) | O(n) | O(n) | O(n) | O(n) |
| Singly linked, sorted | O(n) | O(n) | O(n) | O(n) | O(1) | O(n) | O(1) |
| Doubly linked, unsorted | O(n) | O(1) | O(1)*** | O(n) | O(n) | O(n) | O(n) |
| Doubly linked, sorted | O(n) | O(n) | O(1)*** | O(1) | O(1) | O(1) | O(1) |

\* "Delete(D, x)" is given a **pointer** to the node/element, not a key — so the
cost is the cost of unlinking/removing at that known location, not of finding it.
\** Unsorted array delete is O(1) if you overwrite the removed slot with the
last element (order doesn't matter since the array is unsorted); O(n) if
relative order must be preserved via shifting.
\*** Doubly linked delete is O(1) because both neighbors are directly
reachable from the pointer, unlike a singly linked list where the
predecessor must be found by scanning (O(n)) before it can be unlinked.

**Why these hold, briefly:**
- *Arrays* support O(1) random access, so binary search works only when
  sorted (O(log n) search), but any insert/delete that must preserve sorted
  order requires shifting up to n elements (O(n)).
- *Linked lists* have no random access, so search is always O(n) regardless
  of sort order. Sorting only helps operations that can stop early (Min,
  Successor with sorted singly-linked; Min/Max/Predecessor/Successor all
  O(1) with sorted doubly-linked + head/tail pointers).
- *Doubly* linked lists beat *singly* linked lists only on **Delete** (and on
  Predecessor for the sorted case), because `prev` pointers let you unlink or
  step backward in O(1) without a scan.

**Empirical validation** (`q1_dictionary.c`): builds each structure for
n = 500 … 20000, times average Search and Insert cost, and plots the curves.
The measured curves match theory cleanly: unsorted-array/SLL/DLL search costs
grow linearly and coincide, sorted-array search stays essentially flat
(logarithmic — barely visible next to O(n) curves), unsorted-structure insert
stays flat (O(1)), and sorted-structure insert grows linearly (O(n)).

![Q1 plot](q1_plot.png)

---

## Question 2: Merge sort vs. modified (3-way) merge sort

**Claim:** dividing into thirds instead of halves does **not** change the
asymptotic order of growth — it is still **Θ(n log n)**.

**Reasoning (recurrence):**
Splitting into 3 equal parts, recursively sorting each, then combining with a
3-way merge (which is still linear time — a 3-way merge does O(1) work per
output element, just comparing 3 candidates instead of 2, using k−1
comparisons per step for a k-way merge) gives:

T(n) = 3T(n/3) + O(n)

By the Master Theorem, a = 3, b = 3, so n^(log_b a) = n^(log_3 3) = n^1 = n,
which matches the O(n) merge cost exactly (case 2) — giving

**T(n) = Θ(n log n)**, same as ordinary 2-way merge sort (a = 2, b = 2, same
case-2 match: T(n) = 2T(n/2) + O(n) = Θ(n log n)).

Only the **constant factor** differs: 3-way merge sort does log₃n ≈ 0.63·log₂n
levels of recursion (fewer levels since branching is wider), but each level's
merge does more comparisons per element (up to 2 comparisons to pick the
minimum of 3, vs. 1 for 2-way). In practice these effects partly cancel; the
measured runtime is close to standard merge sort, sometimes slightly faster
due to fewer recursion levels and better cache behavior on the smaller thirds.

**Empirical validation** (`q2_mergesort.c`): both algorithms timed on random
arrays, n = 1,000 … 640,000, averaged over 5 runs.

![Q2 plot](q2_plot.png)

Both curves show the classic n log n shape (near-linear on a log-x view,
slightly super-linear on this linear-x plot) and track each other closely —
confirming they share the same asymptotic class, exactly as the recurrence
predicts.

---

## Question 3: Merging k sorted arrays of n elements each

### (a) Method 1 — Sequential merging

Merge array 1 and 2 (cost O(n + n) = O(2n)), merge that result (size 2n) with
array 3 (cost O(2n + n) = O(3n)), then with array 4 (cost O(4n)), … up to
merging in the k-th array (cost O((k−1)n)).

Total: T(n,k) = O(n) · Σ_{i=1}^{k-1} (i+1) = O(n · k²)

**Worst-case running time: Θ(k² n)**

### (b) Method 2 — Pairwise (tournament) merging

Round 1: pair up the k arrays into k/2 merges, each merging two arrays of
size n → cost O(n) each, k/2 merges → O(kn) total for the round, producing
k/2 arrays of size 2n.
Round 2: k/4 merges of size-2n arrays → O(kn) again.
…this repeats for **log₂k** rounds, each costing O(kn), since total elements
merged per round is always kn regardless of how many arrays remain.

Total: T(n,k) = O(kn · log k)

**Worst-case running time: Θ(kn log k)**

Method 2 is asymptotically much better for large k: k²n grows quadratically
in k, while kn log k grows only slightly faster than linearly in k.

**Empirical validation** (`q3_merge_k_arrays.c`): two experiments —

- *Fixed n = 200, growing k* (2 → 256): shows the sequential method's time
  pulling sharply upward (quadratic) away from the pairwise method (k log k),
  confirming the theoretical gap opens up as k grows.

  ![Q3 vary k](q3_vary_k_plot.png)

- *Fixed k = 32, growing n* (100 → 12,800): with k held constant, both
  methods are linear in n (Θ(k²n) and Θ(kn log k) both reduce to Θ(n) when k
  is fixed), so the two lines stay roughly parallel/close, as expected — the
  divergence between the methods is a function of k, not n.

  ![Q3 vary n](q3_vary_n_plot.png)

---

## Files

| File | Purpose |
|---|---|
| `q1_dictionary.c` | Implements & times Search/Insert on all 6 dictionary structures |
| `q2_mergesort.c` | Implements & times 2-way merge sort vs. 3-way (thirds) merge sort |
| `q3_merge_k_arrays.c` | Implements & times sequential vs. pairwise merging of k sorted arrays |
| `plot_all.py` | Reads the CSVs produced by the programs above and generates the plots |
| `results_q1.csv`, `results_q2.csv`, `results_q3_vary_k.csv`, `results_q3_vary_n.csv` | Raw timing data |
| `q1_plot.png`, `q2_plot.png`, `q3_vary_k_plot.png`, `q3_vary_n_plot.png` | Generated plots |

To reproduce: `gcc -O2 -o q1_dictionary q1_dictionary.c && ./q1_dictionary`
(similarly for q2 and q3), then `python3 plot_all.py`.
