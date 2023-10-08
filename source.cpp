//Image Processor Project by:
//Ghassan Elgendy 20220239    E-Mail: Ghassanelgendyy@gmail.com
//Rowan Ammar     20220133    E-Mail: rawanehab523@gmail.com
//Jana Mohamed    20220470    E-Mail: janamohamedramadan335@gmail.com
//3/10/2023//
#include <iostream>
#include "zeptolib/zeptolib.cpp"

using namespace std;

int main() {
    isIssue = false;
    welcomeScreen();
    loadImage(image, RGBImage);
    if (!isIssue) {
        getAverage(avg);
        imageInfo();

        userChoice();
    } else {
        cout << errorMsg;
        main();
    }
    return 0;
}
