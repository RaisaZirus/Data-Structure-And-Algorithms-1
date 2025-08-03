This project implements a Stack Abstract Data Type (ADT) in C++, using two different underlying data structures: 
an Array-based stack (ArrayStack) and a Linked List-based stack (ListStack). 
The assignment tests the fundamental operations of a stack, including push, pop, top, size, empty, clear, and print.

1. stack.h

    This file defines the abstract base class Stack, which specifies the interface for stack operations.
    It includes pure virtual methods for push, pop, top, size, empty, clear, and print, which must be 
    implemented by any concrete class (e.g., ArrayStack and ListStack).

2. arraystack.cpp

    This file contains the implementation of the ArrayStack class, which uses a dynamically
    allocated array to store elements. The array automatically resizes when it becomes full (doubling its capacity)
    or shrinks when less than 25% of the capacity is used.

    It implements the core stack operations like push, pop, top, and others with dynamic memory management.

3. liststack.cpp

    This file contains the implementation of the ListStack class, which uses a singly linked list to store elements.
    Each node in the list represents one element of the stack.

    It implements the stack operations using the linked list structure, where new elements are pushed
    to the front of the list, and popped elements are removed from the front as well.

4. test.cpp

    This file contains the test framework used to validate the behavior of both the ArrayStack and ListStack
    implementations. It includes test functions for each stack operation (like push, pop, top, size, etc.).

    The test cases also include edge cases (e.g., popping from an empty stack) and performance tests
    (e.g., stress testing with large numbers of operations).