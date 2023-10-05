//Image Processor Project
#include <iostream>
#include <cstring>
#include "bmplib.cpp"

using namespace std;

//declaring the matrix
unsigned char image[SIZE][SIZE];

//boolean to catch logical errors
bool issue = false;

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
void userChoice();

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

//enlarge chosen quarter by scale 2x
void enlarge();

int main() {
    issue = 0;
    welcomeScreen();
    loadImage(image);
    if (!issue) {
        getAverage(avg);
        userChoice();
    } else {
        cout << "\t\t\t\t-----> An unexpected error happened please try again! <-----\n";
        main();
    }
    return 0;
}

void loadImage(unsigned char img[SIZE][SIZE]) {

    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    (readGSBMP(imageFileName, img)) ? issue = 1 : readGSBMP(imageFileName, img);
    cout << '\n';
}

void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
    cout << '\n';
}

void welcomeScreen() {
    cout << "\t\t\t\t<----- Welcome to ZETOSHOP: The Who Needs 'Em Edition ----->\n";

}

int continuePrompt() {
    cout << "\t\t\t\t\t<----- Do you want to save or do something else? ----->\n" <<
         "(S) to save, (D) to do something else\n";
    char c;
    cin >> c;
    if (c == 'd' || c == 'D')
        userChoice();
    else if (c == 's' || c == 'S')
        saveImage();
    else
        cout << "Hanhazar?";
    return 0;
}

void getAverage(int &average) {
    int sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum += (image[i][j]);
        }
    }
    average = (sum / (SIZE * SIZE));
    cout << "\t\t\t\t<----- FOR DEBUGGING I'M IN LINE (118) - Average contrast: <-----" << average << "\n";
}

void userChoice() {
    unsigned char choice;
    cout << "\t\t\t\t\t<----- Please choose what you wanna do ----->\n" <<
         "-1. Black and white filter\n" <<
         "-2. Get average pixels contrast (advanced)\n" <<
         "-3. Invert\n" <<
         "-4. Merge\n" <<
         "-5. Flip\n" <<
         "-6. Rotate\n" <<
         "-7. Change brightness\n" <<
         "-8. Detect edges\n" <<
         "-9. Add smart frame\n" <<
         "-C. Enlarge\n" <<
         "-S. Save image to a file\n";
    cin >> choice;
    choice = tolower(choice);
    switch (choice) {
        case ('1'):
            blackAndWhite(avg);
            break;
        case ('2'):
            cout << "Average pixels contrast = " << avg << '\n';
            break;
        case ('3'):
            invert();
            break;
        case ('4'):
            merge();
            break;
        case ('5'):
            flip();
            break;
        case ('6'):
            rotationPrompt();
            break;
        case ('7'):
            cout << "Choose (B) to brighten the image by 50%, (D) to darken it by 50%\n";
            unsigned char c;
            cin >> c;
            controlBrightness(c);
            break;
        case ('8'):
            detectEdges();
            break;
        case ('9'):
            addFrame();
            break;
        case ('a'):
            cout << "a Under construction\n";
            break;
        case ('b'):
            cout << "b Under construction\n";
        case ('c'):
            enlarge();
            break;
        case ('d'):
            break;
        case ('s'):
            saveImage();
            break;
        default:
            cout << "Wrong entry<<\n";
            userChoice();
            break;
    }
    continuePrompt();
}

void invert() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }
}

void blackAndWhite(int &average) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            (image[i][j] > average) ? image[i][j] = 255 : image[i][j] = 0;
        }
    }
}

void merge() {
    cout << "Load the second image, ";
    unsigned char secImage[SIZE][SIZE];
    loadImage(secImage);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + secImage[i][j]) / 2;
        }
    }
}

void flip() {
    cout << "(V) to flip vertically, (H) to flip horizontally\n";
    unsigned char flipped[SIZE][SIZE];
    char x;
    cin >> x;
    if (x == 'v' || x == 'V') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                flipped[i][j] = image[SIZE - 1 - i][j];
            }
        }
    } else {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                flipped[i][j] = image[i][SIZE - 1 - j];
            }
        }
    }
    burnEffect(flipped);
}

void burnEffect(unsigned char newImg[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = newImg[i][j];
    }
}

void rotate(short time) {
    for (int k = 0; k < time; ++k) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                rotated[i][j] = image[j][SIZE - 1 - i];
            }
        }
        burnEffect(rotated);
    }
}

void rotationPrompt() {
    cout << "Enter degrees of rotation: \n" <<
    "90, 180, 270, 360\n";
    int x;
    cin >> x;
    switch (x) {
        case (90):
            rotate(1);
            break;
        case (180):
            rotate(2);
            break;
        case (270):
            rotate(3);
            break;
        default:
            cout << "?";
    }
}

void controlBrightness(unsigned char c) {
    (c == ('b' | 'B')) ? brighten() : darken();
}

void darken() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] /= 2;
        }
    }
}

void brighten() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + 255) / 2;
        }
    }
}

void detectEdges() {
    unsigned char detected[SIZE][SIZE];
    for (int i = 1; i < SIZE-1; ++i) {
        for (int j = 1; j < SIZE-1; ++j) {
            if (image[i+1][j] == 0  &&
                image[i-1][j] == 255 ||

                image[i][j+1] == 0 &&
                image[i][j-1] ==255){
                detected[i][j] = 0;
            }
            else{
                detected[i][j] = 255;
            }
        }
        burnEffect(detected);
    }
}

void addFrame() {
    unsigned short clr = 255;
    if (avg > 128) clr = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i <= 5 || j <= 5 || i > 250 || j > 250) {
                image[i][j] = clr;
            }
        }
    }
}

void enlarge() {
    int x;
    unsigned char enlarged[SIZE][SIZE];

    cout << "Which quarter do you want to enlarge?\n";
    cin >> x;
    switch (x) {
        //first quad
        case (1):
            for (int i = 0; i < 128; ++i) {
                for (int j = 0; j < 128; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        for (int l = 0; l < 2; ++l) {
                            enlarged[i * 2 + k][j * 2 + l] = image[i][j];
                        }
                    }
                }
            }
            break;
        //second quad
        case (2):
            for (int i = 0; i < 128; ++i) {
                for (int j = 128; j < SIZE; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        for (int l = 0; l < 2; ++l) {
                            enlarged[i * 2 + k][(j - 128) * 2 + l] = image[i][j];
                        }
                    }
                }
            }
            break;
        //second quad
        case (3):
            for (int i = 128; i < SIZE; ++i) {
                for (int j = 0; j < 128; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        for (int l = 0; l < 2; ++l) {
                            enlarged[(i - 128) * 2 + k][j * 2 + l] = image[i][j];
                        }
                    }
                }
            }
            break;
        //second quad
        case (4):
            for (int i = 128; i < SIZE; ++i) {
                for (int j = 128; j < SIZE; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        for (int l = 0; l < 2; ++l) {
                            enlarged[(i - 128) * 2 + k][(j - 128) * 2 + l] = image[i][j];
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
    burnEffect(enlarged);
}

/*

for (int i = 1; i < SIZE - 1; ++i) {
for (int j = 1; j < SIZE - 1; ++j) {
if (image[i + 1][j + 1] < image[i][j])
image[i][j] = 0;
else
image[i][j] = 255;
}
}*/
