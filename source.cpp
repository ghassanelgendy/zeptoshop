
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void blackAndWhite ();
void userChoice();
void welcomeScreen();
void blur();
int main()
{
  loadImage();
  welcomeScreen();
  saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void blackAndWhite() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
        if (image[i][j] > 255/2)
            image[i][j] = 255;
        else
            image[i][j] = 0;
    }
  }
}

void welcomeScreen() {
cout<<"\t\t\tWelcome to ZETOSHOP: The Who Needs 'Em Edition\n\t\t\t\tPlease choose what you wanna do \n"<<
"1. Black and white filter\n";
userChoice();


}

void userChoice() {
    unsigned short choice;
    cin>>choice;
    switch (choice) {
        case(1):
            blackAndWhite();
            break;
    }
}

void blur(){

}