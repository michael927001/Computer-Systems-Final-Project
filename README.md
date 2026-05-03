
# Computer Systems Final Project

## Project Overview

This project compares two C implementations of a simulated log analyzer. The program processes server log entries, counts ERROR messages, identifies duplicate ERROR messages, and reports execution time.

The purpose of the project is to demonstrate how data structure choices and memory layout affect performance. The baseline implementation uses a linked list, while the optimized implementation uses a contiguous array.

## Files

- `baseline.c` - Baseline linked-list implementation
- `optimized.c` - Optimized array-based implementation
- `README.md` - Project documentation

## Baseline Implementation

The baseline version stores each log entry in a linked list node. Each node is allocated separately using `malloc()`.

This approach is slower because:
- It requires many separate memory allocations
- Nodes may be scattered throughout memory
- Pointer chasing reduces cache efficiency
- Sequential CPU prefetching is less effective

## Optimized Implementation

The optimized version stores all log records in one contiguous array.

This improves performance because:
- It uses one large allocation instead of many small allocations
- Log records are stored next to each other in memory
- Cache locality is improved
- Sequential memory access allows better CPU prefetching
- Less time is spent on allocation overhead

## Compilation Instructions

To compile the baseline implementation:

```bash
gcc -Wall -O2 baseline.c -o baseline