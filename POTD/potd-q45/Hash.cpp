#include <vector>
#include "Hash.h"

void doubleHashInput(std::vector<int> &v, int elem){
	//your code here

	int index = firstHash(elem, v.size());
	if(v[index] == -1){
		v[index] = elem;
	}
	else{
		while(v[index] != -1){
			index = (index + secondHash(elem)) %v.size();
		}
		v[index] = elem;
	}
  
}

//make a hash function called firstHash
int firstHash(int elem, int length){
	return (4*elem) % length;
}
//make a second function called secondHash
int secondHash(int elem){
	return 3 - (elem % 3);
}
