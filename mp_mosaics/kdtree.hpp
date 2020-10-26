/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim < 0 || curDim >= Dim)
      return false;  
    if(first[curDim]==second[curDim])  
        return first<second;
    else
      return (first[curDim] < second[curDim]);  
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double current_distance = 0;
    double potential_distance = 0;
    for(int i=0; i<Dim;i++){  
        current_distance += ((target[i]-currentBest[i])*(target[i]-currentBest[i]));
        potential_distance += ((target[i]-potential[i])*(target[i]-potential[i]));
    }

    if(current_distance==potential_distance) 
      return potential < currentBest;  
    else
      return potential_distance<current_distance;
}

template <int Dim>
unsigned KDTree<Dim>::quickSelectHelper(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned pivotIndex)
{
    Point<Dim> pivotValue = list[pivotIndex];
    Point<Dim> temp = list[pivotIndex];

    list[pivotIndex] = list[right];
    list[right] = temp;
    
    unsigned tempIndex = left;
    
    for(unsigned i = left;i<right;i++){
      if(smallerDimVal(list[i],pivotValue,dimension)){
          temp = list[tempIndex];
          list[tempIndex] = list[i];
          list[i] = temp;
          tempIndex++;
      }
    }

    temp = list[tempIndex];
    list[tempIndex] = list[right];
    list[right] = temp;
    return tempIndex;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned k)
{
    if(left==right)
      return list[left];

    unsigned pivotIndex = k;

    pivotIndex = quickSelectHelper(list,dimension,left,right,pivotIndex);  

    if(k==pivotIndex)
      return list[k];

    else if(k<pivotIndex)
      return quickSelect(list, dimension, left, pivotIndex-1, k);

    else 
      return quickSelect(list, dimension, pivotIndex+1, right, k); 
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::constructorHelper(vector<Point<Dim>>& points_, int dimension, unsigned left, unsigned right)
{
    if(points_.empty()||left<0||right>=points_.size()||right<0||left>=points_.size())
      return NULL;

    if(left>right) 
      return NULL;

    unsigned mid_index = (left+right)/2; 

    KDTreeNode* subroot_ = new KDTreeNode(quickSelect(points_,dimension%Dim,left,right,mid_index));
    size+=1;
    dimension++;
    subroot_->left = constructorHelper(points_,dimension,left,mid_index-1);  
    subroot_->right = constructorHelper(points_,dimension,mid_index+1,right);  
  
    return subroot_;
}



template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    vector<Point<Dim>> points_;
    points_.assign(newPoints.begin(), newPoints.end());
    root = constructorHelper(points_, 0, 0, points_.size()-1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other)
{
  /**
   * @todo Implement this function!
   */

  copy(this->root, other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) 
{
  /**
   * @todo Implement this function!
   */
    if (this != NULL) 
      clear(root);

    copy(this->root, rhs.root);
    size = rhs.size;
    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() 
{
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor(root, query, 0);  
}
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode * subroot, const Point<Dim>& query, int dimension) const 
{
  Point<Dim> currentBest = subroot->point;
  bool flag;
  KDTreeNode * checkTraversal;

  if (subroot->left == NULL && subroot->right == NULL) 
    return subroot->point;
  
  if (smallerDimVal(query, subroot->point, dimension)) 
  {
        if (subroot->left == NULL)  
          currentBest = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
        else  
          currentBest = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);

        flag = true;  
  }
  else 
  {
        if (subroot->right == NULL)  
          currentBest = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
        else  
          currentBest = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
        
        flag = false;  
  }
  
  if (shouldReplace(query, currentBest, subroot->point)) 
    currentBest = subroot->point;
  

  double radius = 0;

  for (int i = 0; i < Dim; i++) {
    radius += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
  }

  double distance = subroot->point[dimension] - query[dimension];
  distance = distance * distance;

  if (distance <= radius) { 

    if(flag)
      checkTraversal = subroot->right;
    else
      checkTraversal = subroot->left;

    if (checkTraversal != NULL) { 
      Point<Dim> otherBest = findNearestNeighbor(checkTraversal, query, (dimension + 1) % Dim);
      
      if (shouldReplace(query, currentBest, otherBest))
        currentBest = otherBest;
    }

  }

  return currentBest;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * subroot) 
{
  if (subroot == NULL) 
    return;

  if (subroot->left != NULL) 
    clear(subroot->left);

  if (subroot->right != NULL) 
    clear(subroot->right);

  delete subroot;
  subroot = NULL;
}


template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * subroot, KDTreeNode * othersubroot) {

  subroot = new KDTreeNode();
  subroot->point = othersubroot->point;
  copy(subroot->left, othersubroot->left);
  copy(subroot->right, othersubroot->right);

}




