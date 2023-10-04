
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
int getAverage();
void loadImage ();
void saveImage ();
void userChoice();
void welcomeScreen();
void blur();
void blackAndWhite ();

int main()
{
    welcomeScreen();
    loadImage();
    saveImage();
  return 0;
}

void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
   cout<<'\n';
}

void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

void blackAndWhite() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
        if (image[i][j] > getAverage())
            image[i][j] = 255;
        else
            image[i][j] = 0;
    }
  }
}

void welcomeScreen() {
cout<<"\t\t\t\t<----- Welcome to ZETOSHOP: The Who Needs 'Em Edition ----->\n";
loadImage();
cout<<"\t\t\t\t\t<----- Please choose what you wanna do ----->\n"<<
"-1. Black and white filter\n"<<
"-2. Get average pixels (advanced)\n";
userChoice();


}

void userChoice() {
    unsigned short choice;
    cin>>choice;
    switch (choice) {
        case(1):
            blackAndWhite();
            break;
        case(2):
           cout<< getAverage();
            break;
    }
}

void blur(){

}

int getAverage(){
    int avg = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            avg += (image[i][j]);
        }
    }

    return (avg/(SIZE*SIZE));
}
