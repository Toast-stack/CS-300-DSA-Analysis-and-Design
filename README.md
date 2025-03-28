# CS-300: Data Structures and Algorithms - Analysis and Design

## Project Overview

This project focuses on designing a program that organizes college courses **alphanumerically**, **manages prerequisites**, and **allows students to generate a sample academic schedule**. The key functionalities include:

- Sorting courses in **alphanumeric order**.
- Managing **course prerequisites**.
- Generating a **student course schedule**.
- Allowing users to **select a course and view its prerequisites**.

---

## Problem Statement

The challenge was to develop a system that could efficiently **sort and display courses** while ensuring that all **prerequisites were accounted for**. The program needed to provide an intuitive way for students to understand their academic pathways.

---

## Approach and Solution

### Initial Strategy

Initially, I implemented a **hash table** to store course information. While hash tables allow for fast data retrieval, they lack an **intrinsic sorting mechanism**, which is essential for **maintaining an ordered list of courses**.

### Challenges Faced

A major issue with the hash table was its inability to maintain a **sorted order** for course listings. I initially attempted to **pre-sort the data manually**, but this solution was inefficient and **not scalable**.

### Revised Strategy: Implementing a Binary Search Tree (BST)

To resolve the ordering issue, I transitioned to using a **Binary Search Tree (BST)**.

**Why a BST?**

- Allows efficient **insertion and retrieval** of data.
- Supports **in-order traversal**, ensuring courses are **sorted automatically**.
- Scales well with **large datasets** compared to manual sorting.

In the BST implementation:

- Each **node** represents a course.
- The **left subtree** contains courses that come **before** the parent node.
- The **right subtree** contains courses that come **after** the parent node.

This allowed for **efficient searching, inserting, and maintaining sorted course data** dynamically.

---

## Overcoming Challenges

Switching from a hash table to a BST required a major shift in approach. However, I overcame this by:

- **Researching specific issues** instead of looking up entire solutions, ensuring I fully understood my challenges.
- **Consulting my professor** to clarify my approach and optimize my implementation.
- **Referencing previous assignments** to apply what I had already learned effectively.

---

## Impact on Software Development

This project reinforced the importance of **choosing the right data structures** for specific problems. The transition from a hash table to a BST highlighted key concepts:

- **Data Organization:** Recognizing how different structures influence data storage and retrieval.
- **Algorithm Efficiency:** Understanding the trade-offs between various data structures in terms of performance.
- **Scalability:** Ensuring that the program functions well even with **large datasets**.

---

## Improving Code Maintainability and Readability

This project helped me refine my coding practices by focusing on:

- **Structured Data Storage:** Using a **BST** to efficiently organize and retrieve information.
- **Readable and Maintainable Code:** Writing clean, well-documented, and structured code for **better debugging and collaboration**.
- **Code Scalability:** Implementing a design that allows **future modifications and improvements**.

---

## Conclusion

Through this project, I gained **valuable experience in selecting and implementing data structures** to optimize efficiency. The process of problem-solving, debugging, and refining my approach helped me build a deeper understanding of **software design and algorithm optimization**.

This experience will be **invaluable in future projects**, reinforcing the importance of well-structured, scalable, and maintainable code.
