#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

ImageTraversal::~ImageTraversal() {
  // Nothing
}

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal(), finished_flag(true) {
  // Nothing
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start) 
  :traversal(&traversal), start(start), finished_flag(false) {
  current = traversal.peek();
}

ImageTraversal::Iterator::~Iterator() {
  if (traversal != NULL)
    delete traversal;
  
  traversal = NULL;
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {

    Point currenttop = traversal->pop();
    traversal->setVisit(currenttop.x, currenttop.y);
    
    Point right(currenttop.x + 1, currenttop.y);
    Point below(currenttop.x, currenttop.y + 1);
    Point left(currenttop.x - 1, currenttop.y);
    Point above(currenttop.x, currenttop.y - 1);
    HSLAPixel & origialPixel = traversal->passPng()->getPixel(start.x, start.y);

    
    if ( right.x < traversal->passPng()->width() ) {
      HSLAPixel & pixelRight = traversal->passPng()->getPixel(right.x, right.y);
      double difference = calculateDelta(origialPixel, pixelRight);

      if ( difference < traversal->getTolerance()) 
        traversal->add(right);
      
    }

    // Below case
    if ( below.y < traversal->passPng()->height() ) {
      HSLAPixel & pixelBelow= traversal->passPng()->getPixel(below.x, below.y);
      double difference = calculateDelta(origialPixel, pixelBelow);

      if  ( difference < traversal->getTolerance()) 
        traversal->add(below);
      
    }
    // Left case
    if ( left.x < traversal->passPng()->width() ) {
      HSLAPixel & pixelLeft = traversal->passPng()->getPixel(left.x, left.y);
      double difference = calculateDelta(origialPixel, pixelLeft);

      if ( difference < traversal->getTolerance()) 
        traversal->add(left);
      
    }
    // Above case
    if ( above.y < traversal->passPng()->height() ) {
      HSLAPixel & pixelAbove = traversal->passPng()->getPixel(above.x, above.y);
      double difference = calculateDelta(origialPixel, pixelAbove);

      if ( difference < traversal->getTolerance()) 
        traversal->add(above);
      
    }
 
    while ( !(traversal->empty()) && (traversal->getVisited(traversal->peek().x, traversal->peek().y))) {
      traversal->pop();
    }

    if (traversal->empty()) {
      finished_flag = true;
      return *this;
    }
    current = traversal->peek();
    return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
    return current;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {

    return !(finished_flag && other.finished_flag);
}



