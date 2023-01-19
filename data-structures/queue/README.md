# Queue inherited from list

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

## **Queue methods and their complexities**

- ### ***push(element)***
  Add element to the beginning of the queue.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***pop***
  Remove element from the end of the queue.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***is_empty()***
    Return true if the queue is empty.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***size()***
    Return size of the queue.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***find(element_value)***
    Find the first element with element_value in the queue.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

