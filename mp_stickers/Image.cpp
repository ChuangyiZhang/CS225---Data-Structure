/***
*
*
*
*
*
***/

#include "cs225/HSLAPixel.h"
#include "Image.h"
#include "cs225/PNG.h"
#include <cmath>
#include <iostream>
using namespace std;
using namespace cs225;



	//Lighten an Image by increasing the luminance of every pixel by 0.1
	void Image:: lighten (){

	for(unsigned x = 0 ; x < width(); x ++){
		for(unsigned y = 0; y < height(); y ++){
			HSLAPixel &pixel = this->getPixel(x,y);
			if(pixel.l >= 0.9)
				pixel.l = 1;

			else
				pixel.l = pixel.l + 0.1;
		}
	}

}


	//Lighen an Image by increasing the luminance of every pixel by amount
 	void  Image:: lighten (double amount){
		for(unsigned x = 0 ; x < width(); x ++){
			for(unsigned y = 0; y < height(); y ++){
			HSLAPixel &pixel = this->getPixel(x,y);
				if(pixel.l >= (1- amount))
				pixel.l = 1;

			else
				pixel.l = pixel.l + amount;
		}
	}
}



	//Darken an Image by decreasing the luminance of every pixel by 0.1
	void 	Image:: darken () {

		for(unsigned x = 0 ; x < width(); x ++){
			for(unsigned y = 0; y < height(); y ++){
				HSLAPixel & pixel = this->getPixel(x,y);
				if(pixel.l <= 0.1)
					pixel.l = 0;
				else
					pixel.l = pixel.l - 0.1;
		}
	}

	}

	//Darkens an Image by decreasing the luminance of every pixel by amount
	void Image:: darken (double amount){

	for(unsigned x = 0 ; x < width(); x ++){
		for(unsigned y = 0; y < height(); y ++){
			HSLAPixel & pixel = this->getPixel(x,y);
			if(pixel.l <= amount)
				pixel.l = 0;

			else
				pixel.l = pixel.l - amount;
		}
	}



	}

 	//Saturates an Image by increasing the saturation of every pixel by 0.1.
 	void Image:: saturate (){

 	for(unsigned x = 0 ; x < width(); x ++){
		for(unsigned y = 0; y < height(); y ++){
			HSLAPixel & pixel = this->getPixel(x,y);
			double old = pixel.s;
			if(pixel.s >= 0.9)
				pixel.s = 1;
			else
				pixel.s = pixel.s + 0.1;

//		if(old >= 0.9 && pixel.s == 1.0){
//			//cout << "old: "<< old << "new: " << pixel.s <<"diff: "<< old - pixel.s << endl;
//		}
//		else if((pixel.s - old ) != 0.1){
//				cout << "old: "<< old << "new: " << pixel.s <<"diff: "<< old - pixel.s << endl;
//			}
		}
	}



 	}

 	//Saturates an Image by increasing the saturation of every pixel by amount.
 	void Image:: saturate (double amount){

 	for(unsigned x = 0 ; x < width(); x ++){
		for(unsigned y = 0; y < height(); y ++){
			HSLAPixel & pixel = this->getPixel(x,y);
			if(pixel.s >= (1- amount))
				pixel.s = 1;
			else
				pixel.s = pixel.s + amount;
		}
	}

 	}



 	//Desaturates an Image by decreasing the saturation of every pixel by 0.1.
 	void Image:: desaturate () {

	for(unsigned x = 0 ; x < width(); x ++){
		for(unsigned y = 0; y < height(); y ++){
			HSLAPixel & pixel = this->getPixel(x,y);
			if(pixel.s <= 0.1)
				pixel.s = 0;

			else
				pixel.s = pixel.s - 0.1;
		}
	}

	}



 	//Desaturates an Image by decreasing the saturation of every pixel by amount.
 	void Image:: desaturate (double amount){

		for(unsigned x = 0 ; x < width(); x ++){
			for(unsigned y = 0; y < height(); y ++){
				HSLAPixel & pixel = this->getPixel(x,y);
				if(pixel.s <= amount)
					pixel.s = 0;
				else
					pixel.s = pixel.s - amount;
			}
		}

 	}

	//Turns the image grayscale
 	void Image:: grayscale (){

		for(unsigned x = 0 ; x < width(); x ++){
			for(unsigned y = 0; y < height(); y ++){
				HSLAPixel & pixel = this->getPixel(x,y);
				pixel.s  = 0;
			}
		}


 	}

 	// Rotates the color wheel by degrees
 	void Image:: rotateColor (double degrees){

		for(unsigned x = 0 ; x < width(); x ++){
			for(unsigned y = 0; y < height(); y ++){
				HSLAPixel & pixel = this->getPixel(x,y);


				pixel.h = pixel.h + degrees;

				while(pixel.h >360){
					pixel.h = pixel.h - 360;
				}

				while(pixel.h <0){
					pixel.h = pixel.h + 360;
				}

			}
		}


 	}

 	// Illinify the image
 	void Image:: illinify (){

   		for (unsigned x = 0; x < width(); x++) {
    		for (unsigned y = 0; y < height(); y++) {
      			HSLAPixel & pixel =this->getPixel(x,y);

      			if(pixel.h > 288 )
        			pixel.h = 11;

      			if(abs(pixel.h - 11 ) < abs(pixel.h - 216))
        			pixel.h = 11;

      			else
        			pixel.h = 216;

    		}
  		}

}
 	// Scale the Image by a given factor.
 	void Image::scale (double factor){


 		unsigned int newWidth = ceil(factor * width());
 		unsigned int newHeight = ceil(factor * height());

 		PNG * original = new PNG(*this);

 		this->resize(newWidth,newHeight);

 		if ( factor <= 1){
 		for(unsigned x = 0; x < width(); x++){
 			for(unsigned y = 0; y < height(); y++){
 				HSLAPixel & scaledPixel = (this->getPixel(x, y));
 				HSLAPixel & originalPixel = (original->getPixel(ceil(x/factor),ceil(y/factor)));
 				scaledPixel = originalPixel;

 			}
 		}
 	}

 		if( factor > 1 ){
 		for(unsigned x = 0; x < width()/factor; x++){
 			for(unsigned y = 0; y < height()/factor; y++){
 				HSLAPixel & originalPixel = (original->getPixel(x,y));
 				for(unsigned i = 0; i < ceil(factor); i ++){
 					for(unsigned j = 0; j < ceil(factor); j++){
 						HSLAPixel & scaledPixel = (this->getPixel(x*factor+i, y*factor+j));
 						scaledPixel = originalPixel;
 					}
 				}

 			}
 		}
        }

 	delete original;
 	original = NULL;


 	}

	//Scales the image to fit within the size (w x h).
 	void Image:: scale (unsigned w, unsigned h){
 		double width = this-> width();
 		double height = this->height();


 		double widthFactor = double ( w /width);
 		double heightFactor = double( h /height);

 		cout<<"widthFactor: "<< widthFactor<<endl;
 		cout<<"heightFactor: "<<heightFactor <<endl;

 		if(heightFactor < widthFactor)
 			scale(heightFactor);
 		else
 			scale(widthFactor);


 	}
