# Singly linked list

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

## **List methods and their complexities**

- ### ***push_back(element)***
  Add element to the end of the list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***push_front(element)***
  Add element to the beginning of the list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***pop_back()***
  Remove element from the end of the list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***pop_front()***
  Remove element from beginning of the list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***is_empty()***
    Return true if the list is empty.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***size()***
    Return size of the list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***remove(element_value)***
    Remove element from the list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***find(element_value)***
    Find the first element with element_value in the list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***clear()***
    Clear memory of the list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***copy(list)***
    Copy list to the currently list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***merge(list)***
    Merge list to the currently list (like push_back(another_list)).

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(n)$       | $O(n)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |

- ### ***merge(rvalue_list)***
    Merge rvalue_list to the currently list.

    | Complexities         | Best case | Average case | Worst case |
    | -------------------- | --------- | ------------ | ---------- |
    | **Time complexity**  | $O(1)$    | $O(1)$       | $O(1)$     |
    | **Space complexity** | $O(1)$    | $O(1)$       | $O(1)$     |
