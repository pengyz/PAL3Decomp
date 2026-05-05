#include "gbengine/gbMisc.h"
#include <windows.h>

// High-precision timer using QueryPerformanceCounter

void gbTimeCounter::On() {
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&startTime);
    elapsed = 0.0;
}

double gbTimeCounter::Off() {
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);

    // Calculate elapsed time in seconds
    elapsed = (double)(endTime.QuadPart - startTime.QuadPart) / (double)freq.QuadPart;
    timestamp = elapsed;

    return elapsed;
}

gbTimeCounter& gbTimeCounter::operator=(const gbTimeCounter& other) {
    if (this != &other) {
        startTime = other.startTime;
        freq = other.freq;
        elapsed = other.elapsed;
        timestamp = other.timestamp;
    }
    return *this;
}
