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

// for color images
// Mat_<Vec3b> image;
//  for gray scale images
Mat image;

std::vector<float> m;

void draw_color(Mat_<Vec3b> img)
{ // more you increase the point size, more it resembles an image and less of a dot-art
    glPointSize(1);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // glColor3f(1.0, 1.0, 1.0);

    // Draw the spiral
    for (int i = 0; i < img.rows; ++i)
    {

        for (int j = 0; j < img.cols; j++)
        { // tweak the space between the columns of dots.
            m[0] += 0.003;
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
        // tweak the space between rows of dots
        m[1] -= 0.006;
        // If line 179 has been changed, change this accordingly
        m[0] = -0.008 * float(image.cols / 2);
    }

    // Swap the back and front buffers
    glutSwapBuffers();
}

// To Draw Grey scale Image

Mat padding(Mat image, int padding)
{
    Mat padded;

    padded.create(image.rows + 2 * padding, image.cols + 2 * padding, image.type());
    padded.setTo(cv::Scalar::all(0));

    image.copyTo(padded(Rect(padding, padding, image.cols, image.rows)));

    return padded;
}

// Edge Detection for greyscale images
Mat edge_detection(Mat image)
{
    // image.convertTo(image, CV_32F);
    int data1[25] = {0, 0, -1, 0, 0, 0, -1, -2, -1, 0, -1, -2, 16, -2, -1, 0, -1, -2, -1, 0, 0, 0, -1, 0, 0};
    cv::Mat laplace_filter = cv::Mat(5, 5, CV_32SC1, data1);

    int data2[25] = {2, 4, 5, 4, 2, 4, 9, 12, 9, 4, 5, 12, 15, 12, 5, 4, 9, 12, 9, 4, 2, 4, 5, 4, 2};
    cv::Mat gauss_filter = cv::Mat(5, 5, CV_32SC1, data2);

    int data3_horizontal[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    cv::Mat sobel_filter_horizontal = cv::Mat(3, 3, CV_32SC1, data3_horizontal);

    int data3_vertical[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    cv::Mat sobel_filter_vertical = cv::Mat(3, 3, CV_32SC1, data3_vertical);

    int padding_size = 1;
    image = padding(image, padding_size);

    // std::cout << "type: " << image.type() << "\n";

    // smoothing
    // cv::Mat smoothed_image;
    // cv::filter2D(image, smoothed_image, -1, gauss_filter, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);


    for (int i = padding_size; i < image.rows - padding_size; i++)
    {
        for (int j = padding_size; j < image.cols - padding_size; j++)
        {
            float horizontal_sum = 0.0;
            float vertical_sum = 0.0;

            for (int i1 = -padding_size; i1 <= padding_size; i1++)
            {
                for (int j1 = -padding_size; j1 <= padding_size; j1++)
                {
                    horizontal_sum += image.at<uchar>(i + i1, j + j1) * sobel_filter_horizontal.at<int>(i1 + padding_size, j1 + padding_size);
                    vertical_sum += image.at<uchar>(i + i1, j + j1) * sobel_filter_vertical.at<int>(i1 + padding_size, j1 + padding_size);
                    //  std::cout << image.at<float>(i + i1, j + j1) << " " << sobel_filter_horizontal.at<float>(i1 + 1, j1 + 1) << " " << sobel_filter_vertical.at<float>(i1 + 1, j1 + 1) << "\n";
                }
            }

            image.at<uchar>(i - padding_size, j - padding_size) = sqrt(horizontal_sum * horizontal_sum + vertical_sum * vertical_sum);
        }
    }

    return image;
}

// invert image
Mat invert(Mat image)
{
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            image.at<uchar>(i, j) = 225 - image.at<uchar>(i, j);
            if (image.at<uchar>(i, j) != 0)
            {
                image.at<uchar>(i, j) -= 40;
            }
        }
    }
    return image;
}

// image segmentation for greyscale image
Mat image_segmentation(Mat image)
{
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (image.at<uchar>(i, j) < 100)
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

    glPointSize(1.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // Draw the spiral
    for (int i = 0; i < img.rows; ++i)
    {

        for (int j = 0; j < img.cols; j++)
        {
            m[0] += 0.002;
            // Draw the point

            if (img.at<uchar>(i, j) == 255)
            {

                glBegin(GL_POINTS);
                glVertex2f(m[0], m[1]);
                glEnd();
                // glFlush();
            }
        }

        m[1] -= 0.002;
        // If line 179 has been changed, change this accordingly
        m[0] = -0.002 * float(image.cols / 2);
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

void display_grey_scale()
{

    draw_grey_scale(image);

    // print(0, 0, 0, "Vashist");
}

void display_colour()
{
    draw_color(image);
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

    std::cout << "Enter the option you want to choose:\n1) Show the coloured Image\n2) Show the segmented grey Scale Image\n3) Show Edge detection of the Grey Scale Image.\n";

    int option;
    std::cin >> option;

    switch (option)
    {
    case 1:
        // Read Colour Image
        image = imread("chris_cornell.jpeg");
        glutDisplayFunc(display_colour);
        break;

    case 2:
        //  Read the image file. uncomment IMREAD_GRAYSCALE for reading in grey scale
        image = imread("chris_cronell.jpeg", IMREAD_GRAYSCALE);
        // segmentation of greyscale image
        image = image_segmentation(image);
        imwrite("cornellMod.jpg", image);
        glutDisplayFunc(display_grey_scale);
        break;

    case 3:
        //  Read the image file. uncomment IMREAD_GRAYSCALE for reading in grey scale
        image = imread("chris_cornell.jpeg", IMREAD_GRAYSCALE);
        // segmentation of greyscale image
        image = edge_detection(image);
        // invert the image
        image = invert(image);
        imwrite("cornellModgauss1.jpeg", image);
        glutDisplayFunc(display_grey_scale);
        break;

    default:
        break;
    }

    // test
    //  std::cout << image.rows << " " << image.cols << "\n";

    // save image

    // // Set the display function
    // glutDisplayFunc(display);

    m.push_back(0.002 * float(image.cols / 2));
    // change accrdingly in draw_color or draw_grey_scale
    m.push_back(0.0018 * float(image.rows / 2));

    // Enter the main loop
    glutMainLoop();

    return 0;
}
