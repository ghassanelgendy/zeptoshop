//Image Processor Project by:
//Ghassan Elgendy 20220239    E-Mail: Ghassanelgendyy@gmail.com
//Rowan Ammar     20220133    E-Mail: rawanehab523@gmail.com
//Jana Mohamed    20220470    E-Mail: janamohamedramadan335@gmail.com
//3/10/2023//
#include <iostream>
#include "zeptolib/zeptolib.cpp"
using namespace std;

//declaring the matrix
unsigned char image[SIZE][SIZE];

//boolean to catch logical errors
bool isIssue = false;

bool quartError = false;

//declaring the matrix for rotation
unsigned char rotated[SIZE][SIZE];

//initializing the average contrast for each pixel
int avg = 127;

//function to generate average contrast for image
void getAverage(int &average);

//load image exists in same directory
void loadImage(unsigned char img[SIZE][SIZE]);

//save image in same directory
void saveImage();

//prompt takes choice from user
int userChoice();

//start point of the project
void welcomeScreen();

//"invert" filter
void invert();

//"black and white" filter
void blackAndWhite(int &average);

//optional filter
void addFrame();

//merge two images
void merge();

//flip image in two axes
void flip();

//prompt user to continue editing or save
int continuePrompt();

//prompt user for rotation degree
void rotationPrompt();

//rotates the image
void rotate(short times);

//decrease image brightness by 50%
void darken();

//increase image brightness by 50%
void brighten();

//prompt user to modify image brightness
void controlBrightness(unsigned char c);

//applies the picked filter to the global image[SIZE][SIZE] matrix
void burnEffect(unsigned char newImg[SIZE][SIZE]);

//detect edges of an object
void detectEdges();

//enlarge chosen quarter by scale 4x
void enlarge();

//shrink image by a desired scale
void shrink();

//mirrors chosen half of the imagw
void mirror();

//shuffles quarters of the image
void shuffle();

//blurs the image
void blur();

//crops the image from desired point with desired dimensions
void crop();

//skews the image horizontally or vertically
void skew();

int main() {
    startMainLabel:
    isIssue = false;
    cout << "\t\t\t\t=== Welcome to ZEPTOSHOP: The Who Needs 'Em Edition ===\n";
    loadImage(image, RGBImage);
    if (!isIssue) {
        getAverage(avg);
        imageInfo();
        userChoice();
    } else {
        cout << errorMsg;
        goto startMainLabel;
    }
    return 0;
}
