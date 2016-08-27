#include "stdafx.h"
#include "stdio.h"

#include "FlyCapture2.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <future>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <sys/param.h>
#include <unistd.h>

using namespace FlyCapture2;
using namespace std;

void PrintError( Error error )
{
    error.PrintErrorTrace();
}

int get_current_time()
{
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch());
	return ms.count();
}

int main(int argc, char* argv[])
{
	const Mode k_fmt7Mode = MODE_7;
	const PixelFormat k_fmt7PixFmt = PIXEL_FORMAT_RAW16;
	const vector<int> SHUTTER_SPEEDS { 50, 100, 500 };
	const vector<int> CAPTURES_PER_SHUTTER_SPEED { 10, 2, 1 };

	BusManager busMgr;
	unsigned int numCameras;
	Camera cam;
	Error error;
	PGRGuid guid;

	chdir("/var/run/usbmount/SanDisk_Ultra_Fit_1");

	// TEST FILE WRITE ACCESS
	cout << "Testing file access..." << endl;
    FILE* tempFile = fopen("test.txt", "w+");
    if (tempFile == NULL)  {
		cout << "Failed to create file in current folder.  Please check permissions." << endl;
    	return -1;
 	}
    fclose(tempFile);
    //remove("test.txt");

	// TEST CAMERA DETECTION
	cout << "Testing camera detection..." << endl;
    error = busMgr.GetNumOfCameras(&numCameras);
    if (error != PGRERROR_OK){
    	PrintError( error );
    	return -1;
	}

	// GET CAMERA FROM INDEX
 	cout << "Fetching camera from port index" << endl;
	error = busMgr.GetCameraFromIndex(0, &guid);
    if (error != PGRERROR_OK) {
        PrintError( error );
        return -1;
    }
	
	// CONNECT
	cout << "Connecting to camera..." << endl;
    error = cam.Connect(&guid);
    if (error != PGRERROR_OK) {
	    PrintError( error );
    	return -1;
	}

	// GET CAMERA INFORMATION
	cout << "Fetching camera information..." << endl;
	CameraInfo camInfo;
	error = cam.GetCameraInfo(&camInfo);
	if (error != PGRERROR_OK) {
    	PrintError( error );
        return -1;
	}

	// CREATE FORMAT7 SETTINGS
	cout << "Creating fmt7 settings..." << endl;
  	Format7ImageSettings fmt7ImageSettings;
  	bool valid;
  	Format7PacketInfo fmt7PacketInfo;
		
  	fmt7ImageSettings.mode = k_fmt7Mode;
  	fmt7ImageSettings.offsetX = 0;
 	fmt7ImageSettings.offsetY = 0;
 	fmt7ImageSettings.width = 1024;
 	fmt7ImageSettings.height = 720;
 	fmt7ImageSettings.pixelFormat = k_fmt7PixFmt;

	// VALIDATE FORMAT7 SETTINGS
	cout << "Validating fmt7 settings..." << endl;
  	error = cam.ValidateFormat7Settings(&fmt7ImageSettings,
					    &valid,
				            &fmt7PacketInfo );
  	if (error != PGRERROR_OK){
		PrintError( error );
		return -1;
  	}

  	if ( !valid ){
    	// Settings are not valid
    	cout << "Format7 settings are not valid" << endl; 
    	return -1;
  	}

	// SET FORMAT7 SETTINGS
	cout << "Writing fmt7 settings..." << endl;
  	error = cam.SetFormat7Configuration(&fmt7ImageSettings,
										fmt7PacketInfo.recommendedBytesPerPacket );
  	if (error != PGRERROR_OK){
    	PrintError( error );
    	return -1;
	}

	// SEQUENCE
	cout << "Starting image sequence..." << endl;
	unsigned int imageCount = 0;
	for(int j = 0; j < 3; j++) {

		int shutter_speed = SHUTTER_SPEEDS.at(j); 
    	cout << "Writing image " << imageCount << " ..." << endl;
		imageCount++;
		
		// CREATE SHUTTER PROPERTY
  		Property prop;
  		prop.type = SHUTTER;
  		prop.onOff = true;
  		prop.autoManualMode = false;
  		prop.absControl = true;
  		prop.absValue = shutter_speed;

		
		// WRITE SHUTTE PROPERTY 
		error = cam.SetProperty(&prop);
		if (error != PGRERROR_OK){
			PrintError( error );
	    	return -1;
  		}

		cout << "Properties written..." << endl;

		

		cout << "Starting capture for " <<  shutter_speed << "ms images..." << endl;

		for (int k = 0; k < CAPTURES_PER_SHUTTER_SPEED.at(j); k++) { 
						
			// START CAPTURE
			error = cam.StartCapture();
			if (error != PGRERROR_OK){
				PrintError( error );
				return -1;
	  		}
			
			cout << "Capture started for image " << k << "..." << endl;
	
			// RETRIEVE IMAGE BUFFER
		    Image rawImage;
		
		    error = cam.RetrieveBuffer( &rawImage );
		    if (error != PGRERROR_OK) {
		    	PrintError( error );
	    		return -1;
	  		}
			
			// cout << "Got buffer" << endl;
	
			// SET IMAGE DIMENSIONS
	    	PixelFormat pixFormat;
	    	unsigned int rows, cols, stride;
	    	rawImage.GetDimensions( &rows, &cols, &stride, &pixFormat );
	
			// CONVERT IMAGE
	    	Image convertedImage;
	    	error = rawImage.Convert( PIXEL_FORMAT_BGRU, &convertedImage );
		    if (error != PGRERROR_OK){
				PrintError( error );
				return -1;
			}
	
			// cout << "Converted image" << endl;
	
			// SAVE IMAGE
			ostringstream filename;
			int ms_time = get_current_time();
	
			filename << "img_gps_" << argv[1] << "_pi_" << ms_time << "_shutter_" << shutter_speed << "_groupid_" << k << ".bmp";
		      
	    	error = convertedImage.Save( filename.str().c_str() );
	    	if (error != PGRERROR_OK){
	    		PrintError( error );
	    		return -1;
			}
	
			this_thread::sleep_for(chrono::milliseconds(3000));
	
			// STOP CAPTURE
		    error = cam.StopCapture();
		    if (error != PGRERROR_OK){
		    	PrintError( error );
	      		return -1;
			}
		}
	}

	// DISCONNECT
    error = cam.Disconnect();
    if (error != PGRERROR_OK){
    	PrintError( error );
    	return -1;
	}

	cout << "Done." << endl;
	return 0;
}
