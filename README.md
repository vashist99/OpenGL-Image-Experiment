# OpenGL-Image-Experiment

This is a simple project that renders a given image in using OpenGL vertex rendering after image segmentation of the original image. This project uses both OpenGL and OpenCV for C++.

#### Please not the output of this project is not extraordinary, but the effort was real.

## Requirements:

You will need OpenGL and OpenCV installed for C++ in your machine

## How to run:

`` $g++ Imageart.cpp -lcurl -lgdal -ltiff -lglut -lGLU -lGL `pkg-config --cflags --libs opencv`  ``

`$./a.out`

## Results:
### Original Image:
<img src="https://github.com/vashist99/OpenGL-Image-Experiment/blob/master/chris_cornell%20_small1.png" width="230" height="300">

### After Processing:
<img src="https://github.com/vashist99/OpenGL-Image-Experiment/blob/master/Cornell_Result.jpg" width="400" height="300">


