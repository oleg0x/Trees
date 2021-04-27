#!/bin/bash

rm binary_search_tree.o red-black_tree.o test_structs.o tests_bst.o tests_rbt.o main.o zzz
clear

g++ binary_search_tree.cpp -std=c++20 -Wall -Wextra -c -o binary_search_tree.o
g++ red-black_tree.cpp -std=c++20 -Wall -Wextra -c -o red-black_tree.o
g++ test_structs.cpp -std=c++20 -Wall -Wextra -c -o test_structs.o
g++ tests_bst.cpp -std=c++20 -Wall -Wextra -c -o tests_bst.o
g++ tests_rbt.cpp -std=c++20 -Wall -Wextra -c -o tests_rbt.o
g++ main.cpp -std=c++20 -Wall -Wextra -c -o main.o
g++ binary_search_tree.o red-black_tree.o test_structs.o tests_bst.o tests_rbt.o main.o -o zzz

#clang++ binary_search_tree.cpp -std=c++20 -Wall -Wextra -c -o binary_search_tree.o
#clang++ red-black_tree.cpp -std=c++20 -Wall -Wextra -c -o red-black_tree.o
#clang++ test_structs.cpp -std=c++20 -Wall -Wextra -c -o test_structs.o
#clang++ tests_bst.cpp -std=c++20 -Wall -Wextra -c -o tests_bst.o
#clang++ tests_rbt.cpp -std=c++20 -Wall -Wextra -c -o tests_rbt.o
#clang++ main.cpp -std=c++20 -Wall -Wextra -c -o main.o
#clang++ binary_search_tree.o red-black_tree.o test_structs.o tests_bst.o tests_rbt.o main.o -o zzz

./zzz
