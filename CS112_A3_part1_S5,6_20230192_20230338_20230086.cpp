/*
************ Explain the code *************

  This program is a command-line image editing tool with various functionalities
  like grayscale conversion, darkening/lightening, cropping, rotating, merging, and inverting colors
  It utilizes a custom image class for image manipulation.
    In code : -
    you will find the initial functions (( check the name and save image as you want ))
    and the Filters functions

  Note  (( in merge function you must save changes in a new image )) .

************** Team details ***************
  Badr Eldeen Khaled Ghareeb Said    /   ID : 20230086
  Mohamed Reven Mohamed Hazem        /   ID : 20230338
  Shehab Eldin Ahmed Ezzat Younis    /   ID : 20230192

  (( We all in S5 , S6 ))

************ Who Do Any Filter ************

   Badr Eldeen ==> gray_scale  ,  Merge
   Mohamed Reven ==>  Rotator  ,  Inverter
   Shehab  ==> darken_lighten  ,  Crop

*/
#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include "Image_Class.h"
using namespace std ;
/* Initial variable that when call ( check name function ) to search if the image we will filter it
 if in the directory or not  ,And when calling it when saving changes in new image not check this case
*/
bool Save_InNewImage_Mode ;


string Check_Image_Name(string name , bool Save_InNewImage_Mode) {
    regex pattern(R"(^[^\n\\/:*?"<>|]+\.((jpg)|(jpeg)|(png)|(bmp)|(tga))$)");
    smatch match;

    while (true) {
        cout << "=================================================================\n"
             << "Enter the image file name : - \n"
             << "=================================================================\n";
        getline(cin, name);

        if (regex_match(name, pattern)) {

            if ( Save_InNewImage_Mode == true ){ // if function called in save changing in new image
                return name ;
            }
            // Convert the file name to lowercase
            transform(name.begin(), name.end(), name.begin(), ::tolower);

            // Check if the file exists
            ifstream file(name.c_str());
            if (!file) {
                cout << "File does not exist ( Please include image from the directory )" << endl;
                continue;
            }
            file.close(); // Close the file after checking
            return name ;
        }
        else {
            cout << "(Enter a valid format or fill the image name with any character) \n";
            continue;
        }
    }
}
void Save_Image ( string name  , Image &photo ){  // name is the name of the foto before Editing

    string input ;
    cout << "=================================================================\n"
            "Choose The Type Of Saving : -\n"
            "1) Save changes in the current Image \n"
            "2) Save in a new Image \n"
            "=================================================================\n" ;
    getline (cin , input ) ;
    while (true){
        if ( input == "1"){
            photo.saveImage(name ) ;
            break ;
        }
        else if ( input == "2"){

            string New_name ;
            Save_InNewImage_Mode = true ;       //  to do not check if the new image if in the directory or not
            New_name = Check_Image_Name( New_name , Save_InNewImage_Mode ) ;
            Image New_foto ( photo.width , photo.height) ;
            for (int i = 0; i < photo.width; i++) {
                for (int j = 0; j < photo.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        New_foto(i, j, k) = photo(i, j, k);
                    }
                }
            }
            New_foto.saveImage(New_name) ;
            break;
        }
        else {
            cout << " (( Enter a valid input )) \n" ;
            continue;
        }
    }
}

// Filter Functions
void gray_scale (){
    string foto_befor  ;
    Save_InNewImage_Mode = false ;
    foto_befor = Check_Image_Name( foto_befor , Save_InNewImage_Mode ) ;

    Image photo (foto_befor) ;          // To make gray scale filter
    for ( int i = 0 ; i < photo.width ; i ++){
        for (int j = 0 ; j < photo.height ; j ++){
            unsigned int avg = 0 ;
            for ( int k = 0 ; k < photo.channels ; k++ ){
                avg += photo(i, j ,k) ;
            }
            for ( int k = 0 ; k < photo.channels ; k++ ) {
                photo (i , j , k ) = avg / 3 ;
            }
        }
    }

    Save_Image(foto_befor ,photo ) ;
}

