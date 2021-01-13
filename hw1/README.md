# About
This is homework assignment 1 for COSC4370 Interactive Graphics. In this assignment, we must create 2 arcs of different radii (100, 150) for a 300+ by 300+ view. To do this we must save the point data into a image matrix, save the data into a ppm file, and rasterize this data for an opengl output using c++. In order to do this effectively, we must use the provided algorithms from the reading.pdf material.

# Development Enviornment
Windows<br/>
  * Installations<br/>
    * VcXsrv: allows for viewing output of opengl<br/>
  * IDE: Visual Studio Code<br/>

Ubuntu (via WSL):<br/>
  * apt-get packages<br/>
    ```sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev # for opengl```<br/>
    ```sudo apt install imagemagick # for displaying ppm file```<br/>
  * exports<br/>
    ```export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0;```<br/>
    ```export LIBGL_ALWAYS_INDIRECT=1;```<br/>

# References
Algorithms<br/>
  * Fig. 3.16 The integer midpoint circle scan-conversion "MidpointCircle" algorithm (pg. 86)<br/>
      * This algorithm was modified to include delta x and y arguments that will be added to the final point results so that the circle's center can be shifted from the bottom left to the center of the window. I renamed this modified algorithm to "circleIntegerMidpointScanConversion" for a more verbose name.<br/>
  * Fig. 3.3.1 Eight-Way Symmetry "CirclePoints" algorithm<br/>
      * I modified this algorithm to account for which quadrants to add the symmetry points to and accounting for the shift of the circle to the center using Fig. 3.13 (pg. 83)<br/>

# Run
```g++ main.cpp -o main -lglut -lGLU -lGL; ./main 300;```
```display circle300.ppm;```
