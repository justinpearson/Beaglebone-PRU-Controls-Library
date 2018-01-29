#ifndef UTILJPP_H
#define UTILJPP_H

#include <time.h> // usleep, clock_gettime
#include <stdio.h> // FILE*

double wrapMax(double x, double max);
double wrapMinMax(double x, double min, double max);

void timespec_diff(struct timespec *start, struct timespec *stop, struct timespec *result);

double ts_to_sec( struct timespec ts );

// Need to compile with -lrt to get CLOCK_REALTIME 
void toc(double* sec_since_start, double* sec_since_last );

void print_local_time(FILE* fp);

#endif  // header guard
