# Cache Behavior Lab

## Overview
This assignment demonstrates how memory access patterns affect performance. You'll implement two matrix traversal functions that perform identical computation but access memory differently, then measure and explain the performance difference.

## Files
- `cache_lab.c` - Template file with TODO sections to complete
- `README.md` - This file

## What to Complete
1. `traverse_row_major()` - Sum all elements visiting row-by-row
2. `traverse_column_major()` - Sum all elements visiting column-by-column

## Compiling and Running

**Basic compilation:**
```bash
gcc cache_lab.c -o cache_lab
./cache_lab
```

**Optimization level comparison:**
```bash
gcc -O0 cache_lab.c -o cache_O0 && ./cache_O0
gcc -O2 cache_lab.c -o cache_O2 && ./cache_O2
gcc -O3 cache_lab.c -o cache_O3 && ./cache_O3
```

## Expected Output
Your program should display execution times for both traversal methods across four matrix sizes (1000, 2000, 4000, 8000). A correct implementation will show column-major traversal running significantly slower than row-major.