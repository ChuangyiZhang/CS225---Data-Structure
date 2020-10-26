#include <iostream>
#include <algorithm>
#include "tree.h"

template <class T>
void print(std::vector<T> v) {
	std::cout << "<";
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << v[i] << (i != v.size()-1 ? ", " : "");
	}
	std::cout << ">" << std::endl;
}

int main() {
	Tree<int> t;
	t.setRoot(
		new Tree<int>::Node(1,
			new Tree<int>::Node(3,
				NULL,
				new Tree<int>::Node(2)),
			new Tree<int>::Node(5,
				new Tree<int>::Node(11),
				new Tree<int>::Node(4,
					new Tree<int>::Node(9),
					new Tree<int>::Node(7)))));
	
	std::vector<int> expected = { 3, 1, 11, 5, 9, 7 };
	std::vector<int> actual;
	for ( int i : t ) actual.push_back(i);
	std::cout << "Expected: "; print(expected);
	std::cout << "Actual  : "; print(actual);
}