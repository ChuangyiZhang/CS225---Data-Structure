
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png;
  png.readFromFile("myimage.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(20,40), 0.2);
  HSLAPixel soild(319, 100,41);
  MyColorPicker color(soild);
  image.addFloodFill(bfs, color);
    
  DFS dfs(png, Point(200,400), 0.2);
  HSLAPixel soild1(151, 100,40);
  MyColorPicker color2(soild1);
  image.addFloodFill(dfs, color2);


  Animation animation = image.animate(2000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
