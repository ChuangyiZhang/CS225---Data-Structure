#include "cs225/HSLAPixel.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "StickerSheet.h"
#include <cmath>
#include <iostream>
using namespace std;
using namespace cs225;


StickerSheet::StickerSheet (const Image &picture, unsigned max){
  max_ = max;
  basePicture_ = new Image(picture);
  Image_ = new Image*[max_];
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];
  index_ = 0;
  x_[0] = 0;
  y_[0] = 0;

}


StickerSheet::~StickerSheet (){
  clear();
}

StickerSheet:: StickerSheet (const StickerSheet & other){
  copy(other);

}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
  if(this != &other){
    clear();
    copy(other);
  }
  return *this;
}

void StickerSheet:: clear (){
  for(unsigned i =0 ; i < index_; i ++){
      delete Image_[i];
      Image_[i] = NULL;
  }

  delete[] Image_;
  Image_ = NULL;

  delete[] x_;
  x_ = NULL;

  delete[] y_;
  y_ = NULL;

  delete basePicture_;
  basePicture_ = NULL;

}

void StickerSheet:: copy(const StickerSheet & other){
  index_ = other.index_;
  max_ = other.max_;
  basePicture_ = new Image(*other.basePicture_);
  Image_ = new Image*[max_];
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];

  for(unsigned i = 0; i < index_; i ++){
    Image_[i] = new Image ();
    *(Image_[i]) = * (other.Image_[i]);
    x_[i] = other.x_[i];
    y_[i] = other.y_[i];
  }

}

void StickerSheet::changeMaxStickers (unsigned max){


  Image ** tempPicture = new Image * [index_];
  unsigned * tempx = new unsigned[index_];
  unsigned * tempy = new unsigned[index_];

  for(unsigned i = 0; i < index_; i++){
    tempPicture[i] = Image_[i];
    tempx[i] = x_[i];
    tempy[i] = y_[i];
  }


  delete[] Image_;
  Image_ = NULL;
  delete[] x_;
  x_ = NULL;
  delete[] y_;
  y_ =NULL;

  Image_ = new Image * [max];
  x_ = new unsigned[max];
  y_ = new unsigned[max];


  if(max < index_){

    for(unsigned i = max; i <index_; i++){
      delete tempPicture[i];
      tempPicture[i] = NULL;
    }

    for(unsigned i = 0; i < max; i++){
      Image_[i] = tempPicture[i];
      x_[i] = tempx[i];
      y_[i] = tempy[i];
    }

    index_ = max;

  }else{

      for(unsigned i = 0; i < index_; i++){
          Image_[i] = tempPicture[i];
          x_[i]= tempx[i];
          y_[i]= tempy[i];
      }

    }

  max_ = max;
  delete[] tempPicture;
  delete[] tempx;
  delete[] tempy;


}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
    for(unsigned i = 0; i < max_; i++){
      if(i == index_){
        Image_[i] = new Image(sticker);
        x_[i] = x;
        y_[i] = y;
        index_ = index_+1;
        return int(i);
      }
    }

  return -1;

}

bool  StickerSheet::translate (unsigned index, unsigned x, unsigned y){

  if(index < index_){
    x_[index] = x;
    y_[index] = y;
    return true;
  }
  else
    return false;

}

void  StickerSheet::removeSticker (unsigned index){

  delete Image_[index];

  for(unsigned i = index; i < max_ -1; i++){
     Image_[i] = Image_[i+1];
     x_[i] = x_[i+1];
     y_[i] = y_[i+1];
  }

  x_[max_ -1] = 0;
  y_[max_-1] =0;
  Image_[max_-1] = NULL;
  index_ = index_ -1;

}

Image * StickerSheet::getSticker (unsigned index){
  if(index < index_ )
    return Image_[index];
  else
    return NULL;

}


Image   StickerSheet::render () const{


  Image *base = new Image(*basePicture_);
  unsigned width = base->width();
  unsigned height = base->height();


  for(unsigned i = 0; i < index_ ; i++){

    unsigned x = x_[i] + Image_[i] -> width();
    unsigned y = y_[i] + Image_[i] ->height();

    if(x > width)
      width = x;
    if(y > height)
      height = y;

    base->resize(width,height);

    for(unsigned x = x_[i]; x < (x_[i] + Image_[i]-> width()); x ++){
      for(unsigned y = y_[i]; y < (y_[i] + Image_[i]->height()); y++){
        HSLAPixel & basePixel = base->getPixel(x,y);
        HSLAPixel & pixel = Image_[i]->getPixel(x- x_[i],y - y_[i]);
        if(pixel.a !=0)
          basePixel = pixel;
    }

  }
}
  Image result = *base;
  delete base;

  return result;

}
