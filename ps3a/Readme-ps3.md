# PS3: N-Body Simulation

## Contact
Name: peter meas
Section: 201
Time to Complete: 18 hrs


## Description
Explain what the project does.

This project simulates the motion of celestial bodies (e.g., planets, the Sun) in a 2D plane using Newtonian physics. The program reads the initial state of the universe (positions, velocities, masses, and images of celestial bodies) from a file and renders the simulation in an SFML window.

### Features
Describe what your major decisions were and why you did things that way.

Implemented a new step function that updates the positions and velocities of the celestial bodies based on the gravitational forces acting on them.
The step function basically implemented newtons law of universal graviation with O(n^2) force calculations. This added leapfrog integration, momentum conservation, and energy tracking to my program.
    - uses delta t based time stepping for numerical stability
    - fores applied symmetrically
    - used smart pts for texture mangament and celestial body storage


CelestialBody Class:
I created a CelestialBody class to represent each celestial body (e.g., planets, the Sun). This class stores properties like position, velocity, mass, and an image. I chose to use SFML’s sf::Sprite and sf::Texture to handle rendering because they make it easy to load and display images.
Universe Class:
The Universe class manages a collection of CelestialBody objects. It reads data from a file (e.g., planets.txt) and handles rendering all the bodies in the SFML window. I decided to use a std::vector to store the bodies because it’s efficient and easy to work with.
Scaling and Positioning:
To ensure the planets were displayed correctly, I implemented scaling and positioning logic in the CelestialBody constructor. This calculates the screen positions based on the universe radius and window size. I chose to do this in the constructor to avoid recalculating positions every frame, which improved performance.
File Input:
The program reads the initial state of the universe from a file. I decided to use a simple text format for the input file because it’s easy to parse and modify. This made it straightforward to test different universes.


### Memory
Describe how you managed the lifetimes of your objects, including if you used smart pointers.



I used std::shared_ptr to manage the lifetime of sf::Texture objects. This ensured that textures weren’t destroyed prematurely, which could cause rendering issues (e.g., white squares instead of images). 

The Universe class owns the CelestialBody objects. Celestial bodies are stored in a std::vector in the Universe class, simplifying memory management and access. This approach made it easy to add, remove, and access celestial bodies without worrying about memory leaks.

By calculating scaling and positioning in the constructor, I avoided recalculating these values every frame, which improved performance and reduced memory usage.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I ran into a few challenges while working on this project:

Black Screen Issue:
Initially, the program only displayed a black screen. After adding debug output, I realized the scaling factor was too small, making the planets invisible. I fixed this by adjusting the scaling logic and ensuring the positions were calculated correctly.
Linker Errors:
I encountered linker errors because the default constructor for CelestialBody was missing. This was resolved by explicitly defining the default constructor.
Image Loading:
At one point, the images weren’t loading correctly because the file paths were incorrect. I fixed this by ensuring the image files were in the correct directory and using absolute paths if necessary.
What I Learned:
I learned a lot about SFML rendering, smart pointers, and debugging techniques. This project helped me understand how to manage object lifetimes and optimize performance in a graphical application.

What Doesn’t Work:
Currently, the simulation is static (Part A of the assignment) and works correctly. The planets don’t move or interact with each other. This will be implemented in Part B. 

### Extra Credit
Anything special you did.  This is required to earn bonus points.
If you created your own universe file.  Describe it here and explain why it is interesting.
N/A

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

https://en.sfml-dev.org/forums/index.php?topic=15795.0
https://en.sfml-dev.org/forums/index.php?topic=29597.0
https://www.sfml-dev.org/documentation/2.6.1/
https://www.geeksforgeeks.org/smart-pointers-cpp/
https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one&ved=2ahUKEwiwh7S2vNuLAxWJGFkFHeoHMaIQFnoECBwQAQ&usg=AOvVaw1KjwNjcT-BTUQhvMpHOAxT
https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://stackoverflow.com/questions/63406345/smart-pointers-in-c-98&ved=2ahUKEwiwh7S2vNuLAxWJGFkFHeoHMaIQrAIoAHoECBoQAQ&usg=AOvVaw3eu-sGo1JdROaO1dHsCEdH
https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://en.cppreference.com/book/intro/smart_pointers&ved=2ahUKEwiwh7S2vNuLAxWJGFkFHeoHMaIQFnoECBEQAQ&usg=AOvVaw2RIdF8ektbg8TgUzMTJz7f
https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp%3Fview%3Dmsvc-170&ved=2ahUKEwiwh7S2vNuLAxWJGFkFHeoHMaIQFnoECBYQAQ&usg=AOvVaw1r6BxcI5h1AjzEOrCfoJml
https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://en.sfml-dev.org/forums/index.php%3Ftopic%3D28521.0&ved=2ahUKEwjkta_EvNuLAxVvEGIAHadbDQIQFnoECAkQAQ&usg=AOvVaw0Sh5vJqcgkHBvzCTnW27Qo
COMP4 Discord server
