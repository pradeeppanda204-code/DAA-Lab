import pandas as pd
import matplotlib.pyplot as plt

# ---------- Q1 ----------
df1 = pd.read_csv("results_q1.csv")
fig, axes = plt.subplots(1, 2, figsize=(13, 5))

axes[0].plot(df1.n, df1.unsorted_arr_search, 'o-', label='Unsorted array O(n)')
axes[0].plot(df1.n, df1.sorted_arr_search, 's-', label='Sorted array O(log n)')
axes[0].plot(df1.n, df1.sll_unsorted_search, '^-', label='SLL unsorted O(n)')
axes[0].plot(df1.n, df1.sll_sorted_search, 'v-', label='SLL sorted O(n)')
axes[0].plot(df1.n, df1.dll_unsorted_search, 'd-', label='DLL unsorted O(n)')
axes[0].plot(df1.n, df1.dll_sorted_search, 'x-', label='DLL sorted O(n)')
axes[0].set_title("Q1: Search time vs n")
axes[0].set_xlabel("n"); axes[0].set_ylabel("time (µs)"); axes[0].legend(fontsize=8)

axes[1].plot(df1.n, df1.unsorted_arr_insert, 'o-', label='Unsorted array O(1)')
axes[1].plot(df1.n, df1.sorted_arr_insert, 's-', label='Sorted array O(n)')
axes[1].plot(df1.n, df1.sll_unsorted_insert, '^-', label='SLL unsorted O(1)')
axes[1].plot(df1.n, df1.sll_sorted_insert, 'v-', label='SLL sorted O(n)')
axes[1].plot(df1.n, df1.dll_unsorted_insert, 'd-', label='DLL unsorted O(1)')
axes[1].plot(df1.n, df1.dll_sorted_insert, 'x-', label='DLL sorted O(n)')
axes[1].set_title("Q1: Insert time vs n")
axes[1].set_xlabel("n"); axes[1].set_ylabel("time (µs)"); axes[1].legend(fontsize=8)

plt.tight_layout()
plt.savefig("q1_plot.png", dpi=130)
plt.close()

# ---------- Q2 ----------
df2 = pd.read_csv("results_q2.csv")
plt.figure(figsize=(7, 5))
plt.plot(df2.n, df2.mergesort2_us, 'o-', label='Merge sort (2-way, halves)')
plt.plot(df2.n, df2.mergesort3_us, 's-', label='Modified merge sort (3-way, thirds)')
plt.title("Q2: Merge sort vs 3-way merge sort")
plt.xlabel("n"); plt.ylabel("time (µs)")
plt.legend()
plt.tight_layout()
plt.savefig("q2_plot.png", dpi=130)
plt.close()

# ---------- Q3 vary k ----------
df3k = pd.read_csv("results_q3_vary_k.csv")
plt.figure(figsize=(7, 5))
plt.plot(df3k.k, df3k.sequential_us, 'o-', label='Method 1: sequential O(k^2 n)')
plt.plot(df3k.k, df3k.pairwise_us, 's-', label='Method 2: pairwise O(kn log k)')
plt.title("Q3: Merging k sorted arrays (n=200 fixed) vs k")
plt.xlabel("k"); plt.ylabel("time (µs)")
plt.legend()
plt.tight_layout()
plt.savefig("q3_vary_k_plot.png", dpi=130)
plt.close()

# ---------- Q3 vary n ----------
df3n = pd.read_csv("results_q3_vary_n.csv")
plt.figure(figsize=(7, 5))
plt.plot(df3n.n, df3n.sequential_us, 'o-', label='Method 1: sequential')
plt.plot(df3n.n, df3n.pairwise_us, 's-', label='Method 2: pairwise')
plt.title("Q3: Merging k sorted arrays (k=32 fixed) vs n")
plt.xlabel("n"); plt.ylabel("time (µs)")
plt.legend()
plt.tight_layout()
plt.savefig("q3_vary_n_plot.png", dpi=130)
plt.close()

print("All plots saved.")
