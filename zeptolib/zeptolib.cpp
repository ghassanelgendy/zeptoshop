//FCAI – OOP Programming – 2023 - Assignment #1 - Part 1
//Program Name: CS213-2023-2022047-20220133-20220239-A1-Part1.cpp
//Last Modification Date: 11/10/2023
//Ghassan Elgendy 20220239     E-Mail: Ghassanelgendyy@gmail.com
//Rowan Ammar     20220133     E-Mail: rawanehab523@gmail.com
//Jana Mohamed    20220470     E-Mail: janamohamedramadan335@gmail.com
//Purpose : photo editing app to apply different filters to greyscale and RGB (bonus) images
#include <iostream>
#include <cstring>
#include <vector>
#include "../bmplib.cpp"

#define usn unsigned short
#define usc unsigned char
#define br break;
using namespace std;
// error message
string errorMsg = "\t\t\t\t==> An unexpected error happened please try again! <==\n";
// declaring the matrix
usc image[SIZE][SIZE];
// declaring the 3D RGB matrix
usc RGBImage[SIZE][SIZE][RGB];
// boolean to catch logical errors
bool isIssue = false;
//prompt takes choice from user
void userChoice();
//boolean to decide what color mode is the image
bool isRGB;
// declaring the matrix for rotation
usc rotated[SIZE][SIZE];
usc rotatedRGB[SIZE][SIZE][RGB];
// initializing the average contrast for each pixel
unsigned int avg = 127;
//declaring filesize
unsigned int imageSize = 0;
void detectColorMode(const string &filename) {
    FILE *p_file;
    p_file = fopen(filename.c_str(), "rb");
    fseek(p_file, 0, SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    imageSize = size;
    if (size > 66666)
        isRGB = true;
    else
        isRGB = false;
}
//load image exists in same directory
void loadImage(usc img[SIZE][SIZE], usc RGBImg[SIZE][SIZE][RGB]) {

    char imageFileName[100];
    //  Get image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    //  Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    detectColorMode(imageFileName);
    if (isRGB) {
        readRGBBMP(imageFileName, RGBImg);
    } else {
        (readGSBMP(imageFileName, img)) ? isIssue = true : readGSBMP(imageFileName, img);
    }
    cout << '\n';

}
//applies the picked filter to the global image[SIZE][SIZE] matrix
void burnEffect(usc newImg[SIZE][SIZE], usc newRGBImg[SIZE][SIZE][RGB]) {
    if (isRGB) {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j)
                for (usn k = 0; k < RGB; ++k) {
                    RGBImage[i][j][k] = newRGBImg[i][j][k];
                }
        }
    } else {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j)
                image[i][j] = newImg[i][j];
        }
    }
}
//"black and white" filter
void blackAndWhite() {
    if (isRGB) {
        for (auto &i: RGBImage) {
            for (usn j = 0; j < SIZE; ++j) {
                usc grayscale = (i[j][0] + i[j][1] + i[j][2]) / 3;
                //  Set R, G, and B to the grayscale value
                for (usn k = 0; k < RGB; ++k) {
                    i[j][k] = grayscale;
                }
            }
        }
    } else {
        for (auto &i: image) {
            for (usc &j: i) {
                (j > avg) ? j = 255 : j = 0;
            }
        }
    }
}
//"invert" filter
void invert() {
    if (isRGB) {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                for (usn k = 0; k < RGB; ++k) {
                    RGBImage[i][j][k] = 255 - RGBImage[i][j][k];
                }
            }
        }
    } else {
        for (auto &i: image) {
            for (usc &j: i) {
                j = 255 - j;
            }
        }
    }
}
//merge two images
void merge() {
    cout << "Load the second image, ";
    usc secImage[SIZE][SIZE];
    usc secRGBImage[SIZE][SIZE][RGB];
    loadImage(secImage, secRGBImage);
    if (isRGB) {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                for (usn k = 0; k < RGB; ++k) {
                    RGBImage[i][j][k] = (RGBImage[i][j][k] + secRGBImage[i][j][k]) / 2;
                }
            }
        }
    } else {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                image[i][j] = (image[i][j] + secImage[i][j]) / 2;
            }
        }
    }
}
//flip image in two axes
void flip() {
    cout << "(V) to flip vertically, (H) to flip horizontally\n";
    usc flipped[SIZE][SIZE];
    usc flippedRGB[SIZE][SIZE][RGB];
    char x;
    cin >> x;
    if (isRGB) {
        if (x == 'v' || x == 'V') {
            for (usn i = 0; i < SIZE; ++i) {
                for (usn j = 0; j < SIZE; ++j) {
                    for (usn k = 0; k < RGB; ++k)
                        flippedRGB[i][j][k] = RGBImage[SIZE - 1 - i][j][k];
                }
            }
        } else {
            for (usn i = 0; i < SIZE; ++i) {
                for (usn j = 0; j < SIZE; ++j) {
                    for (usn k = 0; k < RGB; ++k)
                        flippedRGB[i][j][k] = RGBImage[i][SIZE - 1 - j][k];
                }
            }
        }
    } else {
        if (x == 'v' || x == 'V') {
            for (usn i = 0; i < SIZE; ++i) {
                for (usn j = 0; j < SIZE; ++j) {
                    flipped[i][j] = image[SIZE - 1 - i][j];
                }
            }
        } else {
            for (usn i = 0; i < SIZE; ++i) {
                for (usn j = 0; j < SIZE; ++j) {
                    flipped[i][j] = image[i][SIZE - 1 - j];
                }
            }
        }
    }
    burnEffect(flipped, flippedRGB);
}
//increase image brightness by 50%
void brighten() {
    if (isRGB) {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                for (usn k = 0; k < RGB; ++k) {
                    RGBImage[i][j][k] = (RGBImage[i][j][k] + 255) / 2;

                }
            }
        }
    } else {
        for (auto &i: image) {
            for (usc &j: i) {
                j = (j + 255) / 2;
            }
        }
    }

}
//decrease image brightness by 50%
void darken() {
    if (isRGB) {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                for (usn k = 0; k < RGB; ++k) {
                    RGBImage[i][j][k] = (RGBImage[i][j][k]) /= 2;

                }
            }
        }
    } else {
        for (auto &i: image) {
            for (usc &j: i) {
                j /= 2;
            }
        }
    }
}
// controlling image brightness
void controlBrightness() {
    cout << "Choose (B) to brighten the image by 50%, (D) to darken it by 50%\n";
    usc c;
    cin >> c;
    (c == ('b' | 'B')) ? brighten() : darken();
}
//displays image info
void imageInfo() {
    cout << "\t\t\t\t\t\t  === Image info ===\ncolor mode: " << (isRGB ? "RGB" : "grayscale")
         << "\nimage average contrast: " << avg
         << "\nfile size: " << imageSize / 1024
         << "KB\n\t\t\t\t\t  === Have fun and get creative! ===\n\n";
}
//save image in same directory
void saveImage() {

    char imageFileName[100];

    //  Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    //  Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    if (isRGB) {
        writeRGBBMP(imageFileName, RGBImage);

    } else {

        writeGSBMP(imageFileName, image);
    }
    cout << '\n';
}
//rotates the image
void rotate(short time) {
    for (usn k = 0; k < time; ++k) {
        if (isRGB) {
            {
                for (usn i = 0; i < SIZE; ++i) {
                    for (usn j = 0; j < SIZE; ++j) {
                        for (usn l = 0; l < RGB; ++l) {
                            rotatedRGB[i][j][l] = RGBImage[j][SIZE - 1 - i][l];
                        }
                    }
                }
                burnEffect(rotated, rotatedRGB);
            }
        } else {
            for (usn i = 0; i < SIZE; ++i) {
                for (usn j = 0; j < SIZE; ++j) {
                    rotated[i][j] = image[j][SIZE - 1 - i];
                }
                burnEffect(rotated, rotatedRGB);
            }
        }
    }
}
//function to generate average contrast for image
void getAverage(unsigned int &average) {
    unsigned int sum = 0;
    if (isRGB) {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                usc grayscale = (RGBImage[i][j][0] + RGBImage[i][j][1] + RGBImage[i][j][2]) / 3;
                sum += grayscale;
            }
        }
        average = sum / (SIZE * SIZE);
    } else {
        for (auto &i: image) {
            for (usc &j: i) {
                sum += j;
            }
        }
        average = sum / (SIZE * SIZE);
    }
}
//prompt user for rotation degree
void rotationPrompt() {
    startRotateLabel:
    cout << "Enter degrees of rotation: \n" <<
         "1. 90\n2. 180\n3. 270\n";
    short x;
    cin >> x;
    if (x > 3) goto startRotateLabel;
    rotate(x);
}
//detect edges of an object
void detectEdges() {
    if (isRGB) {
        blackAndWhite();
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                image[i][j] = RGBImage[i][j][2];
            }
        }
    }
    isRGB = false;
    for (usn i = 0; i < SIZE; i++) {
        for (usn j = 0; j < SIZE; j++) {
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
//optional filter
void addFrame() {
    unsigned short clr = 255;
    if (isRGB) {
        if (avg > 128) clr = 0;
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                if (i <= 5 || j <= 5 || i > 250 || j > 250) {
                    for (usn k = 0; k < RGB; ++k) {
                        RGBImage[i][j][k] = clr;
                    }
                }
            }
        }
    } else {
        if (avg > 128) clr = 0;
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                if (i <= 5 || j <= 5 || i > 250 || j > 250) {
                    image[i][j] = clr;
                }
            }
        }
    }
}
//enlarge chosen quarter by scale 4x
void enlarge() {
    unsigned short x;
    usc enlarged[SIZE][SIZE];
    usc enlargedRGB[SIZE][SIZE][RGB];

    cout << "Which quarter do you want to enlarge?\n";
    cin >> x;
    if (isRGB) {
        switch (x) {
            // first quad
            case (1):
                for (usn i = 0; i < 128; ++i) {
                    for (usn j = 0; j < 128; ++j) {
                        for (usn k = 0; k < 2; ++k) {
                            for (usn l = 0; l < 2; ++l) {
                                for (usn m = 0; m < RGB; ++m) {
                                    enlargedRGB[i * 2 + k][j * 2 + l][m] = RGBImage[i][j][m];
                                }
                            }
                        }
                    }
                }
                br
                // second quad
            case (2):
                for (usn i = 0; i < 128; ++i) {
                    for (usn j = 128; j < SIZE; ++j) {
                        for (usn k = 0; k < 2; ++k) {
                            for (usn l = 0; l < 2; ++l) {
                                for (usn m = 0; m < RGB; ++m) {
                                    enlargedRGB[i * 2 + k][(j - 128) * 2 + l][m] = RGBImage[i][j][m];

                                }
                            }
                        }
                    }
                }
                br
                // third quad
            case (3):
                for (usn i = 128; i < SIZE; ++i) {
                    for (usn j = 0; j < 128; ++j) {
                        for (usn k = 0; k < 2; ++k) {
                            for (usn l = 0; l < 2; ++l) {
                                for (usn m = 0; m < RGB; ++m) {
                                    enlargedRGB[(i - 128) * 2 + k][j * 2 + l][m] = RGBImage[i][j][m];
                                }

                            }
                        }
                    }
                }
                br
                // fourth quad
            case (4):
                for (usn i = 128; i < SIZE; ++i) {
                    for (usn j = 128; j < SIZE; ++j) {
                        for (usn k = 0; k < 2; ++k) {
                            for (usn l = 0; l < 2; ++l) {
                                for (usn m = 0; m < RGB; ++m) {
                                    enlargedRGB[(i - 128) * 2 + k][(j - 128) * 2 + l][m] = RGBImage[i][j][m];
                                }
                            }
                        }
                    }
                }
                br
            default:
                br
        }
    } else {
        switch (x) {
            // first quad
            case (1):
                for (usn i = 0; i < 128; ++i) {
                    for (usn j = 0; j < 128; ++j) {
                        for (usn k = 0; k < 2; ++k) {
                            for (usn l = 0; l < 2; ++l) {
                                enlarged[i * 2 + k][j * 2 + l] = image[i][j];
                            }
                        }
                    }
                }
                br
                // second quad
            case (2):
                for (usn i = 0; i < 128; ++i) {
                    for (usn j = 128; j < SIZE; ++j) {
                        for (usn k = 0; k < 2; ++k) {
                            for (usn l = 0; l < 2; ++l) {
                                enlarged[i * 2 + k][(j - 128) * 2 + l] = image[i][j];
                            }
                        }
                    }
                }
                br
                // third quad
            case (3):
                for (usn i = 128; i < SIZE; ++i) {
                    for (usn j = 0; j < 128; ++j) {
                        for (usn k = 0; k < 2; ++k) {
                            for (usn l = 0; l < 2; ++l) {
                                enlarged[(i - 128) * 2 + k][j * 2 + l] = image[i][j];
                            }
                        }
                    }
                }
                br
                // fourth quad
            case (4):
                for (usn i = 128; i < SIZE; ++i) {
                    for (usn j = 128; j < SIZE; ++j) {
                        for (usn k = 0; k < 2; ++k) {
                            for (usn l = 0; l < 2; ++l) {
                                enlarged[(i - 128) * 2 + k][(j - 128) * 2 + l] = image[i][j];
                            }
                        }
                    }
                }
                br
            default:
                br
        }
    }
    burnEffect(enlarged, enlargedRGB);

}
//shrink image by a desired scale
void shrink() {
    startShrinkLabel:
    unsigned short scale;
    // declaring new image after apply
    usc shrunk[SIZE][SIZE];
    usc shrunkRGB[SIZE][SIZE][RGB];
    cout << "At what scale?\n" <<
         "1. 1/2\n2. 1/3\n3. 1/4\n";
    cin >> scale;
    if (scale > 3) {
        cout << "Please i'm not a magician, choose a valid number.\n";
        goto startShrinkLabel;
    } else {
        if (isRGB) {
            for (usn i = 0; i < SIZE; ++i) {
                for (usn j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        shrunkRGB[i][j][k] = 255;
                        shrunkRGB[i / (scale + 1)][j / (scale + 1)][k] = RGBImage[i][j][k];
                    }

                }
            }
        } else {
            for (usn i = 0; i < SIZE; ++i) {
                for (usn j = 0; j < SIZE; ++j) {
                    shrunk[i][j] = 255;
                    shrunk[i / (scale + 1)][j / (scale + 1)] = image[i][j];
                }
            }
        }

        burnEffect(shrunk, shrunkRGB);
    }
}
//mirrors chosen half of the imagw
void mirror() {
    startMirrorLabel:
    cout << "1. Left half\n2. Right half\n3. Upper half\n4. Lower half\n";
    unsigned short option;
    cin >> option;
    if (isRGB) {
        switch (option) {
            case (1):
                for (auto &i: RGBImage) {
                    for (usn j = 0; j < SIZE / 2; ++j) {
                        for (int k = 0; k < RGB; ++k) {
                            i[j + 128][k] = i[127 - j][k];
                        }
                    }
                }
                br
            case (2):
                for (auto &i: RGBImage) {
                    for (usn j = 0; j < SIZE / 2; ++j) {
                        for (int k = 0; k < RGB; ++k) {
                            i[127 - j][k] = i[j + 128][k];
                        }
                    }
                }
                br
            case (3):
                for (usn i = 0; i < SIZE / 2; ++i) {
                    for (usn j = 0; j < SIZE; ++j) {
                        for (int k = 0; k < RGB; ++k) {
                            RGBImage[i + 128][j][k] = RGBImage[127 - i][j][k];
                        }
                    }
                }
                br
            case (4):
                for (usn i = 0; i < SIZE / 2; ++i) {
                    for (usn j = 0; j < SIZE; ++j) {
                        for (int k = 0; k < RGB; ++k) {
                            RGBImage[127 - i][j][k] = RGBImage[i + 128][j][k];
                        }
                    }
                }
                br
            default:
                cout << errorMsg;
                goto startMirrorLabel;
                br
        }
    } else {
        switch (option) {
            case (1):
                for (auto &i: image) {
                    for (usn j = 0; j < SIZE / 2; ++j) {
                        i[j + 128] = i[127 - j];
                    }
                }
                br
            case (2):
                for (auto &i: image) {
                    for (usn j = 0; j < SIZE / 2; ++j) {
                        i[127 - j] = i[j + 128];
                    }
                }
                br
            case (3):
                for (usn i = 0; i < SIZE / 2; ++i) {
                    for (usn j = 0; j < SIZE; ++j) {
                        image[i + 128][j] = image[127 - i][j];
                    }
                }
                br
            case (4):
                for (usn i = 0; i < SIZE / 2; ++i) {
                    for (usn j = 0; j < SIZE; ++j) {
                        image[127 - i][j] = image[i + 128][j];
                    }
                }
                br
            default:
                cout << errorMsg;
                goto startMirrorLabel;
                br
        }
    }
}
//shuffles quarters of the image
void shuffle() {
    startShuffleLabel:
    usc shuffled[SIZE][SIZE];
    usc shuffledRGB[SIZE][SIZE][RGB];
    usn quarter = 1;
    cout << "what order of quarters? \n";
    usn order[4];
    for (usn &i: order) {
        cin >> i;
    }
    if (isRGB) {
        for (usn i: order) {
            switch (quarter) {
                case (1):
                    for (usn j = 0; j < 128; ++j) {
                        for (usn k = 0; k < 128; ++k)
                            for (usn g = 0; g < RGB; g++) {
                                switch (i) {
                                    case (1):
                                        shuffledRGB[j][k][g] = RGBImage[j][k][g];
                                        br
                                    case (2):
                                        shuffledRGB[j][k][g] = RGBImage[j][k + 128][g];

                                        br
                                    case (3):
                                        shuffledRGB[j][k][g] = RGBImage[j + 128][k][g];
                                        br
                                    case (4):
                                        shuffledRGB[j][k][g] = RGBImage[j + 128][k + 128][g];
                                        br
                                    default:
                                        cout << errorMsg;
                                }
                            }
                    }
                    br

                case (2):
                    for (usn j = 0; j < 128; ++j) {
                        for (usn k = 128; k < SIZE; ++k)
                            for (usn g = 0; g < RGB; g++) {
                                switch (i) {
                                    case (1):
                                        shuffledRGB[j][k][g] = RGBImage[j][k - 128][g];
                                        br
                                    case (2):
                                        shuffledRGB[j][k][g] = RGBImage[j][k][g];
                                        br
                                    case (3):
                                        shuffledRGB[j][k][g] = RGBImage[j + 128][k - 128][g];
                                        br
                                    case (4):
                                        shuffledRGB[j][k][g] = RGBImage[j + 128][k][g];
                                        br
                                    default:
                                        cout << errorMsg;
                                }
                            }
                    }

                    br

                case (3):
                    for (usn j = 128; j < SIZE; ++j) {
                        for (usn k = 0; k < 128; ++k)
                            for (usn g = 0; g < RGB; g++) {
                                switch (i) {
                                    case (1):
                                        shuffledRGB[j][k][g] = RGBImage[j - 128][k][g];
                                        br
                                    case (2):
                                        shuffledRGB[j][k][g] = RGBImage[j - 128][k + 128][g];
                                        br
                                    case (3):
                                        shuffledRGB[j][k][g] = RGBImage[j][k][g];
                                        br
                                    case (4):
                                        shuffledRGB[j][k][g] = RGBImage[j][k + 128][g];
                                        br
                                    default:
                                        cout << errorMsg;

                                }
                            }
                    }
                    br

                case (4):
                    for (usn j = 128; j < SIZE; ++j) {
                        for (usn k = 128; k < SIZE; ++k)
                            for (usn g = 0; g < RGB; g++) {
                                switch (i) {
                                    case (1):
                                        shuffledRGB[j][k][g] = RGBImage[j - 128][k - 128][g];
                                        br
                                    case (2):
                                        shuffledRGB[j][k][g] = RGBImage[j - 128][k][g];
                                        br
                                    case (3):
                                        shuffledRGB[j][k][g] = RGBImage[j][k - 128][g];
                                        br
                                    case (4):
                                        shuffledRGB[j][k][g] = RGBImage[j][k][g];
                                        br
                                    default:
                                        cout << errorMsg;
                                }
                            }
                    }
                    br
                default:
                    goto startShuffleLabel;
                    br
            }
            quarter++;
        }
    } else {
        for (usn i: order) {
            switch (quarter) {
                case (1):
                    for (usn j = 0; j < 128; ++j) {
                        for (usn k = 0; k < 128; ++k) {
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
                                    br
                                default:
                                    cout << errorMsg;
                            }
                        }
                    }
                    br

                case (2):
                    for (usn j = 0; j < 128; ++j) {
                        for (usn k = 128; k < SIZE; ++k) {
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
                                    br
                                default:
                                    cout << errorMsg;
                            }
                        }
                    }

                    br

                case (3):
                    for (usn j = 128; j < SIZE; ++j) {
                        for (usn k = 0; k < 128; ++k) {
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
                                    br
                                default:
                                    cout << errorMsg;

                            }
                        }
                    }
                    br

                case (4):
                    for (usn j = 128; j < SIZE; ++j) {
                        for (usn k = 128; k < SIZE; ++k) {
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
                                    br
                                default:
                                    cout << errorMsg;
                            }
                        }
                    }
                    br
                default:
                    goto startShuffleLabel;
                    br
            }
            quarter++;
        }
    }

    burnEffect(shuffled, shuffledRGB);
}
//blurs the image
void blur() {
    usc blurred[SIZE][SIZE];
    usc blurredRGB[SIZE][SIZE][RGB];
    if (isRGB) {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                for (usn k = 0; k < RGB; ++k) {
                    blurredRGB[i][j][k] = (RGBImage[i][j][k] +
                                           RGBImage[i + 1][j][k] + RGBImage[i][j + 1][k] + RGBImage[i - 1][j][k] +
                                           RGBImage[i][j - 1][k] +
                                           RGBImage[i + 2][j][k] + RGBImage[i][j + 2][k] + RGBImage[i - 2][j][k] +
                                           RGBImage[i][j - 2][k] +
                                           RGBImage[i + 3][j][k] + RGBImage[i][j + 3][k] + RGBImage[i - 3][j][k] +
                                           RGBImage[i][j - 3][k] +
                                           RGBImage[i + 4][j][k] + RGBImage[i][j + 4][k] + RGBImage[i - 4][j][k] +
                                           RGBImage[i + 5][j][k] + RGBImage[i][j + 5][k] + RGBImage[i - 5][j][k]) / 25;
                }
            }
        }
    } else {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                blurred[i][j] = (image[i][j] +
                                 image[i + 1][j] + image[i][j + 1] + image[i - 1][j] + image[i][j - 1] +
                                 image[i + 2][j] + image[i][j + 2] + image[i - 2][j] + image[i][j - 2] +
                                 image[i + 3][j] + image[i][j + 3] + image[i - 3][j] + image[i][j - 3] +
                                 image[i + 4][j] + image[i][j + 4] + image[i - 4][j] +
                                 image[i + 5][j] + image[i][j + 5] + image[i - 5][j]) / 25;

            }
        }
    }

    burnEffect(blurred, blurredRGB);
}
//crops the image from desired point with desired dimensions
void crop() {
    usn x, y, l, w;
    cout << "Enter point on x-axis, y-axis , length and width\n";
    cin >> x >> y >> l >> w;
    if (isRGB) {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                for (usn k = 0; k < RGB; ++k) {
                    if ((i < y || i > (y + l)) || (j < x || j > (w + x)))
                        RGBImage[i][j][k] = 255;
                }
            }
        }
    } else {
        for (usn i = 0; i < SIZE; ++i) {
            for (usn j = 0; j < SIZE; ++j) {
                if ((i < y || i > (y + l)) || (j < x || j > (w + x)))
                    image[i][j] = 255;
            }
        }
    }

}
//displays the average contrast
void displayAveragePixelContrast() {
    cout << "Average pixels contrast = " << avg << '\n';
}
//prompt user to continue editing or save
void continuePrompt() {
    cout << "\t\t\t\t\t===  Do you want to save or do something else? ===\n" <<
         "(S) to save, (D) to do something else, [write name of output file to quick save!]\n->";
    char outputFileName[50];
    cin >> outputFileName;
    if (outputFileName[0] == 'd' || outputFileName[0] == 'D')
        userChoice();
    else if (outputFileName[0] == 's' || outputFileName[0] == 'S') {
        saveImage();
        cout << "Do you have another image to process? Y/N\n";
        usc loop;
        cin >> loop;
        if (loop == 'y' || loop == 'Y') {
            loadImage(image, RGBImage);
            getAverage(avg);
            imageInfo();
            userChoice();
        } else {
            cout << "Bye.\n";
            abort();
        }
    }
    strcat(outputFileName, ".bmp");
    (isRGB) ? writeRGBBMP(outputFileName, RGBImage) :
    writeGSBMP(outputFileName, image);
}
//main features of the project
void displayFeatures() {
    cout << "\t\t\t\t\tzepto-\n"
            "\ta combining form (denoting a factor of 10) meaning 'one sextillionth'\n"
            "\t\t Basically it's photoshop but in zepto scale\n\n\n"
            "Features -> "
            "15 required filters + additional filters as follows\n"
            "- Mode auto detection : detects image color more (RGB or grayscale) to apply the correct algorithm\n"
            "- Smart frame: generates frame color depending on average image contrast.\n"
            "- Error handling : keeps asking the user for valid input\n"
            "- Quick save mode : takes user input as filename for quick save\n\n"
            "\t\tThis amazing project was made possible by\n"
            "\tGhassan Elgendy \t\tgithub: ghassanelgendy\n"
            "\tRowan Ammar     \t\tgithub: rowanammar\n"
            "\tJana Mohamed    \t\tgithub: janaramadan\n" //xDDD
            "\t   As assignment for Dr.Mohamed Elramly FCAI-CU\n";

}
void skew(){
    if(isRGB){
        cout<<"Ana skewed";
    }
    else{
        cout<<"Ana kman bs GS";
    }
}
//start point of the project
void userChoice() {
    cout << "\t\t\t\t\t=== Please choose what you wanna do ===\n" <<
         "- 1. Black and white filter\n" << //done
         "- 2. Invert filter\n" <<          //done
         "- 3. Merge\n" <<                  //done
         "- 4. Flip\n" <<                   //done
         "- 5. Change brightness\n" <<      //done
         "- 6. Rotate\n" <<                 //done
         "- 7. Detect edges\n" <<           //done
         "- 8. Enlarge\n" <<                //done
         "- 9. Shrink\n" <<                 //done
         "- A. Mirror\n" <<                 //done
         "- B. Add smart frame\n" <<        //done
         "- C. Get average pixels contrast (advanced)\n" << //done
         "- D. Shuffle\n" <<                //done
         "- E. Blur\n" <<                   //done
         "- F. Crop\n" <<                   //done
         "- G. Skew\n" <<                   //lol
         "- H. Help & tutorials\n" <<       //done
         "- I. Credits\n" <<                //done
         "- J. Save image to a file\n" <<   //done
         "- 0. Exit :(\n"                   //obv done
         "->";
    std::vector<void (*)()> funPointers = {
            abort, blackAndWhite, invert, merge, flip, // abort() terminates with code 3.
            controlBrightness, rotationPrompt,
            detectEdges, enlarge, shrink, mirror,
            addFrame, displayAveragePixelContrast,
            shuffle, blur, crop, skew, displayFeatures, saveImage
    };
    usc choiceNumber;
    startUserChoiceLabel:
    cin >> choiceNumber;
    usn choice = tolower(choiceNumber);
    if (choice >= '0' && choice <= '9' || choice >= 'a' && choice <= 'j') {
        (choice >= 97) ?
        funPointers[choice - 87]() : // handle the letters
        funPointers[choice - 48]();  // handle the numbers
    } else {
        cout << "Please, choose a valid option!\n";
        goto startUserChoiceLabel;
    }
    continuePrompt();
}