#pragma once

inline int factorial(int x) {
    return (x == 1 ? x : x * factorial(x - 1));
}

inline bool next_set(int* a, int n) {
    int j = n - 2;
    while (j != -1 && a[j] >= a[j + 1])
        j--;
    if (j == -1)
        return false;
    int k = n - 1;
    while (a[j] >= a[k])
        k--;
    auto swap = [](int *a, int i, int j) {
        int s = a[i];
        a[i] = a[j];
        a[j] = s;
    };
    swap(a, j, k);
    int l = j + 1;
    int r = n - 1;
    while (l < r)
        swap(a, l++, r--);
    return true;
}
