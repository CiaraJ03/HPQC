#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double to_second_float(struct timespec in_time);
struct timespec calculate_runtime(struct timespec start_time, struct timespec end_time);

int main()
{
    struct timespec start_time, end_time, time_diff;
    double runtime = 0.0;

    timespec_get(&start_time, TIME_UTC);

    FILE *f = fopen("i_o_time_c.txt", "rb");

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *data = malloc(size + 1);
    if (data == NULL)
    {
        fprintf(stderr, "Error allocating memory.\n");
        fclose(f);
        exit(-1);
    }

    fread(data, 1, size, f);
    data[size] = '\0';

    fclose(f);

    timespec_get(&end_time, TIME_UTC);

    time_diff = calculate_runtime(start_time, end_time);
    runtime = to_second_float(time_diff);

    printf("\n\nRuntime for file read: %lf seconds.\n\n", runtime);

    free(data);

    return 0;
}

double to_second_float(struct timespec in_time)
{
	// creates and initialises the variables
	float out_time = 0.0;
	long int seconds, nanoseconds;
	seconds = nanoseconds = 0;

	// extracts the elements from in_time
	seconds = in_time.tv_sec;
	nanoseconds = in_time.tv_nsec;

	// calculates the time in seconds by adding the seconds and the nanoseconds divided by 1e9
	out_time = seconds + nanoseconds/1e9;

	// returns the time as a double
	return out_time;
}

struct timespec calculate_runtime(struct timespec start_time, struct timespec end_time)
{
	// creates and initialises the variables
	struct timespec time_diff; long int seconds, nanoseconds; seconds = nanoseconds = 0; 
	double runtime = 0.0;
	// extracts the elements from start_time and end_time
	seconds = end_time.tv_sec - start_time.tv_sec;
	nanoseconds = end_time.tv_nsec - start_time.tv_nsec;

	// if the ns part is negative
	if (nanoseconds < 0)
	{
		// "carry the one!"
		seconds = seconds - 1;
		nanoseconds = ((long int) 1e9) - nanoseconds;
	}

	// creates the runtime
	time_diff.tv_sec = seconds;
	time_diff.tv_nsec = nanoseconds;

	return time_diff;
}

