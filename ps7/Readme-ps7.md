# PS7: Kronos Log Parsing

## Contact
Name: peter meas
Section: 201 
Time to Complete:2 days


## Description
Explain what the project does.
This project parses Kronos InTouch time clock logs to analyze device boot processes. It identifies boot start and completion events, calculates boot duration, and generates a report showing the boot history of the device. The program handles both successful boots and failed boots.

### Features
Describe what your major decisions were and why you did things that way.

Parses log files using regular expressions to identify boot start and completion events
Detects incomplete boot sequences and reports them appropriately
Generates a report with summary statistics and detailed boot information

### Approach
Describe your overall approach to solving this problem.

I divided this problem into several parts:

First, I created regular expressions to identify the start and completion patterns described in the specification
Then I implemented a line-by-line parser to scan through the log file
I tracked the state of boot processes using boolean flags to identify incomplete boots
I used Boost's date/time library to calculate time differences between boot events
Finally, I generated a formatted report with both summary and detailed information

### Regex
What regular expressions did you use?  Explain what each one does.

Boot Start Pattern:

(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}): \(log\.c\.\d+\) server started
This matches a timestamp in ISO format (YYYY-MM-DD HH:MM), followed by a colon, followed by the text "(log.c.XXX) server started" where XXX is any number of digits. It captures the timestamp in group 1

Boot Completion Pattern:

(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})(?:\.\d{3})?:INFO:oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:\d{4}
This matches a timestamp in ISO format, optionally followed by milliseconds, followed by :INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0: and then a 4-digit port number. It captures the timestamp in group 1

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

The most challenging part was handling the timestamp format correctly. Initially I assumed the wrong format which led to parsing errors. I also had to be careful with the boot state tracking to properly handle incomplete boots and unexpected completion events.

Failed tests for endtime log3 and endtime log 6
else everything works correct

### Extra Credit
Anything special you did.  This is required to earn bonus points.

I implemented the summary header as specified in the extra credit section. The report now begins with a summary section showing total lines processed, number of boot starts found, and number of boot completions found.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
Boost library documentation for timestamp handling
Class noteso n regex processing
C++ reference documentation for regex syntax and features