## Binary Search Tree 
This program stores course information for a sample course schedule in a binary search tree. Users can search for a course, or display all courses alphanumerically. 

<details> 
  <summary>Table of Contents</summary> 
  <ol> 
    <li><a href="#the-problem">The Problem</a></li> 
    <li><a href="#my-approach">My Approach</a></li> 
    <li><a href="#overcoming-roadblocks">Overcoming Roadblocks</a></li> 
    <li><a href="#expanding-my-approach">Expanding My Approach</a></li> 
    <li><a href="#evolving-my-approach">Evolving My Approach</a></li> 
  </ol> 
</details> 

### The Problem 
The goal of this course was to create the most efficient data structure for storing course data from a sample course list of a computer science program. The data structures that were examined were vectors, hash tables, and binary search trees. In order to complete the problem, the user needed to be able to search for an individual course, and print all courses in alphanumeric order. 

### My Approach 
My approach to this problem was to first create pseudocode and do a runtime analysis for the implementation of each data structure. Because one of the requirements was to sort the courses in alphanumeric order, a hash table was immediately eliminated from the list of data structures to use for this application. Binary search trees typically have a much faster search time than vectors, but if the data starts out sorted, or nearly sorted, then the runtime for search is very similar to a vector. I decided if the data was sorted, I would use a vector because they are easier to implement, and if it was unsorted, I would use a binary search tree because that is a much faster search. The data was unsorted, so I used a binary search tree as my chosen data structure. 

### Overcoming Roadblocks 
Any roadblocks I encountered I solved by looking at past programs, checking stack overflow, or doing a google search. I also found it useful to draw out the data structure on a whiteboard and use that to really break down what is happening during the programs run. This was particularly useful when examining the recursive functions. 

### Expanding My Approach 
This project expanded my approach development by making me much more comfortable with the more complicated to implement data structures such as hash tables, binary search trees, and linked lists. This allows me to be a much more versatile programmer, and can implement the best data structure, instead of the ones I'm comfortable with. 

### Evolving My Approach
Another main reason I chose to use a binary search tree was if the set of data was expanded to include every course in the school's catalogue, the runtime it takes to search for a course is going to be dramatically faster than using a vector. I designed this program with scalability in mind so that it would be adaptable to a larger implementation. Learning exactly how binary search trees work also enabled me to write code that was easily maintainable and readable for any future developers working on this code. 
