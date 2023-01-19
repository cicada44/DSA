# Stack inherited from list

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

## **Stack methods and their complexities**

- ### ***push(element)***
  Add element to stack.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***pop()***
  Remove element from stack.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***is_empty()***
    Return true if the stack is empty.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***size()***
    Return size of the stack.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***find(element_value)***
    Find the first element with element_value in the stack.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |
