#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tolerance_ =tolerance;

  traversal.push(start);
  visited.resize(png_.width());
    for (unsigned i = 0; i < visited.size(); i++) {
        visited[i].resize(png_.height());
        for (unsigned j = 0; j < visited[i].size(); j++) {
            visited[i][j] = false;
        }
    }
    visited[start.x][start.y] = true;
}


/**
 * Returns an iterator for the traversal starting at the first point.
 */


BFS::~BFS(){
  //NOTHING
}

ImageTraversal::Iterator BFS::begin() {

    BFS * bfs = new BFS(png_, start_, tolerance_);
    return ImageTraversal::Iterator(*bfs, start_);

  /** @todo [Part 1] */
  
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  traversal.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point top = traversal.front();
  traversal.pop();
  return top;

}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return traversal.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
    return traversal.empty();
}

bool BFS::getVisited(unsigned x, unsigned y) {
    return visited[x][y];
}
void BFS::setVisit(unsigned x, unsigned y) {
    visited[x][y] = true;
}
PNG * BFS::passPng() {
    return &png_;
}
double BFS::getTolerance() {
    return tolerance_;
}