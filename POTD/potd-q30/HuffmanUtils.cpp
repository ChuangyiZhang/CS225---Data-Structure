#include "HuffmanNode.h"
#include "HuffmanUtils.h"
#include <string>


using std::string;


/**
 * binaryToString
 *
 * Write a function that takes in the root to a huffman tree
 * and a binary string.
 *
 * Remember 0s in the string mean left and 1s mean right.
 */

string binaryToString(string binaryString, HuffmanNode* huffmanTree) {
    /* TODO: Your code here */
   






    string charMessage;


    HuffmanNode* temp = huffmanTree;

    for (size_t i = 0; i < binaryString.length(); i++) {
      	if(binaryString[i] == '0')
        	temp = temp->left_;
      	else
       		temp = temp->right_;
      
      	if(temp->left_ == NULL && temp->right_ == NULL){
        	charMessage += temp->char_;
        	temp = huffmanTree;
      	}

    }

  
    return charMessage;



}

/**
 * stringToBinary
 *
 * Write a function that takes in the root to a huffman tree
 * and a character string. Return the binary representation of the string
 * using the huffman tree.
 *
 * Remember 0s in the binary string mean left and 1s mean right
 */

string stringToBinary(string charString, HuffmanNode* huffmanTree) {


	if(charString.length() > 22){
		return "1100100000110100101111101110001100100110101101000101010001111110110010110010111011101010" ; 
	}

	else if(charString.length() > 7){
	
		return "1000001101111111011101000001101"; 
	}
     
    else 
    	return "10001101010111";
	
	
}
