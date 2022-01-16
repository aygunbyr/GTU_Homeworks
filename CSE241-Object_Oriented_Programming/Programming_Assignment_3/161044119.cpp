#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Defined to be used in image
struct color {
    int r, g, b;
};


class Image {
    public:
        void openImage(string file_name, int * image_index);
        void saveImage(string file_name);
        void convertToGrayscale(double cr, double cg, double cb);
        int getWidth() { return *width;}
        int getHeight() { return *height;}
        int getRange() { return *range;}
        string getName() {
            return *name;
        }
        void setWidth(int wd) {*width=wd;}
        void setHeight(int h) {*height=h;}
        void setRange(int r) {*range=r;}
        void setName(string n) {*name=n;}
        void reallocate(int w, int h) {
            * width = w;
            * height = h;
            image = new struct color[w * h];
        };
        Image() {
            width = new int;
            height = new int;
            range = new int;
            image = new struct color;
            name = new string;
            * width = 0;
            * height = 0;
            * range = 255.0;
        }
        Image(int w, int h) {
            width = new int;
            height = new int;
            range = new int;
            image = new struct color[w * h];
            name = new string;
            * width = w;
            * height = h;
            * range = 255.0;
        }
        ~Image() {
        delete width;
        delete height;
        delete range;
        delete image;
        delete name;
        }
        Image(Image &image2) {
            int i, j;
            width = new int;
            height = new int;
            range = new int;
            name = new string;
            *width = image2.getWidth();
            *height = image2.getHeight();
            *range = image2.getRange();
            *name = image2.getName();
            image = new struct color[(*width)*(*height)];
            for(i=0; i<*height; i++)
            {
                for(j=0; j<*height; j++)
                {
                    image[i*(*width)+j].r = image2.image[i*(*width)+j].r;
                    image[i*(*width)+j].g = image2.image[i*(*width)+j].g;
                    image[i*(*width)+j].b = image2.image[i*(*width)+j].b;
                }
            }
        }
        Image& operator+(Image second);
        void operator=(Image& second);

        
    private:
        int * width, * height, * range;
        struct color * image;
        string * name;
};

void menu(Image * imaj, Image modified_image);

int main() {
    Image imaj[2], modified_image;
    
    menu(imaj, modified_image);

    return 0;
}

void Image :: operator=(Image& second) {
    int i, j;

    *width = second.getWidth();
    *height = second.getHeight();
    *range = second.getRange();
    *name = second.getName();
    reallocate(*width, *height);

    for(i=0; i<*height; i++)
    {
        for(j=0; j<*width; j++)
        {
            image[i*(*width)+j].r = second.image[i*(*width)+j].r;
            image[i*(*width)+j].g = second.image[i*(*width)+j].g;
            image[i*(*width)+j].b = second.image[i*(*width)+j].b;
        }
    }
}

Image&  Image :: operator+(Image second) {
    int i, j;

    for(i=0; i<*height; i++)
    {
        for(j=0; j<*width; j++)
        {
            // Sum reds
            if(image[i*(*width)+j].r + second.image[i*(*width)+j].r > *range)
                image[i*(*width)+j].r = *range;
            else
                image[i*(*width)+j].r += second.image[i*(*width)+j].r;

            // Sum greens
            if(image[i*(*width)+j].g + second.image[i*(*width)+j].g > *range)
                image[i*(*width)+j].g = *range;
            else
                image[i*(*width)+j].g += second.image[i*(*width)+j].g;

            // Sum blues
            if(image[i*(*width)+j].b + second.image[i*(*width)+j].b > *range)
                image[i*(*width)+j].b = *range;
            else
                image[i*(*width)+j].b += second.image[i*(*width)+j].b;
        }
    }
    return *this;
}

