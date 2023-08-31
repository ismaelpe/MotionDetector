# MotionDetector

This project may be used to detect any moves in a scene. The algorithm is very simple:

1. Get Orginal image from source.
2. Transform it in gray scale.
3. Save last gray image and substract with current image.
4. Calculate then mean of de the substract operation and apply a threshold.
5. If the mean is greather than the threshold there is some move in the scene.

## Requisites
You must install OpenCV in your computer, visit OpenCV to compile with C/C++.

## To Compile use

Go to the project's path, open a terminal and type the following commands:

´´´
mkdir build
cd build
cmake ..
make
´´´
