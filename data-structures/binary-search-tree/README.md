# Binary search tree

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

## **BST methods and their complexities**

- ### ***insert(key, value)***
  Add element to the BST. Returns void.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(log(n))$  | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***insert_list(const vector of pairs <key, value>)***
  Add vector with elements to the BST. Returns void.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(nlog(n))$ | $O(n^2)$   |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***find(key)***
   Searches element with key in the BST. Returns pair <key, value>.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(log(n))$  | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***remove(key)***
  Remove element from BST. Returns void.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(log(n))$  | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***min()***
    Searches minimal element in the BST. Returns pair <key, value>.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(log(n))$  | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***max()***
    Searches maximal element in the BST. Returns pair <key, value>.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(log(n))$  | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***delete_dfs()***
    Delete tree with DFS order. Returns void.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***print_preorder(ostream)***
    Display tree with preorder to ostream. Returns void.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |
