 /**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include "cs225/PNG.h"
using namespace cs225;

class StickerSheet{

  public:

  StickerSheet (const Image &picture, unsigned maxNum);

  ~StickerSheet ();

  void clear();

  void copy(const StickerSheet &other);

  StickerSheet (const StickerSheet &other);

  const StickerSheet & operator= (const StickerSheet &other);

  void  changeMaxStickers (unsigned max);

  int   addSticker (Image &sticker, unsigned xCoord, unsigned yCoord);

  bool  translate (unsigned index, unsigned xCoord, unsigned yCoord);

  void  removeSticker (unsigned index);

  Image * getSticker (unsigned index);


  Image   render () const;

  private:

    unsigned *x_;
    unsigned *y_;
    Image ** Image_;
    Image * basePicture_;
    unsigned index_;
    unsigned max_;


};