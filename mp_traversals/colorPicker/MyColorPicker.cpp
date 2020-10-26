#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include<stdio.h>
#include<math.h>

using namespace cs225;

MyColorPicker::MyColorPicker(HSLAPixel color): color(color){
	
}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  return HSLAPixel(int(sqrt(x*x + y*y)) % 360, 1, 0.5);
}
