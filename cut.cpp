#include "stdafx.h"     //By default

#include < string.h>

#include < stdio.h>

#include < stdlib.h>

#include "cv.h"

#include < highgui.h>

#include "cxcore.h" 

#include <iostream>     //To use cout and cin

using namespace cv;     //To use VideoCapture

//Public file path

string fullPath;

VideoCapture capture(0);


void ExplicitWM()

{

 //Explicit Watermark

//Input Message
char txt[100] = {'\0'};
cout << "Enter message to encode: " << endl;
cout<<"-----------------------"<< endl;
cin >> txt;


double dWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
double dHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

//Save Video to desktop
string userProfile = getenv("userprofile");
string path = userProfile + "\\Desktop\\";
string saveVid;
getline (cin, saveVid);
string fullPath = path + saveVid;

//CV_FOURCC('P','I','M','1') is a MPEG-1 codec
VideoWriter oVideoWriter (fullPath + "SavedVid.avi", CV_FOURCC('P', 'I', 'M', '1'), 30, frameSize, true); //initialize the VideoWriter object 

if ( !oVideoWriter.isOpened() ) //if not initialize the VideoWriter successfully, exit the program
{
    cout << "ERROR: Failed to write the video" << endl;
}

while ( capture.isOpened() )
{
        Mat frame;

        bool bSuccess = capture.read(frame); // read a new frame from video

        imshow("Original Video", frame); //show the frame in "Original Video" window

        Mat imgW = frame;

        // cvScalar(255,255,255) = rgb
        // cvPoint(40,40) = x-y cord
        // 0.8 = font size
        putText(imgW, txt, cvPoint(400,400), CV_FONT_HERSHEY_COMPLEX, 0.8, cvScalar(255,255,255), 1, CV_AA);


        imshow("Watermarked Video", imgW); //show the frame of which watermark added

        oVideoWriter.write(imgW); //write the frame into the file

        if (waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
        {
                cout << "Esc key is pressed by user" << endl; 
                break; 
        }
 }
}

int main(int argc, char* argv[] )

{

cout<< endl;

cout << "Place video in Desktop and enter file name (e.g. vid.avi):" << endl;

cout<<"--------------------------------------"<< endl;

//Get user desktop file path

string userProfile = getenv("userprofile"); //GetEnvironmentVariable() is to get current userprofile (e.g."C:\Users\L30807")

string path = userProfile + "\\Desktop\\";

string vid;

getline (cin, vid);     //Prompt to input file name
fullPath = path + vid;
capture.open(fullPath); //Read video
cout<< endl;

if ( capture.isOpened() )
{
    char choice;
        cout<< "Choose option (a or b): "<< endl;
        cout<<"-----------------------"<< endl;
        cout<< "a.Encode Video "<<endl;
        cout<< "b.Decode Video "<<endl;
        cout<<"-----------------------"<< endl;
        cin >> choice;
        cout<< endl;

        if (choice== 'a')//Encode Video
        {
            int choiceEn;
            cout<< "Choose option (1 or 2): "<< endl;
            cout<<"-----------------------"<< endl;
            cout<< "1.Explicit Watermarking " <<endl;
            cout<< "2.Implicit Watermarking(DCT) "<<endl;
            cout<<"-----------------------"<< endl;
            cin >> choiceEn;
            cout<< endl;

            switch ( choiceEn ) 
            {
                case 1:         
                ExplicitWM();
                break;

                default:
                cout<<"Error: Wrong input. Exiting..." << endl;
                return 0;
            }
        }

        else if (choice== 'b') 
        { 

        }
}
