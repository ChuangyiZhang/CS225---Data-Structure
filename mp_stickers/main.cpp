#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"


int main() {

    Image thonasironman;
    Image inevitable;
    Image segFault;
    Image valgrind;
    Image students;

    Image myImage;

    thonasironman.readFromFile("images/ironmanthanos.png");
    inevitable.readFromFile("images/inevitable.png");
    segFault.readFromFile("images/segFault.png");
    valgrind.readFromFile("images/valgrind.png");
    students.readFromFile("images/students.png");
    myImage.readFromFile("myImage.png");

    students.scale(0.5);
    segFault.scale(0.5);
    valgrind.scale(0.5);
    inevitable.scale(0.5);




    StickerSheet sheet(myImage,6);
    sheet.addSticker(thonasironman, 0,0);
    sheet.addSticker(inevitable, 500,580);
    sheet.addSticker(segFault, 600,20);
    sheet.addSticker(valgrind, 700,800);
    sheet.addSticker(students, 200,1250);

    Image output = sheet.render();


    output.writeToFile("myImage.png");





  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