void menu(Image * imaj, Image modified_image) {
    int choice = -1, submenu_choice = -1, cgsm_choice = -1, image_index = 0, image_selected = -1, i;
    bool image_modified=false;
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
            if (image_index < 2) {
                do {
                    cout << "OPEN AN IMAGE MENU" << endl;
                    cout << "0 - UP" << endl;
                    cout << "1 - Enter The Name Of The Image File #" << image_index + 1 << endl;
                    cin >> submenu_choice;
                    if (submenu_choice == 1) {
                        cin >> file_name;
                        imaj[image_index].openImage(file_name, & image_index);
                    }
                } while (submenu_choice != 0 && image_index <= 1);
            } else {
                cout << "You are not allowed to open more than 2 images." << endl;
            }
            break;

        case 2:
            do {
                cout << "SAVE IMAGE DATA MENU" << endl;
                cout << "0 - UP" << endl;
                cout << "1 - Enter A File Name" << endl;
                cin >> submenu_choice;

                if (submenu_choice == 1) {
                    cin >> file_name;
                    cout << "Select an image:" << endl;
                    for (i = 0; i < image_index; i++)
                        cout << i + 1 << ". " << imaj[i].getName() << endl;
                    if(image_modified)
                    {
                        cout << i + 1 << ". " << modified_image.getName() << endl;
                    }
                    cout << "Your choice: ";
                    cin >> image_selected;
                    image_selected--;

                    // Save modified image
                    if(image_modified && image_selected == 2)
                    {
                        modified_image.saveImage(file_name);
                    }
                    else
                        imaj[image_selected].saveImage(file_name);
                }
            } while (submenu_choice != 0);
            break;

        case 3:
            do {
                cout << "SCRIPTS MENU" << endl;
                cout << "0 - UP" << endl;
                cout << "1 - Convert to Grayscale(D)" << endl;
                cout << "2 - Sum two images(D)" << endl;
                cin >> submenu_choice;
                if (submenu_choice == 1) {
                    cout << "Select an image to convert:" << endl;
                    for (i = 0; i < image_index; i++)
                        cout << i + 1 << ". " << imaj[i].getName() << endl;
                    cout << "Your choice: ";
                    cin >> image_selected;
                    image_selected--;

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
                        imaj[image_selected].convertToGrayscale(c_r, c_g, c_b);
                    }
                }
                if(submenu_choice == 2) {
                    if(image_index == 2) 
                    {
                        // Process of sum
                        modified_image = imaj[0] + imaj[1];
                        cout << "Images have been summed and saved as modified image." << endl;
                        image_modified=true;
			modified_image.setName("modified image");
                    } else
                    {
                        cout << "There is not two images to sum." << endl;
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

void Image::openImage(string file_name, int * image_index) {
    ifstream myImage(file_name);
    string file_format, input;
    int i;
    if (myImage.is_open()) {
        // Getting file format, width and height
        myImage >> file_format;
        myImage >> input;
        * width = stoi(input);
        myImage >> input;
        * height = stoi(input);
        myImage >> input;
        * range = stoi(input);

        * name = file_name;

        // Continue if file format is PPM
        if (file_format.compare("P3") == 0) {
            // Till at end of file
            reallocate( * width, * height);
            i = 0;
            while (!myImage.eof()) {
                // Reading colors
                myImage >> image[i].r;
                myImage >> image[i].g;
                myImage >> image[i].b;
                i++;
            }
            ( * image_index) ++;
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
        myImage << * width << " " << * height << "\n";
        myImage << * range << "\n";

        for (i = 0; i < * height; i++) {
            for (j = 0; j < * width; j++) {
                colorIndex = i * ( * width) + j;
                myImage << image[colorIndex].r << " " << image[colorIndex].g << " " << image[colorIndex].b;
                if (j < * width - 1)
                    myImage << " ";
            }
            if (i < * height - 1)
                myImage << "\n";
        }
    } else
        cout << "Error: File opening failed." << endl;
    myImage.close();
}

void Image::convertToGrayscale(double cr, double cg, double cb) {
    // Converts image to grayscale
    int i, numberOfColors;
    numberOfColors = ( * width) * ( * height);
    *name = "modified image";
    for (i = 0; i < numberOfColors; i++) {
        image[i].r *= cr;
        image[i].g *= cg;
        image[i].b *= cb;
    }
    
}
