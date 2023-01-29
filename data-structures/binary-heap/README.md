# Binary heap (Max-heap)

## **CMake** **Presets**:
- ### debug
- ### release
- ### test

<br>

## **Generate**:
### *cmake --preset <PRESET_NAME>*
<br>

## **Build**:
### *cmake --build --preset <PRESET_NAME>*

<br>
<hr>

## **Max-heap methods and their complexities**

- ### ***insert(key, value)***
  Add element to the heap. Returns void.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(log(n))$  | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***add_list(const vector of pairs <key, value>)***
  Add elements from vector to the heap. Returns void.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(nlog(n))$ | $O(n^2)$   |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***max()***
   Returns max element - <key, value> (Root - MaxHeap).

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***increase_key(key)***
  Increases key of element. Returns void.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(log(n))$  | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***extract_max()***
    Delete maximal element from heap. Returns pair <key, value> - max.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(log(n))$  | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |
