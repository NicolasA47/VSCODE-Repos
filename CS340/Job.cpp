#include "Job.h"

/*
Job class.  The fundamental task for Dan's Wacky Machine.
Author: Daniel Page
Fall 2021
*/

/*
Constructor
*/
Job::Job(std::string id, int priority, int length) {
    this->id = id;
    this->priority = priority;
    this->length = length;
}


/*
getPriority
Inputs: (None)
Returns: Priority of the job, priority.
*/
int Job::getPriority() {
    return priority;
}

/*
getLength
Inputs: (None)
Returns: Length of the job, length
*/
int Job::getLength() {
    return length;
}

/*
toString
Inputs: (None)
Returns: std::string that represents the job.
*/
std::string Job::toString() {
    return id + "," + std::to_string(getPriority());
}