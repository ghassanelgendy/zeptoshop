//Image Processor Project by:
//Ghassan Elgendy 20220239     E-Mail: Ghassanelgendyy@gmail.com
//Rowan Ammar     20220133     E-Mail: rawanehab523@gmail.com
//Jana Mohamed    20220470     E-Mail: janamohamedramadan335@gmail.com
//3/10/2023//
#include <iostream>
#include <cstring>
#include "../bmplib.cpp"

#define br break;

using namespace std;
//error message
string errorMsg = "\t\t\t\t==> An unexpected error happened please try again! <==\n";
//declaring the matrix
unsigned char image[SIZE][SIZE];
//declaring the 3D RGB matrix
unsigned char RGBImage[SIZE][SIZE][RGB];
//boolean to catch logical errors
bool isIssue = false;

bool isRGB;
//declaring the matrix for rotation
unsigned char rotated[SIZE][SIZE];

void burnEffect(unsigned char newImg[SIZE][SIZE]);

void brighten();

void darken();

//initializing the average contrast for each pixel
int avg = 127;

int RGBAvg = 128;

int iSize=0;

int continuePrompt();

void imageInfo() {
    cout << "\t\t\t\t\t\t  === Image info ===\ncolor mode: " << (isRGB ? "RGB" : "grayscale") << "\nimage average contrast: "<< avg
         << "\nfile size: "<<iSize/1024
         << "KB\n\t\t\t\t\t  === Have fun and get creative! ===\n\n";

}

void detectColorMode(string filename) {
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(), "rb");
    fseek(p_file, 0, SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    iSize = size;
    if (size > 66666)
        isRGB = true;
    else
        isRGB = false;

}

void loadImage(unsigned char img[SIZE][SIZE], unsigned char RGBImg[SIZE][SIZE][RGB]) {

    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    detectColorMode(imageFileName);
    if (isRGB) {
        readRGBBMP(imageFileName, RGBImg);
    } else {
        (readGSBMP(imageFileName, img)) ? isIssue = true : readGSBMP(imageFileName, img);
    }
    cout << '\n';

}

void saveImage() {

    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    if (isRGB) {
        writeRGBBMP(imageFileName, RGBImage);

    } else {

        writeGSBMP(imageFileName, image);
    }
    cout << '\n';

}

void welcomeScreen() {

    cout << "\t\t\t\t=== Welcome to ZETOSHOP: The Who Needs 'Em Edition ===\n";
}

void getAverage(int &average) {
    int sum = 0;
    if(isRGB) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                unsigned char grayscale = (RGBImage[i][j][0] + RGBImage[i][j][1] + RGBImage[i][j][2]) / 3;
                sum+=grayscale;
            }
        }
        average = sum / (SIZE * SIZE) ;
    }
    else{
        for (auto &i: image) {
            for (unsigned char &j: i) {
                sum += j;
            }
        }
        average = sum / (SIZE * SIZE);
        // cout << "\t\t\t\t<----- FOR DEBUGGING I'M IN LINE (118) - Average contrast: <-----" << average << "\n";
    }
}

void invert() {

    for (auto &i: image) {
        for (unsigned char &j: i) {
            j = 255 - j;
        }
    }
}

void blackAndWhite(int &average) {
    if (isRGB) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                unsigned char grayscale = (RGBImage[i][j][0] + RGBImage[i][j][1] + RGBImage[i][j][2]) / 3;
                // Set R, G, and B to the grayscale value
                for (int k = 0; k < RGB; ++k) {
                    RGBImage[i][j][k] = grayscale;
                }
            }
        }
    } else {
        for (auto &i: image) {
            for (unsigned char &j: i) {
                (j > average) ? j = 255 : j = 0;
            }
        }
    }
}

void merge() {
    cout << "Load the second image, ";
    unsigned char secImage[SIZE][SIZE];
    unsigned char secRGBImage[SIZE][SIZE][RGB];
    loadImage(secImage, secRGBImage);
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
         "1. 90\n 2. 180\n 3. 270\n";
    short x;
    cin >> x;
    rotate(x);
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
    unsigned short x;
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
    startShrink:
    unsigned short scale;
    //declaring new image after apply
    unsigned char shrunk[SIZE][SIZE];
    cout << "At what scale?\n" <<
         "1. 1/2\n2. 1/3\n3. 1/4\n";
    cin >> scale;
    if (scale > 3) {
        cout << "Please i'm not a magician, choose a valid number.\n";
        goto startShrink;
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
            for (auto &i: image) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    i[j + 128] = i[127 - j];
                }
            }
            break;
        case (2):
            for (auto &i: image) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    i[127 - j] = i[j + 128];
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
            break;
    }
}

void shuffle() {
    unsigned char shuffled[SIZE][SIZE];
    int quarter = 1;
    cout << "what order of quarters? \n";
    int order[4];
    for (int &i: order) {
        cin >> i;
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
                                br
                            default:
                                cout << errorMsg;
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
                                br
                            default:
                                cout << errorMsg;
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
                                br
                            default:
                                cout << errorMsg;

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
                                br
                            default:
                                cout << errorMsg;

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
            blurred[i][j] = (image[i][j] +
                             image[i + 1][j] + image[i][j + 1] + image[i - 1][j] + image[i][j - 1] +
                             image[i + 2][j] + image[i][j + 2] + image[i - 2][j] + image[i][j - 2] +
                             image[i + 3][j] + image[i][j + 3] + image[i - 3][j] + image[i][j - 3] +
                             image[i + 4][j] + image[i][j + 4] + image[i - 4][j] +
                             image[i + 5][j] + image[i][j + 5] + image[i - 5][j]) / 25;

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

int userChoice() {

    unsigned char choice;
    cout << "\t\t\t\t\t=== Please choose what you wanna do ===\n" <<
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
         "- S. Save image to a file\n" <<
         "- 0. Exit :(\n"
         "-> \t";
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
            shuffle();
            break;
        case ('0'):
            cout << "Bye.\n";
            return 0;
        default:
            cout << "Wrong entry<<\n";
            userChoice();
            break;
    }
    continuePrompt();
    return 0;
}

int continuePrompt() {

    cout << "\t\t\t\t\t===  Do you want to save or do something else? ===\n" <<
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
            loadImage(image, RGBImage);
            getAverage(avg);
            userChoice();
        } else {
            cout << "Bye.\n";
        }
    }
    return 0;
}
