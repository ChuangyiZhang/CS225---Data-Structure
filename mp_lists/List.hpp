/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {


	if(length_ == 0 )
		return;

	while( head_  !=  0  ){ 		
 		ListNode * next = head_->next;
 		delete head_;
 		head_ = next;

	}

	head_ = NULL; 
	tail_ = NULL;
	
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1


  ListNode * newNode = new ListNode(ndata);

	if(length_ == 0){
		head_ = newNode;
		tail_ = newNode;
		newNode -> next = NULL;
		newNode -> prev = NULL;  
 	}
 	else{
 		newNode -> prev = NULL;
 		newNode -> next = head_; 
 		head_ -> prev = newNode; 
 		head_ = newNode;
 	}	

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1

	ListNode * newNode = new ListNode(ndata);

	if(length_ == 0){
		head_ = newNode;
		tail_ = newNode;
		newNode -> next = NULL;
		newNode -> prev = NULL;  
 	}
 	else{
 		newNode->next = NULL;
 		newNode->prev = tail_;
 		tail_->next = newNode; 
 		tail_ = newNode;
 	
 	}	

	length_++;


}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  
 if(start == NULL)
 	return NULL;
 if(splitPoint < 1)
 	return start;
 if(length_ < splitPoint)
 	return NULL;

	ListNode * curr = start;
	 int counter = 0; 
	 while(counter < splitPoint){
	 	if(curr->next !=NULL)
	 		curr = curr->next;
	 	counter++;
	 }

	tail_ = curr->prev;
	curr->prev->next = NULL;
	curr->prev = NULL;
	return curr; 


}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {

    
    ListNode * temp = NULL; 
    ListNode * curr= NULL; 
    ListNode * end = NULL; 
    bool  reservesLastNode = false;
    int length = length_;
     
    
    if(length == 3){
        temp = head_ ->next;
        curr ->prev = tail_;
        tail_ ->next = head_;
        head_ ->next = NULL;
        temp-> prev = NULL; 
        tail_ = head_;
        head_ = temp;

    }
    
    
    
    
    if(length > 3 )  {
    
        temp = head_ -> next;
        temp-> prev = NULL; 
        (temp->next)->next-> prev= head_;
        head_->next = temp->next->next;
        temp->next->next = head_;
        head_->prev = temp->next; 
        head_ = temp; 
        curr = head_->next->next->next; 
        ListNode * nextcurr;
        length = length - 3;
        

    
    
    while(curr != NULL){
        
        if(length == 3){
            end = curr;
            reservesLastNode = true;
        }

        if(curr->next == NULL)
            break;
        if(curr->next->next == NULL)
            break;
    
        if(curr->next->next ->next == NULL)
            break;
    
        nextcurr = curr->next->next->next;
        
        cout<<length<<endl;
        
        if(length == 6 ){
            end = nextcurr;
            reservesLastNode = true; 
        }
        
        temp = curr -> next;
        temp->prev = curr->prev;
        curr->prev->next = temp;
        curr->next = temp->next->next;
        temp->next->next->prev = curr;
        temp->next->next = curr;
        curr->prev = temp ->next ->next; 
        curr = nextcurr;
        length = length - 3;  
        }
    }   
    
    
    if(reservesLastNode ){
        
       temp = end ->next;
       temp-> prev = end->prev;
       end->prev->next = temp; 
       end ->prev = tail_;
       tail_ ->next = end;
       end ->next = NULL;
        
        tail_ = end;
        end = temp;
    }




  // @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {



	/// @todo Graded in MP3.2
	if(startPoint == NULL && endPoint == NULL)
		return;
	if(tail_ == head_)
		return;

	ListNode * StartPointPrev = startPoint->prev;

	ListNode * curr = startPoint;
	ListNode * temp = curr->next; 
	curr->next = endPoint->next;
	curr->prev = temp;
	curr = temp;


	while (curr != endPoint){
		temp = curr->next;
		curr->next = curr->prev;
		curr->prev = temp;
		curr = temp;
	}

	endPoint->next = endPoint->prev;
	endPoint->prev = StartPointPrev;

	if(head_!= startPoint)
		StartPointPrev->next = curr;

	if(head_ == startPoint)
		head_ = endPoint;

	if(tail_ != endPoint)
		startPoint->next->prev = startPoint;

	if(tail_ == endPoint)
		tail_ = startPoint;
	
  
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
	ListNode * reverseBegin = head_;
	ListNode * reverseEnd = reverseBegin;


	while(reverseBegin != NULL){
		for(int i = 1; i < n ; i ++){
			if(reverseEnd != tail_)
				reverseEnd = reverseEnd->next;
		}
		reverse(reverseBegin, reverseEnd);
		reverseBegin = reverseBegin->next;
		reverseEnd = reverseBegin;
	}

  /// @todo Graded in MP3.2
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;



}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
	ListNode* newHead = NULL;

	if(first->data < second->data){
		newHead = first;
		first = first->next;
	}
	else{
		newHead = second;
		second = second->next; 
	}

	ListNode * currentNode = newHead;
	while (first != NULL && second != NULL){
		if(second->data < first->data){
			currentNode->next = second;
			second->prev = currentNode;
			second = second -> next;
		}else{
			currentNode->next = first;
			first->prev = currentNode;
			first = first->next;
		}
		currentNode = currentNode -> next; 
	}

	if(second == NULL && first != NULL){
		currentNode->next = first;
		first->prev = currentNode;
	}

	if(first == NULL && second != NULL){
		currentNode->next = second;
		second->prev = currentNode;
	}


  return newHead;

 
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

	if(start->next == NULL)
		return start;
	ListNode * second = split(start, chainLength/2);

  	return merge(mergesort(start,chainLength/2), (mergesort(second,(chainLength%2) +chainLength/2)));
}






