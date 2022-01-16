#include <iostream>

#include <fstream>

#include <string>

#include <vector>

using namespace std;

struct color {
  int r, g, b;
};

class Image {
  public:
  void openImage(string file_name);
  void saveImage(string file_name);
  void convertToGrayscale(double cr, double cg, double cb);
  int getWidth() {
    return width;
  }
  int getHeight() {
    return height;
  }
  Image() {
    width = 0;
    height = 0;
    range = 255;
  }

  private:
    int width, height, range;
  vector < color > image;
};

void menu(Image imaj);

int main() {
  Image imaj;

  menu(imaj);

  return 0;
}

void menu(Image imaj) {
  int choice = -1, submenu_choice = -1, cgsm_choice = -1;
  string file_name;

  double c_r = 0.0, c_g = 0.0, c_b = 0.0;

  do {
    cout << "MAIN MENU" << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Open An Image(D)" << endl;
    cout << "2 - Save Image Data(D)" << endl;
    cout << "3 - Scripts(D)" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
      do {
        cout << "OPEN AN IMAGE MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter The Name Of The Image File" << endl;
        cin >> submenu_choice;
        if (submenu_choice == 1) {
          cin >> file_name;
          imaj.openImage(file_name);
        }
      } while (submenu_choice != 0);
      break;

    case 2:
      do {
        cout << "SAVE IMAGE DATA MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter A File Name" << endl;
        cin >> submenu_choice;
        if (submenu_choice == 1) {
          cin >> file_name;
          imaj.saveImage(file_name);
        }
      } while (submenu_choice != 0);
      break;

    case 3:
      do {
        cout << "SCRIPTS MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Convert to Grayscale(D)" << endl;
        cin >> submenu_choice;
        if (submenu_choice == 1) {
          cout << "CONVERT TO GRAYSCALE MENU" << endl;
          cout << "0 - UP" << endl;
          cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;
          cin >> cgsm_choice;
          if (cgsm_choice == 1) {
            cin >> c_r >> c_g >> c_b;
            while (c_r < 0.0 || c_r > 1.0 || c_g < 0.0 || c_g > 1.0 || c_b < 0.0 || c_b > 1.0) {
              cout << "ERROR! Enter a double numbers between 0 and 1 for each coefficient for red, green and blue." << endl;
              cin >> c_r >> c_g >> c_b;
            }
            imaj.convertToGrayscale(c_r, c_g, c_b);
          }
        }
      } while (submenu_choice != 0);
      break;

    case 0:
      cout << "Good Bye!" << endl;
      break;

    default:
      cout << "You have entered a wrong input." << endl;
      break;
    }
  } while (choice != 0);
}

void Image::openImage(string file_name) {
  ifstream myImage(file_name);
  string file_format, input;
  color temp;
  if (myImage.is_open()) {
    // Getting file format, width and height
    myImage >> file_format;
    myImage >> input;
    width = stoi(input);
    myImage >> input;
    height = stoi(input);
    myImage >> input;
    range = stoi(input);

    // Continue if file format is PPM
    if (file_format.compare("P3") == 0) {
      // Till at end of file
      while (!myImage.eof()) {
        // Reading colors
        myImage >> temp.r;
        myImage >> temp.g;
        myImage >> temp.b;
        image.push_back(temp);
      }
    }
  } else 
    cout << "Error: File opening failed." << endl;
  myImage.close();
}

void Image::saveImage(string file_name) {
  ofstream myImage;
  myImage.open(file_name);
  string file_format;
  color temp;
  int i, j, colorIndex;
  if (myImage.is_open()) {
    myImage << "P3\n";
    myImage << width << " " << height << "\n";
    myImage << range << "\n";

    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
        colorIndex = i * width + j;
        myImage << image[colorIndex].r << " " << image[colorIndex].g << " " << image[colorIndex].b;
        if (j < width - 1)
          myImage << " ";
      }
      if (i < height - 1)
        myImage << "\n";
    }
  } else
    cout << "Error: File opening failed." << endl;
  myImage.close();
}

void Image::convertToGrayscale(double cr, double cg, double cb)
{
    int i, numberOfColors;
    numberOfColors = width*height;
    for(i=0; i<numberOfColors; i++)
    {
        image[i].r *= cr;
        image[i].g *= cg;
        image[i].b *= cb;
    }
}
