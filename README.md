# Project1_DSA
Implement Lempel-Ziv-Welch (LZW) algorithm:

                    ITCS 6114/8114: Algorithms and Data Structures
					      Programming Project 1: LZW Compression
					            Md Rajib, mrajib@uncc.edu

Program Design: 
To implement Lempel-Ziv-Welch (LZW) algorithm, the overall program is divided into three parts. These are encoder, 
decoder and an auxiliary helper module that is shared by both the encoder and decoder. As the name
suggests, functions of encoder and decoder are encoding the input text file to a compressed file in UTF-16BE
format and vice versa. The helper module faciliates with code table initialization, insertion, searching etc. Due
to the nature of code table creation, insertion takes constant time. However as the table grows,
searching for encoded table takes larger and larger amount of running time.

Data structure design:
For data structure, vectors were used from C++ standarad template library. Thus the size of table can be dynamically adjusted.

Breakdown of files:
There are two program files- "encoder.cpp" and "decoder.cpp" to implement the encode-decode algorithms respectively.
A header file "lzw.h" used to provide auxialiary functions as mentioned above.


Programming language and compiler: 
C++ language is used with 98 standard compatibility in mind.  g++ compiler version was 4.8.4. 


Problems:
The algorithm doesnot seem as fast as expected. Some further optimizations might be necessary. 
Though the algorithm itself was simple, extensive file manipulaions made it more challenging. 

----------------------------------------------------------
To compile the program use the following commands (in linux machines):

g++ encoder.cpp lzw.h -o encoder
g++ decoder.cpp lzw.h -o decoder

To encode a file, e.g., 'input.txt' with 12 bit encoding:

./encoder input.txt 12

To decode the generated file from above procedure, use

./decoder input.lzw 12









