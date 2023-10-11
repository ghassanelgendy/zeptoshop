//FCAI – OOP Programming – 2023 - Assignment #1 - Part 1
//Program Name: CS213-2023-2022047-20220133-20220239-A1-Part1.cpp
//Last Modification Date: 11/10/2023
//Ghassan Elgendy 20220239     E-Mail: Ghassanelgendyy@gmail.com
//Rowan Ammar     20220133     E-Mail: rawanehab523@gmail.com
//Jana Mohamed    20220470     E-Mail: janamohamedramadan335@gmail.com
//Purpose : photo editing app to apply different filters to greyscale and RGB (bonus) images
#include <iostream>
#include "zeptolib/zeptolib.cpp"
using namespace std;

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
