```
Concurrent Merge Sort -> concurrent_merge_sort.c
Regular Merge Sort -> regular_mergesort.c
Test file -> test.c
Input File -> Input.txt
```

Comparison between regular merge sort and concurrent merge sort.

For array size = 10000000
-> Concurrent merge sort takes = 11.117s.
-> Regular merge sort takes = 12.063s.

For array size = 1000000
-> Both concurrent and regular merge sort takes approximately same time = 1.21s

For less array size regular merge sort is fast.

Reason:
-> Forking has overhead because a lot of cache miss because two process of left and right child are working parallely.
-> Forking has overhead. Because new process, new memory space is created,etc.
-> But for larger array size. There is a benefit of parallel process which helps finishing faster.
-> Hence for big inputs concurrent merge sort is beneficial.