void darken_lighten (){
    string foto_befor  ;
    Save_InNewImage_Mode = false ;
    foto_befor = Check_Image_Name( foto_befor , Save_InNewImage_Mode ) ;

    while ( true ){
        string input ;
        cout << "==================================================\n"
                "What you want to do ? \n"
                "1) Darken \n"
                "2) Lighten \n"
                "==================================================\n" ;
        getline( cin , input ) ;
        Image photo (foto_befor) ;

        if ( input == "1"){                          // To Darken Filter
            for ( int i = 0 ; i < photo.width ; i ++){
                for (int j = 0 ; j < photo.height ; j ++){
                    for ( int k = 0 ; k < photo.channels ; k++ ){
                        photo ( i , j , k ) /= 2 ;
                    }
                }
            }
            Save_Image(foto_befor , photo ) ;
            break ;
        }
        else if ( input == "2"){                                // To lighten Filter
            for ( int i = 0 ; i < photo.width ; i ++){
                for (int j = 0 ; j < photo.height ; j ++){
                    for ( int k = 0 ; k < photo.channels ; k++ ){
                        photo(i, j, k) * 1.5 ;
                        if ( photo(i, j, k) >= 170  ){          //   170 + 170 /2 = 255
                            photo(i, j, k) = 255;
                        }
                    }
                }
            }
            Save_Image(foto_befor , photo ) ;
            break ;
        }
        else {
            cout << "(( Enter a valid input )) \n" ;
            continue ;
        }
    }
}

void Just_Crop ( int rows , int cols , Image &photo){
    Image temp_photo ( rows , cols ) ;
    for ( int i = 0 ; i < rows ; i ++){
        for (int j = 0 ; j < cols ; j ++){
            for ( int k = 0 ; k < 3 ; k++ ){
                temp_photo ( i , j , k ) = photo ( i , j , k )  ;
            }
        }
    }
    photo.width = rows ;
    photo.height = cols ;
    for ( int i = 0 ; i < rows ; i ++){
        for (int j = 0 ; j < cols ; j ++){
            for ( int k = 0 ; k < 3 ; k++ ){
                photo ( i , j , k ) = temp_photo ( i , j , k )  ;
            }
        }
    }
}

void Crop_Filter () {
    string photo_name;
    Save_InNewImage_Mode = false ;
    photo_name = Check_Image_Name(photo_name , Save_InNewImage_Mode );
    Image photo(photo_name);
    int rows, cols;
    while (true) {
        cout << "==================================================\n"
                "Enter the dimensions of the Image you want : -\n"
                "Rows = ";
        cin >> rows;
        cin.ignore();
        if (rows >= 0 && rows <= photo.width) {
            cout << "Columns = ";
            cin >> cols;
            cin.ignore();
            if (cols >= 0 && cols <= photo.height) {
                Just_Crop(rows, cols, photo);
                Save_Image(photo_name, photo);
                break;
            } else {
                cout << "(( Enter a valid Columns number )) \n";
                continue;
            }
        } else {
            cout << "(( Enter a valid rows number )) \n";
            continue;
        }
    }
}



