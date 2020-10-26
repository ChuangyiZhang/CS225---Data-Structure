#include "TreeNode.h"

bool isHeightBalanced(TreeNode* root) {
  	if(findHeight(root->left_) - findHeight(root->right_) == 1)
		return true;


	if(findHeight(root->left_) - findHeight(root->right_) == -1)
		return true;


	if(findHeight(root->left_) - findHeight(root->right_) == 0)
		return true;


  	
  	return false;
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
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