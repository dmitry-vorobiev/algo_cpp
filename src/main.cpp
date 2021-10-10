#include <iostream>

#include "sorting/insertion_sort.h"
#include "sorting/merge_sort.h"


int main(int argc, char** argv)
{
	std::cout << "test_insertion_sort: " << test_insertion_sort() << std::endl;

	test_merge();
	return 0;
}
