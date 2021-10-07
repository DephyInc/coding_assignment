#include "datafile.hpp"
#include "proto.hpp"


/*********************************************
                  align_data
*********************************************/
DataFile* align_data(DataFile* dataFiles, int n)
{
    /***
    Determines which file has the earliest first peak and then shifts
    the arrays of every file such that the first peak occurs at the
    same time.
    ***/
    int i;
    int j;
    int earliestIdx = 0;
    float earliestTime = dataFiles[0].get_times()[dataFiles[0].firstPeakIndex];
    float curTime;
    float diff;
    float* times;

    // Find out which file's first peak occurs at the earliest time
    for (i=1; i<n; i++)
    {
        times = dataFiles[i].get_times();
        curTime = times[firstPeakIndex];

        if (curTime < earliestTime)
        {
            earliestIdx = i;
            earliestTime = curTime;
        }
        delete[] times;
    }

    // Determine the difference between the first peak time for each
    // file and the file with the earliest first peak. We then shift
    // the times of the later file by that amount
    for (i=0; i<n; i++)
    {
        times = dataFiles[i].get_times();
        curTime = times[firstPeakIndex];
        diff = curTime - earliestTime;

        for (j=0; j<dataFiles[i].nRecords; j++)
        {
            dataFiles[i].shiftedTimes[j] = times[j] - diff;
        }
        delete[] times;
    }

    return dataFiles;
}
