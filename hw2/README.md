# About
This is homework assignment 2 for COSC4370 Interactive Graphics. In this assignment, we must create 2 out of the 3 pictures in the hw2.pdf as well as create a rough wireframe hand according to the fake hand picture provided (problem3() function). I chose picture 1 for problem1() function (teapots that are rotated in a circle formation) and picture 2 for problem2() function (horizontal boxes that are scaled up the farther tranlated right it is). This requires pipeline knowledge in opengl to effectively recreate the models. There are a total of 3 "problems" that are modeled.

# Development Enviornment
Windows<br/>
  * Installations<br/>
    * VcXsrv: allows for viewing output of opengl<br/>
  * IDE: Visual Studio Code<br/>

Ubuntu (via WSL):<br/>
  * apt-get packages<br/>
    ```sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev # for opengl```<br/>
  * exports<br/>
    ```export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0;```<br/>
    ```export LIBGL_ALWAYS_INDIRECT=1;```<br/>

# References
Formulas
  * trigonometry sin and cos laws<br/>
    * x = r * cos(theta)
    * y = r * sin(theta)

# Program 
Run<br/>
```g++ main.cpp -o main -lglut -lGLU -lGL; ./main;```<br/>

Controls<br/>
* right arrow: next problem<br/>
* left arrow: previous problem<br/>
