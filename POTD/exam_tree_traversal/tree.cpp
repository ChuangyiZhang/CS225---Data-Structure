#ifndef TREE_CPP
#define TREE_CPP

#include "tree.h"

template <class T>
Tree<T>::Iterator::Iterator(Tree::Node *root) : curr_(root) {
	// TODO: your code here
	if(curr_ == NULL) 
		return;	
	while(curr_ != NULL) {
		stacktemp.push(curr_);
		curr_ = curr_->left_;
	}

	curr_ = stacktemp.top();
	stacktemp.pop();

	if((curr_->data_ )%2 == 0 ) 
		operator++();
}

template <class T>
typename Tree<T>::Iterator & Tree<T>::Iterator::operator++() {
	// TODO: your code here
	if(curr_->right_ != NULL) {
		curr_ = curr_->right_;

		while(curr_ != NULL) {
			stacktemp.push(curr_);
			curr_ = curr_->left_;
		}
		
		curr_ = stacktemp.top();
		stacktemp.pop();
	} else {
		if(stacktemp.empty()) {
			curr_ = NULL;
			return *this;
		}

		curr_ = stacktemp.top();
		stacktemp.pop();
	}
	

	if((curr_->data_ )%2 == 0 ) 
		operator++();
	
	return *this;
}

template <class T>
T Tree<T>::Iterator::operator*() const {
	// TODO: your code here
	if(curr_ == NULL)
		return T(); 
	else 
		return curr_->data_;	
}



/*******************
 ** PROVIDED CODE **
 *******************/
template <class T>
bool Tree<T>::Iterator::operator!=(const Tree<T>::Iterator &other) {
	return !(curr_ == other.curr_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::begin() {
	return Iterator(root_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::end() {
	return Iterator(NULL);
}

#endif