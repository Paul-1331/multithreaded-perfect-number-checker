# Multithreaded Perfect Number Checker

## Description

This program determines whether a given number **N** is a *perfect number* using **P threads**.
A perfect number is a number whose sum of proper divisors (excluding itself) is equal to the number.

Examples:

* 6 → 1 + 2 + 3 = 6 
* 28 → 1 + 2 + 4 + 7 + 14 = 28 

The program uses **POSIX threads (pthreads)** and **mutex synchronization** to safely compute the sum of factors in parallel.

---

## Requirements

* GCC compiler
* POSIX Threads (pthread library)
* Math library (libm)

---

## Compilation

```bash
gcc B240266CS_A2.c -o a2 -lpthread -lm
```

---

## Execution

```bash
./a2 <N> <P>
```

### Parameters:

* `N` → Number to check
* `P` → Number of threads

---

## Example Runs

```bash
./a2 6 2
Output: 6 is a Perfect Number

./a2 28 4
Output: 28 is a Perfect Number

./a2 10 3
Output: 10 is NOT a Perfect Number
```

---

## Approach

1. The program reads **N** and **P** from command line.
2. The search range is reduced to **1 → √N** for optimization.
3. The range is divided among **P threads**.
4. Each thread:

   * Checks if a number divides N
   * Adds valid factors to a shared variable `sum`
5. A **mutex lock** ensures safe updates to `sum`.
6. After all threads finish:

   * If `sum == N` → Perfect number
   * Else → Not perfect

---

## Synchronization

* A shared variable `sum` is updated by multiple threads.
* To prevent **race conditions**, a mutex (`pthread_mutex_t`) is used:

  * `pthread_mutex_lock()`
  * `pthread_mutex_unlock()`

---

## Optimization

* Instead of checking all numbers up to N, only values up to **√N** are checked.
* For every divisor `i`, the corresponding divisor `N/i` is also considered.

---

## Edge Cases Handled

* `N <= 1` → Not a perfect number
* `P <= 0` → Invalid input
* `P > √N` → Adjusted to avoid idle threads

---

## File Structure

```
B240266CS_A2.c   → Source code
B240266CS.pdf    → Design Document
README.md        → Execution Steps
B240266CS_1.png  → Successful cases for Perfect Numbers
B240266CS_2.png  → Successful cases for Non Perfect Numbers
B240266CS_3.png  → Failure cases
```

---

## Author

Paul Biju Cheeramvelil
