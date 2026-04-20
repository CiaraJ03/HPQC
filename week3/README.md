# Week 3 – Introduction to MPI

Note: I was unable to reconnect to the physics server after completing the practical work. Because of this, I was able to upload the write-up and results through GitHub in the browser, but was unable to commit the code.

## Part 1 – MPI Hello World

For the first part of the practical, I created my own MPI Hello World program in C. The program initialised MPI, obtained the rank of each process and the total number of processes in `MPI_COMM_WORLD`, printed a message from each process, and then finalised MPI. This follows the practical requirement to create, compile, and run an MPI Hello World program using `mpicc` and `mpirun`.

The program was compiled with:

    mpicc hello_mpi.c -o ~/bin/hello_mpi

and run with:

    mpirun -np 4 ~/bin/hello_mpi

This demonstrated that each process runs the same program, but with a different rank.

## Part 2 – Breakdown of `proof.c`

In the second part of the practical, I examined `proof.c` and broke down the purpose of each function.

### `main()`
`main()` sets up the MPI program. It checks the command-line arguments, starts MPI, gets the current process rank and the total communicator size, checks that the communicator size is valid, and then sends each process to the correct task. At the end, it finalises MPI.

### `check_args()`
`check_args()` checks whether the user has provided the correct number of command-line arguments. If a valid numerical argument is given, it converts it from a string to an integer. If not, it prints an error and exits.

### `check_uni_size()`
`check_uni_size()` checks that there are enough MPI processes available for the program to run properly. If the communicator size is too small, it prints an error and exits.

### `check_task()`
`check_task()` decides which function each process should run based on its rank. Rank 0 is assigned the root task, while all other ranks are assigned the client task.

### `root_task()`
`root_task()` is performed by rank 0. It receives one integer message from every other process using `MPI_Recv()`, adds these values together into a running total, and then prints the combined result.

### `client_task()`
`client_task()` is performed by all non-root processes. Each client calculates a value using its rank and the numerical argument, then sends that result to the root process using `MPI_Send()`.

### Overall logic
The program uses a root-client structure. The root process collects results from all client processes and combines them, while each client process carries out a local calculation and sends its result to the root.

## Part 3 – MPI Vector Addition

### Serial version
I first compiled and ran the provided serial program:

    gcc PHY1090/week3/vector_serial.c -o ~/bin/vector_serial
    time ~/bin/vector_serial 10

The output was:

    Sum: 0

    real    0m0.005s
    user    0m0.000s
    sys     0m0.004s

This showed that the original program was a trivial example, because the vector contained only zeroes and so the sum was always zero. The practical specifically says to modify this so that the vector is non-trivial.

### Modified serial version
I made my own copy of the serial program and changed the vector so that each element was set to `i + 1` instead of zero. This made the vector contain meaningful values.

For input `10`, the modified serial version gave:

    Sum: 55

    real    0m0.006s
    user    0m0.004s
    sys     0m0.001s

For input `1000`, it gave:

    Sum: 500500

    real    0m0.005s
    user    0m0.004s
    sys     0m0.001s

For input `100000`, after changing the sum type to `long long int` to avoid overflow, it gave the correct result:

    Sum: 5000050000

This made the serial version non-trivial and suitable for comparison with a parallel implementation.

### Parallel MPI version
I then created an MPI version of the vector summation program. In this version, the vector was partitioned logically into chunks based on the number of processes. Each process calculated the sum of its own chunk, and the partial sums were combined into a final total using `MPI_Reduce()`.

The MPI version was compiled with:

    mpicc vector_mpi.c -o ~/bin/vector_mpi

and run with:

    mpirun -np 4 ~/bin/vector_mpi 10

For input `10`, the MPI version gave:

    Sum: 55

For input `1000`, it gave:

    Sum: 500500

For input `100000`, after also changing the MPI sum variables to `long long int`, it gave:

    Sum: 5000050000

This showed that the MPI program was functionally correct and matched the results of the serial version.

### Benchmarking serial vs parallel
I compared the runtime of the modified serial program and the MPI version.

For input `10`:

Serial:
    real    0m0.006s

MPI:
    real    0m0.432s

For input `1000`:

Serial:
    real    0m0.005s

MPI:
    real    0m0.436s

For input `100000`:

Serial:
    real    0m0.009s

MPI:
    real    0m0.429s

These results showed that the MPI version was much slower than the serial version for all of the tested input sizes. Although the MPI version worked correctly, the overhead of creating and coordinating multiple processes was much larger than the cost of doing the calculation in serial. This means that for this simple task and the tested input sizes, parallelism was not beneficial. This fits with the practical note that a small and simple program may not scale well on a small parallel system. :contentReference[oaicite:7]{index=7}

## Conclusion

This practical introduced the basic structure of MPI programs and showed how multiple processes can work together on the same problem. The MPI Hello World example demonstrated the use of `MPI_Init()`, `MPI_Comm_rank()`, `MPI_Comm_size()`, and `MPI_Finalize()`. The analysis of `proof.c` showed how root and client processes can communicate using `MPI_Send()` and `MPI_Recv()`.

In the vector addition exercise, I first worked with the provided serial code, then modified it to make it non-trivial, and finally created a parallel MPI version. Both the serial and MPI versions produced the same correct sums once the integer overflow issue was fixed by using `long long int`. However, the MPI version was much slower than the serial version for all the input sizes I tested. This suggests that MPI overhead dominated the runtime, so the problem was too small and simple for parallelism to provide an advantage.
