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
void loadImage (unsigned char img[SIZE][SIZE]);
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

void flip();

int continuePrompt();

void rotate();

int main()
{
    welcomeScreen();
    loadImage(image);
    userChoice();
  return 0;
}

void loadImage (unsigned char img[SIZE][SIZE]) {

    char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, img);
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
    cout<<"\t\t\t\t\t<----- Do you want to save or do smth else? ----->\n"<<
        "S to save / D to do smth else\n";
    char c;
    cin>>c;
    if (c == 'd' || c == 'D')
        userChoice();
    else if (c == 's' || c == 'S')
        saveImage();
    else
        cout<<"Hanhazar?";
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
    unsigned char choice;
    cout<<"\t\t\t\t\t<----- Please choose what you wanna do ----->\n"<<
        "-1. Black and white filter\n"<<
        "-2. Get average pixels (advanced)\n"<<
        "-3. Invert\n"<<
        "-4. Merge\n"<<
        "-5. Flip\n"<<
        "-6. Rotate\n"<<
        "-7. Save image to a file\n";
    cin>>choice;
    switch (choice) {
        case('1'):
            blackAndWhite(avg);
            break;
        case('2'):
           cout<< avg;
            break;
        case('3'):
            invert();
            break;
        case('4'):
            merge();
            break;
        case('5'):
           flip();
           break;
        case('6'):
            rotate();
            break;
        case('g'):
            saveImage();
            break;
    }
    continuePrompt();
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
    cout<<"Load the second image, ";
    unsigned char secImage[SIZE][SIZE];
    loadImage(secImage);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
           image[i][j] = ( image[i][j] + secImage[i][j] ) / 2  ;
        }
    }
}

void flip(){
    cout<<"V to flip vertically, H to flip horizontally\n";
    unsigned char flipped[SIZE][SIZE];
    char x;
    cin>>x;
    if (x == 'v' || x == 'V'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                flipped[i][j] = image[SIZE - 1 - i][j];
            }
        }
    }
    else{
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                flipped[i][j] = image[i][SIZE - 1 - j];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = flipped[i][j];
    }
}

void rotate(){
    cout<<"Enter degree of rotation\n"<<
    "90, 180, 270, 360";
    unsigned char rotated[SIZE][SIZE];
    int x;
    cin>>x;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j <SIZE; ++j) {
            rotated[i][j] = image[j][i];
        }
    }
    flip();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = rotated[i][j];
    }
    saveImage();
}

