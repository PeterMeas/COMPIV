# PS6: RandWriter

## Contact
Name: Peter
Section: 201
Time to Complete: 15 hrs


## Description
Explain what the project does.

Project implemented a psuedo-random text generator using a Markov model of order k
Given input text, analyzes kgram and the characters that follow them, generating
new text which mimics the character level structure of original input
### Features
Describe what your major decisions were and why you did things that way.
Built a RandWriter class that constructs the frequency model from text input
Implemented
`freq(kgram)` and `freq(kgram, c)` to return frequencies.
`kRand(kgram)` to choose the next character using weighted random selection.
`generate(kgram, L)` to create new text of length L based on the model.
- Used `std::map` and `std::string` for internal data storage.
- Used `std::discrete_distribution` from `<random>` to ensure generated characters match the learned probabilities.
- Implemented `operator<<` to print out the internal model.

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?

I wrote unit tests to test the following:

kRand() returns a valid next character that follows the given kgram in the input
generate() produces output of the correct length and format, starting with the given seed
All generated characters correctly follow the k-gram frequency model
Exception handling is tested using BOOST_REQUIRE_THROW for cases where kgram length is incorrect or the kgram doesn’t exist
my code passed the tests against kzero, wrong length, wrong start, and wrong distribution but failed the no error checking test because i didnt explicitly check for exception throwing against a wrongful implementation, i later corrected this

### Lambda
What does your lambda expression do?  What function did you pass it to?

I used a lambda inside the operator<< function to iterate over the alphabet when printing
The lambda was passed to std::for_each, handling special character formatting  which was
space, newline, tab, when printing the alphabet to output stream
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

everything seems to be working fine except failing one unit test, where i later fixed by explicitly checking for exception throwing 

Forgot to store the text and k in the constructor, which led to bugs during runtime, but i fixed it after realizing those were needed across methods.
Learned a lot about using STL containers like map, and about std::random tools like discrete_distribution

### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
Instructor , course slides
cplusplus.com for STL ref
Boost documentation 