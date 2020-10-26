#include "TreeNode.h"
#include <queue>

TreeNode* findLastUnbalanced(TreeNode* root) {
  	TreeNode * temp = root;
  	TreeNode * result = NULL;
  	std::queue<TreeNode*> tempQueue;

  	while( temp != NULL){
  		if( ! isHeightBalanced(temp))
  			result = temp;

  		tempQueue.push(temp->left_);
  		tempQueue.push(temp->right_);
  		temp = tempQueue.front();
  		tempQueue.pop();
  	}

  return result;
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}


bool isHeightBalanced(TreeNode* root) {
  	if(findHeight(root->left_) - findHeight(root->right_) == 1)
		return true;


	if(findHeight(root->left_) - findHeight(root->right_) == -1)
		return true;


	if(findHeight(root->left_) - findHeight(root->right_) == 0)
		return true;


  	
  	return false;
}




int findHeight(TreeNode * root){

	if(root == NULL)
		return -1;

	if(root->left_ == NULL && root->right_ == NULL)
		return 0;

	int leftHeight = 0;
	int rightHeight = 0;

	if(root->left_ != NULL)
		leftHeight = findHeight(root->left_);

	if(root->right_ != NULL)
		rightHeight = findHeight(root->right_);

	if(rightHeight >= leftHeight)
		return rightHeight+1;
	else 
		return leftHeight + 1; 

}