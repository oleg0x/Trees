#!/bin/bash

rm binary_search_tree.o tests.o main.o zzz
clear

g++ binary_search_tree.cpp -std=c++20 -Wall -Wextra -c -o binary_search_tree.o
g++ tests.cpp -std=c++20 -Wall -Wextra -c -o tests.o
g++ test_structs.cpp -std=c++20 -Wall -Wextra -c -o test_structs.o
g++ main.cpp -std=c++20 -Wall -Wextra -c -o main.o
g++ binary_search_tree.o tests.o test_structs.o main.o -o zzz

#clang++ binary_search_tree.cpp -std=c++20 -Wall -Wextra -c -o binary_search_tree.o
#clang++ tests.cpp -std=c++20 -Wall -Wextra -c -o tests.o
#clang++ test_structs.cpp -std=c++20 -Wall -Wextra -c -o test_structs.o
#clang++ main.cpp -std=c++20 -Wall -Wextra -c -o main.o
#clang++ binary_search_tree.o tests.o test_structs.o main.o -o zzz

./zzz
