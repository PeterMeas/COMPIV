# PS2: Triangle Fractal

## Contact
Name: Peter Meas
Section: 201

Partner Name: N/A
Partner Section: N/A

Time to Complete: 3 days


## Description
Explain what the project does.
This project implements a Sierpinski Triangle fractal using SFML graphics library. The program takes two command-line arguments: the side length of the initial triangle (L) and the recursion depth (N). It creates a visually appealing fractal pattern with different colors for each recursion level.

### Features
Describe what your major decisions were and why you did things that way.  How did you represent fractal elements and how did you compute their positions?

Each triangle is represented using SFML's ConvexShape with 3 points
Points are arranged to create downward-pointing triangles:

"shape.setPoint(0, sf::Vector2f(0, height/2));     // Bottom point
shape.setPoint(1, sf::Vector2f(-L/2, -height/2)); // Top left
shape.setPoint(2, sf::Vector2f(L/2, -height/2));  // Top right"

Positions are computed using the centroid of the triangle and the side length. Size of the smaller/child triangles sides are half the size of the parent triangle, calculated by the midpoints from A to B, A to C, and B to C. The height, centroid, and side length were really important calculations, the height was calculated using the pythagorean theorem, the centroid was calculated by using the midpoint of the base of the triangle, and the side length was given as a command line argument. Also recursive depth is given through second command line argument.

I also added input validation to check if the command line arguments are valid. If not, the program will exit with an error message. I also added window size to be calculated based on the side length of the triangle to make sure the triangle is not cut off or overextends past the window.
         C
         /\
        /  \
       /    \
      /      \
     /        \
    /          \
A  /            \ B



Child triangle positions are calculated using carefully calibrated offsets:

// Bottom triangle
centroid.x - L/4, centroid.y + height/1.33

// Left triangle
centroid.x - L/1.99, centroid.y - height/1.33

// Right triangle
centroid.x + L/1.33, centroid.y - height/4

These specific ratios (1.33, 1.99) were chosen because they:

Maintain proper point-to-point contact between triangles
Create the correct visual spacing for the Sierpinski pattern
Ensure triangles are properly oriented (pointing downward)


Color Implementation:
I tried implementing a function that Fractal would call to get the color of the triangle based on the recursion level. Each recursion level has a unique color Colors cycle through a rainbow pattern (purple, indigo, blue, green, yellow, orange) Color selection is based on recursion depth using modulo operator

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I had trouble with the ratios of the child triangles, I had to play around with them to get the correct spacing between triangles. I also had trouble with the colors, I had to play around with them to get the correct colors for each recursion level.

Initially attempted to use exact mathematical positions (height/2, L/2), but this caused orientation issues Found that slightly adjusted ratios produced better visual results while maintaining the correct fractal pattern
The current implementation prioritizes visual correctness over pure mathematical precision

Also, getting triangles to point in the correct direction was challenging
I felt like I solved by carefully setting the initial triangle points and maintaining consistent orientation through recursion

### Extra Credit
Anything special you did.  This is required to earn bonus points.

Color Implementation:
I added a function that would get the color of the triangle based on the recursion level. I also added a rainbow pattern to the colors. I created a visually appealing rainbow pattern throughout the fractal the colors help visualize the recursive structure of the pattern
## Pair Programming
How did working with a partner affect your work?
did not work with partner

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

SFML Documentation for graphics implementation
Course materials and lectures on fractals

https://www.sfml-dev.org/tutorials/2.6/graphics-shape.php
https://www.geeksforgeeks.org/sierpinski-triangle/
https://www.geeksforgeeks.org/sierpinski-triangle-set-2/
https://www.geeksforgeeks.org/sierpinski-triangle-set-3-using-c-opengl/



