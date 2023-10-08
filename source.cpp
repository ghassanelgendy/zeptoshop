//Image Processor Project by:
//Ghassan Elgendy 20220239     E-Mail: Ghassanelgendyy@gmail.com
//Rowan Ammar     20220133     E-Mail: rawanehab523@gmail.com
//Jana Mohamed    20220470     E-Mail: janamohamedramadan335@gmail.com
//3/10/2023//
#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include <cmath>

#define br break;
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
    isIssue = false;
    welcomeScreen();
    loadImage(image);
    if (!isIssue) {
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
    (readGSBMP(imageFileName, img)) ? isIssue = true : readGSBMP(imageFileName, img);
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
    else if (c == 's' || c == 'S') {
        saveImage();
        cout << "Do you have another image to process? Y/N\n";
        unsigned char loop;
        cin >> loop;
        if (loop == 'y' || loop == 'Y') {
            main();
        } else {
            cout << "Bye.\n";
        }
    }
    return 0;
}

void getAverage(int &average) {

    int sum = 0;
    for (auto &i: image) {
        for (unsigned char &j: i) {
            sum += j;
        }
    }
    average = (sum / (SIZE * SIZE));
    // cout << "\t\t\t\t<----- FOR DEBUGGING I'M IN LINE (118) - Average contrast: <-----" << average << "\n";
}

int userChoice() {

    unsigned char choice;
    cout << "\t\t\t\t\t<----- Please choose what you wanna do ----->\n" <<
         "- 1. Black and white filter\n" <<
         "- 2. Invert filter\n" <<
         "- 3. Merge\n" <<
         "- 4. Flip\n" <<
         "- 5. Change brightness\n" <<
         "- 6. Rotate\n" <<
         "- 7. Detect edges\n" <<
         "- 8. Enlarge\n" <<
         "- 9. Shrink\n" <<
         "- A. Mirror\n" <<
         "- B. Add smart frame\n" <<
         "- C. Get average pixels contrast (advanced)\n" <<
         "- D. Shuffle\n" <<
         "- E. Blur\n" <<
         "- F. Crop\n" <<
         "- G. Skew\n" <<
         "- S. Save image to a file\n" <<
         "- 0. Exit :(\n";
    cin >> choice;
    choice = tolower(choice);
    switch (choice) {
        case ('1'):
            blackAndWhite(avg);
            break;
        case ('2'):
            invert();
            break;
        case ('3'):
            merge();
            break;
        case ('4'):
            flip();
            break;
        case ('5'):
            cout << "Choose (B) to brighten the image by 50%, (D) to darken it by 50%\n";
            unsigned char c;
            cin >> c;
            controlBrightness(c);
            break;
        case ('6'):
            rotationPrompt();
            break;
        case ('7'):
            detectEdges();
            break;
        case ('8'):
            enlarge();
            break;
        case ('9'):
            shrink();
            break;
        case ('a'):
            mirror();
            break;
        case ('b'):
            addFrame();
            break;
        case ('c'):
            cout << "Average pixels contrast = " << avg << '\n';
            break;
        case ('d'):
            shuffle();
            break;
        case ('e'):
            blur();
            break;
        case ('s'):
            saveImage();
            break;
        case ('f'):
            crop();
            break;
        case ('g'):
            skew();
            break;
        case ('0'):
            cout << "Bye.\n";
            return 0;
            break;
        default:
            cout << "Wrong entry<<\n";
            userChoice();

            break;
    }
    continuePrompt();
}

void invert() {

    for (auto &i: image) {
        for (unsigned char &j: i) {
            j = 255 - j;
        }
    }
}

void blackAndWhite(int &average) {
    for (auto &i: image) {
        for (unsigned char &j: i) {
            (j > average) ? j = 255 : j = 0;
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
    start:
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
    }
    else if (x == 'h' || x == 'H') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                flipped[i][j] = image[i][SIZE - 1 - j];
            }
        }
    }
    else{
        cout<<"please enter a valid input.\n";
        goto start;
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
    cout << "Enter degree of rotation: \n" <<
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
            cout << "?\n";
            rotationPrompt();
    }
}

void controlBrightness(unsigned char c) {
    (c == ('b' | 'B')) ? brighten() : darken();
}

void darken() {
    for (auto &i: image) {
        for (unsigned char &j: i) {
            j /= 2;
        }
    }
}

void brighten() {
    for (auto &i: image) {
        for (unsigned char &j: i) {
            j = (j + 255) / 2;
        }
    }
}

void detectEdges() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] >= avg) {
                if (image[i + 1][j] < avg
                    || image[i][j + 1] < avg) {
                    image[i][j] = 0;
                } else {
                    image[i][j] = 255;
                }
            } else {
                if (image[i + 1][j] >= avg
                    || image[i][j + 1] >= avg) {
                    image[i][j] = 0;
                } else {
                    image[i][j] = 255;
                }
            }
        }
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
    start :
    unsigned short x =0;
    unsigned char enlarged[SIZE][SIZE];
    cout << "Which quarter do you want to enlarge?\n";
    cin >> x;
    if (x < 0 || x > 4) {
        cout << "choose a quarter from 1-4 please\n";
        goto start;
    }
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
            //third quad
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
            //fourth quad
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

