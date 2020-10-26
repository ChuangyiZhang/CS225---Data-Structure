#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace cs225;
using namespace std;

void rotate(std::string inputFile, std::string outputFile) {

    PNG* original = new PNG();
    
    original->readFromFile(inputFile);
    unsigned int width = original->width();
    unsigned int height = original->height();
    
    // Create out.png
    PNG* output = new PNG(width,height);

    for(unsigned int x = 0; x < width; x++) {
    	for(unsigned int y = 0; y < height; y++){

        	HSLAPixel& rota = original->getPixel(x, y);
        	HSLAPixel& rotaPixel = output->getPixel((width-1)-x,(height-1)-y);
            rotaPixel = rota;

    	}
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
   // delete original;

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  png.resize(width,height);

  unsigned int half  = width/2 ;
  unsigned int quad  = half/2 ;


      for (unsigned x = 0; x < half; x++) {
        for (unsigned y = 0; y < half; y++) {
            HSLAPixel &artpixel = png.getPixel(x,y);
            unsigned distance =  sqrt((x - quad) * (x - quad) + (y - quad)* (y - quad));
            artpixel.s=  (1 - distance * 0.005) * artpixel.l ;
            artpixel.l = 0.25;
            artpixel.a = 1;
            if(x <= quad && y <= quad)
                artpixel.h = 221;
            if(x <= quad && y >= quad)
                artpixel.h = 221;
            if(x >= quad && y <= quad)
                artpixel.h = 221;
            if(x >= quad && y >= quad)
                artpixel.h = 221;
        }
    }


      for (unsigned x = half; x < width; x++) {
        for (unsigned y = 0; y < half; y++) {
            HSLAPixel &artpixel = png.getPixel(x,y);
            unsigned distance =  sqrt(((x-half) - quad) * ((x-half) - quad) + (y - quad)* (y - quad));
            artpixel.s=  (1 - distance * 0.005) * artpixel.l ;
            artpixel.l = 0.25;
            artpixel.a = 1;
            if(x <= (quad+half) && y <= quad)
                artpixel.h = 360;
            if(x <= (quad+half) && y >= quad)
                artpixel.h = 360;
            if(x >= (quad+half) && y <= quad)
                artpixel.h = 360;
            if(x >= (quad+half) && y >= quad)
                artpixel.h = 360;
        }
    }

      for (unsigned x = 0; x < half; x++) {
        for (unsigned y = half; y < width; y++) {
            HSLAPixel &artpixel = png.getPixel(x,y);
            unsigned distance =  sqrt((x - quad) * (x - quad) + ((y-half)- quad)* ((y-half) - quad));
            artpixel.s=  (1 - distance * 0.005) * artpixel.l ;
            artpixel.l = 0.25;
            artpixel.a = 1;
            if(x <= quad && y <= (quad+half))
                artpixel.h = 37;
            if(x <= quad && y >= (quad+half))
                artpixel.h = 37;
            if(x >= quad && y <= (quad+half))
                artpixel.h = 37;
            if(x >= quad && y >= (quad+half))
                artpixel.h = 37;
        }
    }

    
      for (unsigned x = half; x < width; x++) {
        for (unsigned y = half; y < width; y++) {
            HSLAPixel &artpixel = png.getPixel(x,y);
            unsigned distance =  sqrt(((x - half) - quad ) * ((x - half) - quad) + (((y- half) - quad )* ((y- half) - quad )));
            artpixel.s=  (1 - distance * 0.005) * artpixel.l ;
            artpixel.l = 0.25;
            artpixel.a = 1;
            if(x <= (quad+half) && y <= (quad+half))
                artpixel.h = 140;
            if(x <= (quad+half) && y >= (quad+half))
                artpixel.h = 140;
            if(x >= (quad+half) && y <= (quad+half))
                artpixel.h = 140;
            if(x >= (quad+half) && y >= (quad+half))
                artpixel.h = 140;
        }
    }



  return png;
}
