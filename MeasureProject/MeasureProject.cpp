// MeasureProject.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

// Namespaces
namespace fs = std::experimental::filesystem;
using namespace std;
using namespace cv;

// Global variables
bool DEBUG = false;
Mat image;
string IMAGE_DIRECTORY;
const string INPUT_CONSTANT = "input/";

// Forward declarations
static void load_image();
static void show_image();
void mouse_callback(int event, int x, int y, int flags, void* userdata);

// Main method
int main()
{
	cout << "Measure Project\nAuthor: Andy Thai" << endl;
	cout << "\nUsing OpenCV version " << CV_VERSION << endl;
	if (DEBUG) {
		cout << getBuildInformation();
	}

	// Check if input and output directories exist
	if (!fs::exists("input")) { // Check if input folder exists
		cout << "\nNo input folder detected! Creating input folder." << endl <<
			"FrameGrabber will shut down. Please move your input images to the input folder." << endl;
		fs::create_directory("input"); // create input folder
		cin.ignore();
		return 1;
	}
	if (!fs::exists("output")) { // Check if output folder exists
		cout << "\nCreating output folder..." << endl;
		fs::create_directory("output"); // create output folder
	}

	load_image();
	show_image();

	cin.ignore();
	return 0;
}

// Loads image
static void load_image() {
	// Get video file location
	bool valid_input = false;
	cout << "Input image file: ";

	while (!valid_input) {
		getline(cin, IMAGE_DIRECTORY);

		// Concatenate to add input folder directory to beginning
		string image_input = INPUT_CONSTANT + IMAGE_DIRECTORY;

		// Initialize and load image
		image = imread(image_input, CV_LOAD_IMAGE_UNCHANGED);
		if (image.data) {
			valid_input = true;
		}
		else {
			cout << "Unable to load " << IMAGE_DIRECTORY << "! Please re-enter image filename: ";
		}
	}

	// Resize image for better viewing and user experience

}

// Shows image
static void show_image() {
	namedWindow(IMAGE_DIRECTORY, WINDOW_AUTOSIZE);				// Create a window for display.
	setMouseCallback(IMAGE_DIRECTORY, mouse_callback, NULL);	// Sets callback function for mouse
	imshow(IMAGE_DIRECTORY, image);								// Show our image inside it.
	waitKey(0);													// Wait for a keystroke in the window
}

// Mouse callback function
void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	/*
	else if (event == EVENT_MOUSEMOVE)
	{
		cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

	}
	*/
}