void shrink() {
    unsigned short scale;
    //declaring new image after apply
    unsigned char shrunk[SIZE][SIZE];
    cout << "At what scale?\n" <<
         "1. 1/2\n2. 1/3\n3. 1/4\n";
    cin >> scale;
    if (scale > 3) {
        cout << "Please i'm not a magician, choose a valid number.\n";
        shrink();
    } else {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                shrunk[i][j] = 255;
                shrunk[i / (scale + 1)][j / (scale + 1)] = image[i][j];
            }
        }
        burnEffect(shrunk);
    }
}

void mirror() {
    cout << "1. Left half\n2. Right half\n3. Upper half\n4. Lower half\n";
    unsigned short option;
    cin >> option;
    switch (option) {
        case (1):
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    image[i][j + 128] = image[i][127 - j];
                }
            }
            break;
        case (2):
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    image[i][127 - j] = image[i][j + 128];
                }
            }
            break;
        case (3):
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[i + 128][j] = image[127 - i][j];
                }
            }
            break;
        case (4):
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[127 - i][j] = image[i + 128][j];
                }
            }
            break;
        default:
            cout << "How??\n";
            mirror();
            break;
    }
}

void shuffle() {
    start:
    unsigned char shuffled[SIZE][SIZE];
    int quarter = 1;
    cout << "what order of quarters? \n";
    int order[4];
    for (int &i: order) {
        cin >> i;
        if (i < 0 || i > 4) {
            cout << "Please enter a valid order\n";
            goto start;
        }
    }
    for (int i: order) {
        switch (quarter) {
            case (1):
                for (int j = 0; j < 128; ++j) {
                    for (int k = 0; k < 128; ++k) {
                        switch (i) {
                            case (1):
                                shuffled[j][k] = image[j][k];
                                br
                            case (2):
                                shuffled[j][k] = image[j][k + 128];

                                br
                            case (3):
                                shuffled[j][k] = image[j + 128][k];
                                br
                            case (4):
                                shuffled[j][k] = image[j + 128][k + 128];
                        }
                    }
                }
                br
            case (2):
                for (int j = 0; j < 128; ++j) {
                    for (int k = 128; k < SIZE; ++k) {
                        switch (i) {
                            case (1):
                                shuffled[j][k] = image[j][k - 128];
                                br
                            case (2):
                                shuffled[j][k] = image[j][k];
                                br
                            case (3):
                                shuffled[j][k] = image[j + 128][k - 128];
                                br
                            case (4):
                                shuffled[j][k] = image[j + 128][k];
                        }
                    }
                }

                br
            case (3):
                for (int j = 128; j < SIZE; ++j) {
                    for (int k = 0; k < 128; ++k) {
                        switch (i) {
                            case (1):
                                shuffled[j][k] = image[j - 128][k];
                                br
                            case (2):
                                shuffled[j][k] = image[j - 128][k + 128];
                                br
                            case (3):
                                shuffled[j][k] = image[j][k];
                                br
                            case (4):
                                shuffled[j][k] = image[j][k + 128];

                        }
                    }
                }

                br
            case (4):
                for (int j = 128; j < SIZE; ++j) {
                    for (int k = 128; k < SIZE; ++k) {
                        switch (i) {
                            case (1):
                                shuffled[j][k] = image[j - 128][k - 128];
                                br
                            case (2):
                                shuffled[j][k] = image[j - 128][k];
                                br
                            case (3):
                                shuffled[j][k] = image[j][k - 128];
                                br
                            case (4):
                                shuffled[j][k] = image[j][k];

                        }
                    }
                }
                br
            default:
                br
        }
        quarter++;
    }
    burnEffect(shuffled);
}

void blur() {
    unsigned char blurred[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int sum = 0;
            for (int k = -5; k <= 5; ++k) {
                sum += image[i + k][j] + image[i][j + k];
            }
            blurred[i][j] = sum / 25;
        }
    }
    burnEffect(blurred);
}

void crop() {
    int x, y, l, w;
    cout << "enter x y l w\n";
    cin >> x >> y >> l >> w;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((i < y || i > (y + l)) || (j < x || j > (w + x)))
                image[i][j] = 255;
        }


    }
}

void skew() {
    unsigned char skewed[SIZE][SIZE];
    int angle;
    cin >> angle;
    int Rangle = angle * M_PI / 180;
    int side = tan(Rangle) * 256;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int x = i * tan(Rangle);
            skewed[i][j] = image[i][j];

        }

        for (int k = 0; k < side; ++k) {
            for (int j = 0; j < SIZE; ++j) {
                skewed[k][j] = 255;
            }
        }
        burnEffect(skewed);

    }
}








