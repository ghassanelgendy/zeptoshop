//Image Processor Project
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
//declaring the matrix
unsigned char image[SIZE][SIZE];
//initializing the average contrast for each pixel
int avg = 127;
//function to generate average contrast for image
void getAverage(int &average);
//load image exists in same directory
void loadImage ();
//save image in same directory
void saveImage ();
//prompt takes choice from user
void userChoice();
//start point of the project
void welcomeScreen();
//"invert" filter
void invert();
//"black and white" filter
void blackAndWhite (int average);

void merge();

int continuePrompt();

int main()
{
    welcomeScreen();
    loadImage();
    getAverage(avg);
    userChoice();
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

void welcomeScreen() {
cout<<"\t\t\t\t<----- Welcome to ZETOSHOP: The Who Needs 'Em Edition ----->\n";

}

int continuePrompt(){
    cout<<"\t\t\t\t\t<----- Do you want to do anything else? ----->\n"<<
        "Y to continue / N to exit\n";
    char c;
    cin>>c;
    if (c == 'y' || c == 'Y')
        userChoice();
    else
        return 0;
}

void getAverage(int &average){
    int sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum += (image[i][j]);
        }
    }
    average = (sum/(SIZE*SIZE));
    cout<<"Average contrast: "<<average<<"\n";
}

void userChoice() {
    unsigned short choice;
    cout<<"\t\t\t\t\t<----- Please choose what you wanna do ----->\n"<<
        "-1. Black and white filter\n"<<
        "-2. Get average pixels (advanced)\n"<<
        "-3. Invert\n"<<
        "-4. Save image to a file\n";
    cin>>choice;
    switch (choice) {
        case(1):
            blackAndWhite(avg);
            break;
        case(2):
           cout<< avg;
            break;
        case(3):
            invert();
            break;
        case(4):
            saveImage();
            break;
        case(5):
            merge();
    }
}

void invert(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
        image[i][j] = 255 - image[i][j] ;
        }
    }
}

void blackAndWhite(int average) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (image[i][j] > average)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

void merge() {
loadImage();
    for (int i = 0; i < SIZE; ++i) {
        
    }
}

