#include "MinHeap.h"
#include <math.h>
using namespace std; 


vector<int> lastLevel(MinHeap & heap)
{
        // Your code here

	vector<int> v;
	if(heap.elements.empty())
		return v;


	if(heap.elements.size() <= 2){
		v.push_back(heap.elements[1]);
		return v;
	}
	
	int h = 1;
	while(heap.elements.size() - 1 > pow(2, h) -1)
		h = h + 1;

	h = h  - 1;
	

	for(size_t i = (int) pow(2,h);i< heap.elements.size(); i ++)
		v.push_back(heap.elements[i]);

	return v; 
}

