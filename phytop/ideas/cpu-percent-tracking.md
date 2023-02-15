# CPU-Percent-Tracking

The phytop program will optionally allow the user to select a percentage of their CPU power to consume in order to execute the simulation and render the results.

The phytop program will implement a feedback-control system.

1. reads phytop current percent usage of CPU
2. compares it to the desired percentage of CPU usage
3. calculate error (measured - desired)
4. calculate proportional, integral, and differential gain coefficients
5. sum those three P, I, D 
6. based on the sum, change the amount of time you sleep() each iteration.  i.e. if you are using 14% CPU instead of your desired 10% CPU, so the program needs to increase the amount of idle time in each screen repaint.

