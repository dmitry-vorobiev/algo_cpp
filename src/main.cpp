#include <iostream>

#include "sorting/insertion_sort.h"
#include "sorting/merge_sort.h"
#include "sorting/quick_sort.h"

#include "./exponentiation.h"

#include "./data_structures/heap.h"
#include "./data_structures/avl_tree.h"


int main(int argc, char** argv)
{
	bool is_ok = test_avl_tree();
	std::cout << "test_avl_tree: " << is_ok << std::endl;

	// test_pow();
	// test_heap();

	// std::cout 
	// 	<< "test_insertion_sort: " << test_insertion_sort() << std::endl 
	// 	<< "test_merge_sort: " << test_merge_sort() << std::endl
	// 	<< "test_quick_sort: " << test_quick_sort() << std::endl;
	
	return 0;
}