void Merge () {
    string foto_1, foto_2;
    Save_InNewImage_Mode = false ;
    foto_1 = Check_Image_Name( foto_1 , Save_InNewImage_Mode);
    foto_2 = Check_Image_Name( foto_2 , Save_InNewImage_Mode);

    Image photo1(foto_1);
    Image photo2(foto_2);

    int rows_f1 =photo1.height ;
    int cols_f1 =photo1.width ;
    int rows_f2 =photo2.height ;
    int cols_f2 =photo2.width ;

    int width_difference = rows_f1 - rows_f2 ;        // these differences is the extra piece we want to crop it
    int height_difference = cols_f1 - cols_f2 ;

    if ( width_difference > 0 ){
        Just_Crop(  rows_f1 - width_difference , cols_f1 , photo1 );
        rows_f1 = rows_f1 - width_difference ;
    }
    if ( height_difference > 0 ){
        Just_Crop( rows_f1 , cols_f1 - height_difference , photo1 );
        cols_f1 = cols_f1 - height_difference ;
    }
    if ( width_difference < 0 ){
        width_difference *= -1 ;
        Just_Crop(  rows_f2 - width_difference , cols_f2 , photo2 );
        rows_f2 = rows_f2 - width_difference ;
    }
    if ( height_difference < 0 ){
        height_difference *= -1 ;
        Just_Crop(  rows_f2  , cols_f2 - height_difference , photo2 );
        cols_f2 = cols_f2 - height_difference ;
    }


    Image photo3 (rows_f2 , cols_f2);          // or photo2.width and height as they are equal
    string photo3_name ;
    Save_InNewImage_Mode = false ;
    photo3_name = Check_Image_Name ( photo3_name , Save_InNewImage_Mode);
    for (int i = 0; i < rows_f2; i++) {
        for (int j = 0; j < cols_f2; j++) {
            for (int k = 0; k < 3 ; k++) {
                photo3(i, j, k) = ( photo1(i, j, k) + photo2(i , j , k ) ) /2 ;
            }
        }
    }
    photo3.saveImage( photo3_name );
}

void Rotator () {
    string photo_name;
    Save_InNewImage_Mode = false ;
    photo_name = Check_Image_Name(photo_name , Save_InNewImage_Mode );
    Image image(photo_name);

    while (true) {
        string choice;
        cout << "Enter the rotate degree from those ( 90 , 180 , 270 ) \n"
                "1) 90 \n"
                "2) 180 \n"
                "3) 270 \n"
                "======================================================\n";

        getline(cin, choice);
        if (choice == "1") { // 90 degrees
            Image rotatedimage(image.height, image.width);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        rotatedimage(image.height - j - 1, i, k) = image(i, j, k);
                    }
                }
            }
            Save_Image(photo_name, rotatedimage);
            break;
        }
        else if (choice == "2") { // 180 degrees
            Image rotatedimage(image.width, image.height);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        rotatedimage(image.width - i - 1, image.height - j - 1, k) = image(i, j, k);
                    }
                }
            }
            Save_Image(photo_name, rotatedimage);
            break;
        }
        else if (choice == "3") {
            Image rotatedimage(image.height, image.width);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        rotatedimage(j, image.width - i - 1, k) = image(i, j, k);
                    }
                }
            }
            Save_Image(photo_name, rotatedimage);
            break;
        } else {
            cout << "(( Enter a valid choice )) \n";
            continue;
        }
    }
}

void Inverter (){
    string photo_name;
    Save_InNewImage_Mode = false ;
    photo_name = Check_Image_Name(photo_name , Save_InNewImage_Mode );
    Image image(photo_name);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    Save_Image( photo_name , image );
}

