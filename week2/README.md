# Week 2 Tasks

## Time and benchmarking

In this practical, I used the `time` command to measure how long different programs took to run. This showed the difference between real time, user time, and system time, and introduced a simple way of benchmarking code from the terminal.

## C vs Python Hello World! Run Time

Below is the output from running both `hello_world.py` and the compiled version of `hello_world.c`:

time python3 ./PHY1090/week2/hello_world.py  
Hello, World!

real    0m0.032s  
user    0m0.022s  
sys     0m0.008s  

time ./bin/hello_world  
Hello, World!

real    0m0.007s  
user    0m0.000s  
sys     0m0.005s  

From this, it can be seen that the C version ran faster than the Python version. Even though both programs were very small, the compiled C code still had a lower total runtime.

## C vs Python Repeat Adder

The C version of `repeat_adder` ran successfully. The Python version from the sample files did not run at first because of indentation errors, so this had to be corrected before it could be tested properly.

## Internal Timing

I then tested the `time_print` program in C with a few different input values.

For input `3`, the core loop runtime was `0.000135 seconds`, with a wall-clock time of `0.006s`.

For input `10`, the core loop runtime was `0.000203 seconds`, with a wall-clock time of `0.005s`.

For input `100`, the core loop runtime was `0.000191 seconds`, with a wall-clock time of `0.004s`.

For input `1000`, the core loop runtime was `0.000362 seconds`, with a wall-clock time of `0.004s`.

These results showed that the internal timing was more useful for measuring the actual loop, while the external `time` command mostly reflected the total runtime and system overhead. Since these programs were so small, the real time stayed almost the same even as the input increased.

The Python `time_print.py` file also had to be corrected before it would run, as the original sample code contained a syntax error.

## File I/O Timing

I made a modified version of the C timing code called `time_write`. This program takes an integer input and writes the numbers to a file called `i_o_time_c.txt` instead of printing them to the terminal.

Running `time_write 10` gave an internal runtime of `0.000030 seconds`, with a wall-clock time of `0.009s`. The output file was created successfully and contained the numbers 0 to 9.

I also made a corresponding `time_read` program, which reads the file back into memory and reports the runtime.

Running `time_read` gave an internal runtime of `0.026564 seconds`, with a wall-clock time of `0.031s`.

From this, it can be seen that reading the file took longer than writing it in my test.

## Conclusions

Overall, this practical showed that runtime depends on both the language being used and the type of operation being carried out. In the simple Hello World test, the C version was faster than the Python version. Internal timing was also more useful than the Linux `time` command for measuring small sections of code, because it isolated the actual computation from general program overhead.

The file I/O tests showed that reading from a file took longer than writing to it in this case.
