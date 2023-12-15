# STL Libraries Implementation

This repository contains C++ implementations of fundamental data structures, including Deque, Priority Queue, Unordered Map, and Ordered Map. Each data structure is designed with specific operations and follows standard conventions.

## Deque

### Description

Deque is a dynamic array with the ability to resize itself automatically when an element is inserted. It supports insertion and deletion from both ends in amortized constant time.

### Operations

1. `deque()` - Initialize an empty deque.
2. `deque(n)` - Initialize a deque of length n with default values.
3. `deque(n, x)` - Initialize a deque of length n with all values as x.
4. `push_back(x)` - Append data x at the end.
5. `pop_back()` - Erase data at the end.
6. `push_front(x)` - Append data x at the beginning.
7. `pop_front()` - Erase an element from the beginning.
8. `front()` - Return the first element in the deque.
9. `back()` - Return the last element in the deque.
10. `operator[]` - Return the nth element of the deque.
11. `empty()` - Check if the deque is empty.
12. `size()` - Return the current size of the deque.
13. `resize(n)` - Change the size dynamically to new size n.
14. `resize(n, d)` - Change the size dynamically to new size n with value d.
15. `reserve(n)` - Change the capacity of deque to n.
16. `shrink_to_fit()` - Reduce the capacity of the deque to the current size.
17. `clear()` - Remove all elements from the deque.
18. `capacity()` - Return the current capacity of the deque.

## Priority Queue

### Description

Priority Queue is a data structure that maintains a collection of elements with priorities. Elements are stored in a way that allows the retrieval of the element with the highest priority quickly.

### Operations

1. `priority_queue()` - Initialize an empty priority queue.
2. `size()` - Return the current size of the priority queue.
3. `push(el)` - Insert an element el in the priority queue.
4. `top()` - Return the top element in the priority queue.
5. `pop()` - Remove the top element of the priority queue.
6. `empty()` - Check if the priority queue is empty.

## Unordered Map

### Description

Unordered Map is an associated container that stores elements formed by the combination of a key value and a mapped value.

### Operations

1. `insert(key, value)` - Insert value in the map with the given key.
2. `erase(key)` - Delete key and its value from the map.
3. `contains(key)` - Check if the key exists in the map.
4. `operator[](key)` - Insert default value with key if not present, return value by reference.
5. `clear()` - Clear the map.
6. `size()` - Return the size of the map.
7. `empty()` - Check if the map is empty.
8. `keys()` - Return a vector of keys.

## Ordered Map

### Description

Ordered Map is a sorted associative container that contains key-value pairs with unique keys. Keys are sorted by using the comparison function std::less<key>.

### Operations

1. `empty()` - Check if the map is empty.
2. `size()` - Return the size of the map.
3. `contains(key)` - Check if key is present in the map.
4. `insert(key, value)` - Insert value with key in the map.
5. `erase(key)` - Delete key and its value from the map.
6. `operator[](key)` - Insert default value with key if not present, return value by reference.
7. `clear()` - Clear the map.
8. `keys()` - Return a vector of keys.
9. `lower_bound(key)` - Return true and the first key >= 'key', or false and default value.
10. `upper_bound(key)` - Return true and the first key > 'key', or false and default value.