void Detect_Image_Edges (){
    string photo_name ;
    Save_InNewImage_Mode = false ;
    photo_name = Check_Image_Name(photo_name , Save_InNewImage_Mode);
    Image image (photo_name);

    bool photo_is_gray = true;         // to check if photo is grayed or coloured
    bool end_first_loop = false ;
    for (int i = 0; i < image.width; i++) {
        if ( end_first_loop == false ){
            for (int j = 0; j < image.height; j++) {
                if ( image(i, j , 0) != image(i, j , 1) && image(i, j , 0) != image(i, j , 2) ){
                    photo_is_gray = false;
                    end_first_loop = true;
                    break ;
                }
            }
        }
        else{
            break;
        }
    }

    if ( photo_is_gray == true){
        for (int i = 0; i < image.width; i++) {  // if photo is gray scaled like (photographer) then we do it directly
            for (int j = 0; j+3 < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    if ( image(i, j, k) > 127){
                        image(i, j, k) = 255 ;
                    }
                    else{
                        image(i, j, k) = 0;
                    }
                }
            }
        }
    }
    else{
        for (int i = 0; i < image.width; i++) {  // to make photo black and white (if photo is coloured)
            for (int j = 0; j < image.height; j++) {
                unsigned avg = 0;
                for (int k = 0; k < 3; k++) {
                    avg += image(i, j, k);
                }
                for (int k = 0; k < 3; k++) {
                    image(i, j, k) = avg ;
                }
                for (int k = 0; k < 3; k++) {
                    if ( image(i, j, k) > 127 ){
                        image(i, j, k) = 255 ;
                    }
                    else{
                        image(i, j, k) = 0 ;
                    }
                }
            }
        }
    }



    for (int i = 0; i < image.width; i++) {   // to detect the photo
        for (int j = 0; j+3 < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                if ( image(i, j, k) == 0 && image(i,j+1,k) == 0 && image(i,j+2,k) == 0 ) {
                    for(int f = j + 2 ; f + 2 < image.height ; f++ ){
                        if ( image(i, f, k) == 0 && image(i, f + 1, k) == 0 && image(i,f + 2,k) == 0){
                            image(i, f, k) = 255 ;
                        }
                        else if ( image(i, f, k) == 255 && image(i, f + 1, k) == 0 && image(i, f + 2, k) == 0 ){
                            break;
                        }
                    }
                }
            }
        }
    }
    Save_Image( photo_name , image );
}

void The_Land_Of_Wano(){
    string photo_name ;
    Save_InNewImage_Mode = false ;
    photo_name = Check_Image_Name(photo_name , Save_InNewImage_Mode);
    Image image (photo_name);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i, j, 0) += ( 255 - image(i, j, 0)) / 5 ;
            image(i, j, 1) += ( 255 - image(i, j, 1)) / 5 ;
            image(i, j, 2) = image(i, j, 2) * 4/5 ;
        }
    }
    Save_Image( photo_name , image );
}

void Oil_Painting(){
    string photo_name ;
    Save_InNewImage_Mode = false ;
    photo_name = Check_Image_Name(photo_name , Save_InNewImage_Mode);
    Image image (photo_name);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i, j, 0) += ( 255 - image(i, j, 0)) / 5 ;
            image(i, j, 1) += ( 255 - image(i, j, 1)) / 5 ;
            image(i, j, 2) = image(i, j, 2) * 4/5 ;
        }
    }
    Save_Image( photo_name , image );
}



int main() {
    string input ;
    while ( true ) {
        cout << "================================================================="
                "\n            Welcome To Baby Photoshop Program \n"
                "=================================================================\n"
                "Choose The Filter You Want To Do In Your Image : - \n"
                "1) Gray Scale \n"
                "2) Darken , Lighten \n"
                "3) Crop \n"
                "4) Rotator \n"
                "5) Inverter\n"
                "6) Merge ( with crop (( untill now )) ) \n"
                "7) Detect Image Edges\n"
                "8) Land Of Wano \n"
                "0) Exit Program \n"
                "=================================================================\n";
        cin >> input;
        cin.ignore();
        if (input == "1") {
            gray_scale();
            continue;
        } else if (input == "2") {
            darken_lighten();
            continue;
        } else if (input == "3") {
            Crop_Filter();
            continue;
        } else if (input == "4"){
            Rotator ();
            continue;
        } else if (input == "5"){
            Inverter ();
        }else if ( input == "6"){
            Merge();
            continue;
        } else if (input == "7") {
            Detect_Image_Edges();
            continue;
        } else if (input == "8"){
            The_Land_Of_Wano();
            continue;
        }else if ( input == "0") {
            cout << "================================================================\n"
                    "      We Hope You Have Nice Time Using Baby Photoshop  \n"
                    "================================================================\n";
            break ;
        } else {
            cout << "(( Enter a a valid input )) \n";
            continue ;
        }
    }
    return 0;
}
