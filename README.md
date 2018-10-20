# Selection without replacement

[This algorithm](cardchoose.md) selects k integers 0 <= x < n at random
and returns them in sorted order. It takes O(k log k) time and needs no
auxiliary data structures, just the list it will return things in. I've
implemented it in Python and C++, and compared it to some other options.

Any algorithm can be turned into one with a "sorted" order guarantee
with an O(k log k) sort, or a "random" order guarantee with an O(k)
Fisher-Yates shuffle.

Order guarantee | Time | Data structures | Algorithm | Python | C++
----|----|----|----|----|----
Sorted | k log k | none | this algorithm | [Python](python/algorithms/cardchoose.py) | [C++](cpp/cardchoose.cpp)
Random | k  | Set | rejection sampling | [Python](python/algorithms/rejectionsample.py) | [C++](cpp/rejectionsample.cpp)
Random | k^2  | none | quadratic rejection sampling |  | [C++](cpp/quadraticreject.cpp)
Sorted | n | none | iterative random choosing | [Python](python/algorithms/iterativechoose.py) | [C++](cpp/iterativechoose.cpp)
Random | n | n-sized list | Python-style Fisher-Yates | [Python](python/algorithms/fisheryates.py) | [C++](cpp/fisheryates.cpp)
Random | k | Dictionary | Selby Fisher-Yates | [Python](python/algorithms/algorithms/selby_fy.py) | [C++](cpp/selby_fy.cpp)
none | k | Set | Floyd's F2 | [Python](python/algorithms/floydf2.py) | [C++](cpp/floydf2.cpp)

On my machine, in C++, Fisher-Yates is the only algorithm using an auxiliary
data  structure that ever does better than one which doesn't; see [these
preliminary results](cpp/results).

This is not an officially supported Google product.
