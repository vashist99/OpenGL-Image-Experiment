#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SPIRAL_SIZE = 200;

// Mat_<Vec3b> image;
// for gray scale images
Mat image;

std::vector<float> m;

void draw_color(Mat_<Vec3b> img)
{
    glPointSize(3.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // glColor3f(1.0, 1.0, 1.0);

    // Draw the spiral
    for (int i = 0; i < img.rows; ++i)
    {
        m[1] -= 0.006;
        m[0] = -0.008 * float(image.cols / 2);
        for (int j = 0; j < img.cols; j++)
        {
            m[0] += 0.006;
            // Draw the point

            glBegin(GL_POINTS);
            float b = float(float(img.at<Vec3b>(i, j)[0]) / float(255));
            float g = float(float(img.at<Vec3b>(i, j)[1]) / float(255));
            float r = float(float(img.at<Vec3b>(i, j)[2]) / float(255));

            // std::cout << r << " " << g << " " << b << "\n";

            glColor3f(r, g, b);
            glVertex2f(m[0], m[1]);
            glEnd();
            // glFlush();

            // std::cout << "haha\n";
        }
    }

    // Swap the back and front buffers
    glutSwapBuffers();
}

// To Draw Grey scale Image

// image segmentation for greyscale image
Mat image_segmentation(Mat image)
{
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (image.at<uchar>(i, j) < 128)
            {
                image.at<uchar>(i, j) = 0;
            }
            else
            {
                image.at<uchar>(i, j) = 255;
            }
        }
    }

    return image;
};

void draw_grey_scale(Mat img)
{

    glPointSize(3.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // Draw the spiral
    for (int i = 0; i < img.rows; ++i)
    {
        m[1] -= 0.006;
        m[0] = -0.008 * float(image.cols / 2);
        for (int j = 0; j < img.cols; j++)
        {
            m[0] += 0.006;
            // Draw the point

            if (img.at<uchar>(i, j) == 255)
            {

                glBegin(GL_POINTS);
                glVertex2f(m[0], m[1]);
                glEnd();
                // glFlush();
            }
        }
    }

    // Swap the back and front buffers
    glutSwapBuffers();
}

// experiment to print characters
void print(int x, int y, int z, std::string name)
{
    // set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);
    // get the length of the string to display

    // loop to display character by character
    for (int i = 0; i < name.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name[i]);
    }
};

void display()
{

    draw_color(image);

    // print(0, 0, 0, "Vashist");
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set the display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Set the window size
    glutInitWindowSize(10000, 10000);

    // Set the window title
    glutCreateWindow("Image Art");

    // image reading and segmentation:
    //  Read the image file as gray scale
    image = imread("chris_cornell.png" /*,IMREAD_GRAYSCALE*/);

    // Read Colour Image
    // image = imread("ayushi.png");

    // segmentation of greyscale image
    // image = image_segmentation(image);

    // test
    //  std::cout << image.rows << " " << image.cols << "\n";

    // save image
    // imwrite("chris_cornell_mod.jpeg", image);

    // Set the display function
    glutDisplayFunc(display);

    m.push_back(-0.005 * float(image.cols / 2));
    m.push_back(0.005 * float(image.rows / 2));

    // Enter the main loop
    glutMainLoop();

    return 0;
}