# PS1: LFSR / PhotoMagic

## Contact
Name: Peter meas

Section: 201

Time to Complete:
6-9 hours


## Description
Explain what the project does.
The project had us create a FibLFSR class representing a linear feedback shifter as 16 bits and inside this class, we had to write functions that would modify the state of the register, the "step" and "generate" functions. The step being the calculation fucntion where a feedback bit would be calculated from XORing bit 15 and the taps, at position 13,12,and10. The genereate function would work off of the step function, basically "how many times do you want the step functoin to run"

The project starts with an image and a seed. The seed is used to encrypt the image by changing the pixel values. Each pixel's RGB values are altered using the FibLFSR class's generate function. This function produces an 8-bit number, which is used for the RGB values (ranging from 0 to 255). After the image is encrypted, it can be decrypted using the same seed. When the same method is applied to the encrypted image, the original image is restored. This works because XOR is its own inverse: applying the same XOR operation twice with the same key restores the original value.

### Features
Describe the representation you used and why you did things that way as well as any other interesting design decisions you made.

#### Part a
I made test units for exception handling to make sure an exception was thrown whenever a conditon was satisfied/not satisfied, i added tests for the generate functoin, step function, and to make sure '<<' operator was functioning correctly. All this was done through the representation of the bitset function
from the STL library. I used this to represent the 16 bit LFSR state because it provides methods already built
in for bit manipulation, being able to shift, access individual bits, and it also ensures regsiter is always 16 bits which prevents invalid states
#### Part b
I chose a nested for loop for the transform function to go through the chosen images (x,y) in row-major order. I made corresponding
variables to store the individual color channels, one each for red green and blue. This was done so i could store a new value
which was made up of XORing the original extracted color with a value from the generate function from the LFSR. 8 bit numbers were 
generated due to it being the max these channels can hold.
Also made sure user has to enter 3 arguments, "input.png output.png LFSR_Seed" or else it would prompt an error message



### Issues
What doesn't work.  Be honest.  You might be penalized if you claim something works and it doesn't.
Everything seems to be working
### Tests
Describe what is being tested in your Boost unit tests.

I wrote the following unit tests to verify the correctness of my implementation:

1. testStep:
   - Tests the `step()` method by verifying the output of the first few steps.
   - Ensures the feedback bit is computed correctly using the specified tap positions.

2. testGenerate` :
   - Tests the `generate()` method by extracting x amount of bits and verifying the result.
   - Ensures the bits are combined in the correct order.

3.`testOutputOperator`:
   - Tests the `<<` operator by verifying the output matches the current state of the LFSR.

4.testInvalidConstructor
    - Verifies the constructor behavior with invalid input, ensures proper exception handling when the constructor is provided invalid data, and checks that valid data does not cause errors.
5.testInvalidGen
    -Veries behavior of gen function with invalid input

### Extra Credit
Anything special you did. This is required to earn bonus points.
N/A

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
Community discord with linting/makefile issues

### Credits
List where you got any images or other resources.
SFML documentation