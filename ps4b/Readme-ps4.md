# PS4: Sokoban

## Contact
Name: Peter Meas
Section: 201
Time to Complete: A week


## Description
Explain what the project does.
this project implemented a Sokoban puzzle game through SFML graphics. The game is basically players pushing boxes to a designated storage location in the grid based UI. through this, they have to
navigate through walls and empty spaces

### Features
Describe what your major decisions were and why you did things that way.

i used a 1d vector to represent the 2d grid for efficient memory usage, i implemented a row
major order grid representation for easy indexing and i also seperated the inital and current game states to support a reset option
-Level loading from files
    - in order to play game 
-Gameplay with both WASD and arrow keys
     - can play with both if want
-Box pushing mechanics with collision detection
    - in order to follow gam erules 
-Win condition, printing "You Win" on win when all boxes placed in storage areas
    - message for player indicating they won the game, also pauses charater cant move until hit reset button

#### Part a
i was able to successfully load level data from a text file, through the given folder i drew
game tiles using SFML sprites 
different tile types render well with this basic grid i implemented
i also created a drawable Sokoba class, which can load and display levels

#### Part b

Implemented gameplay mechanics including 
player movement with WASD and arrow keys, wall colision detection in order to prevent invalid moves, implemented box pushing mechanics that follow game rules, created a win condition function that detected game state, implemented level reset functionality and game displays a victory message upon winning

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

i stored the level data in a vector of chars, this is for dynamic memory allocation
i also used standard containers to prevent memory leaks
i had seperate vectors for the current and initial game state in order for the reset to work 



### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I used the std::count_if algorithm from the algorithm header with three lambda expressions to implement the win condition logic:

1. `BoxNotOnStorage`: A lambda that identifies boxes not on storage areas `[](char c) { return c == 'A'; }`
2. `StorageWithoutBox`: A lambda that identifies empty storage areas `[](char c) { return c == 'a'; }`
3. `BoxOnStorage`: A lambda that identifies boxes placed on storage areas `[](char c) { return c == '1'; }`

These lambda expressions, combined with std::count_if, allow me to calculate
- How many boxes are not on storage spots
- How many storage spots are empty
- How many boxes are correctly placed on storage

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I had trouble with the tests, and I'm unable to write tests that pass 1.3, 1.4,1.5,1.6 and 1.9.
All else seems to work.

at first i had trouble understanding the grid representation, debugging the texture and sprite loading/position and alsp making sure the correct coordinates were being mapped between the grid and pixel space

I learned alot about matrices in coding in class, and using lambda functions , actually using them
Also a little sbout how games are made, we made simple sokoban game and this can give a lot of insight into more complicated games
### Extra Credit
Anything special you did.  This is required to earn bonus points.


## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Course materials and examples provided in class
SFML documentation for graphics rendering
Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
