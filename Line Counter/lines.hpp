/*
One of the ways that is often used to measure the amount of work you've done in project courses is
to count the lines of code you've written. Although it's debatable whether this is a good metric,
it certainly is a good way to exercise your C++ knowledge.

In namespace HLP3, declare a function lines in lines.hpp and define the function in lines.cpp.
You cannot use the I/O facilities from the C standard library. Instead, you must use the C++-only
I/O facilities from the C++ standard library. Any references to FILE*, <cstdio>, fopen, fread,
fscanf, fgets, ... will not compile!!!

Function lines takes an array of (text) file names and calculates the total number of lines in these files.
To keep this exercise as simple as possible, assume a line in a text file is defined as a sequence of
characters terminated by newline character. Function lines takes an array as parameter with each element
of the array pointing to a C-style string that specifies the name of a text file. The last element of the
array is a null pointer signifying the end of the array. The function must return an int value specifying
the total number of lines in the list of files specified by the function's parameter.

NOTE: Submissions using functions from the C standard library will be considered in violation of the Academic Integrity Policy.
Just don't do it!!!
*/