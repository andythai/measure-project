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
vector<Coordinates*> POINTS;
int LOCATION = 0;
int X_POS = -1;
int Y_POS = -1;

// Forward declarations
static void setup_vector();
static void load_image();
static void show_image();
void mouse_callback(int event, int x, int y, int flags, void* userdata);
static void calc_width();
static void calc_height();
static void calc_angle();

// Main method
int main()
{
	cout << "Measure Project\nAuthor: Andy Thai" << endl;
	cout << "Using OpenCV version " << CV_VERSION << endl << endl;
	if (DEBUG) {
		cout << getBuildInformation();
	}

	// Initializes vector of coordinates
	setup_vector();

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

	cout << "Click on the left, right, top, and bottom corners of the rat's eye (respectively)." << endl;
	cout << "DO NOT PRESS ENTER ON THIS CONSOLE UNTIL FINISHED." << endl;

	show_image();

	cin.ignore();
	cin.ignore();
	cin.ignore();

	return 0;
}

// Initializes points for use in tracking ratios and angles
static void setup_vector() {
	for (int i = 0; i < 7; i++) {
		POINTS.push_back(new Coordinates());
	}
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
	// Undo command
	if (event == EVENT_RBUTTONDOWN) {
		cout << "UNDO ";
		if (LOCATION == 1) {
			cout << "left side." << endl;
		}
		else if (LOCATION == 2) {
			cout << "right side." << endl;
		}
		else if (LOCATION == 3) {
			cout << "top side." << endl;
		}
		else if (LOCATION == 4) {
			cout << "bottom side." << endl;
		}
		else if (LOCATION == 5) {
			cout << "first anchor." << endl;
		}
		else if (LOCATION == 6) {
			cout << "second anchor." << endl;
		}
		else if (LOCATION == 7) {
			cout << "third anchor." << endl;
		}

		// Make sure index doesn't get reduced to negatives.
		if (LOCATION > 0) {
			LOCATION--;
		}
	}

	// Get width
	else if (LOCATION < 2) {
		if (event == EVENT_LBUTTONDOWN) {

			// Left side
			if (LOCATION == 0) {
				cout << "Left side of rat eye selected at (" << x << ", " << y << ")" << endl;
				POINTS[LOCATION]->set_coords(x, y);
				LOCATION++;
			}

			// Right side
			else if (LOCATION == 1) {
				cout << "Right side of rat eye selected at (" << x << ", " << y << ")" << endl;
				POINTS[LOCATION]->set_coords(x, y);
				LOCATION++;
			}
		}
	}

	// Get height
	else if (LOCATION < 4) {
		if (event == EVENT_LBUTTONDOWN) {

			// Top side
			if (LOCATION == 2) {
				cout << "Top side of rat eye selected at (" << x << ", " << y << ")" << endl;
				POINTS[LOCATION]->set_coords(x, y);
				LOCATION++;
			}

			// Bottom side
			else if (LOCATION == 3) {
				cout << "Bottom side of rat eye selected at (" << x << ", " << y << ")" << endl;
				POINTS[LOCATION]->set_coords(x, y);
				LOCATION++;
			}
		}
	}

	// Get angle
	else if (LOCATION < 7) {
		if (event == EVENT_LBUTTONDOWN) {

			// First anchor point
			if (LOCATION == 4) {
				cout << "First anchor point selected at (" << x << ", " << y << ")" << endl;
				POINTS[LOCATION]->set_coords(x, y);
				LOCATION++;
			}

			// Second anchor point
			else if (LOCATION == 5) {
				cout << "Second anchor point selected at (" << x << ", " << y << ")" << endl;
				POINTS[LOCATION]->set_coords(x, y);
				LOCATION++;
			}

			// Third anchor point
			else if (LOCATION == 6) {
				cout << "Last anchor point selected at (" << x << ", " << y << ")" << endl;
				POINTS[LOCATION]->set_coords(x, y);
				LOCATION++;
			}
		}
	}
	/*
	else if (event == EVENT_MOUSEMOVE)
	{
		cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

	}
	*/
}

// Calculates width for height/width ratio
static void calc_width() {
	while (LOCATION < 2) {
		if (LOCATION == 0) {
			cout << "Select the left side of the rat's eye, then press ENTER." << endl;
			cin.ignore();
			POINTS[LOCATION]->set_coords(X_POS, Y_POS);
			cout << "Point at (" << POINTS[LOCATION]->get_x() << ", " << POINTS[LOCATION]->get_y() << ") selected." << endl;
			LOCATION++;
		}
		else if (LOCATION == 1) {
			cout << "Select the right side of the rat's eye, then press ENTER." << endl;
			cin.ignore();
			POINTS[LOCATION]->set_coords(X_POS, Y_POS);
			LOCATION++;
		}
	}
}