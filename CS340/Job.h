#include<string>
#ifndef JOB_H
#define JOB_H
/*
Job class.  The fundamental task for Dan's Wacky Machine.
Author: Daniel Page
Fall 2021
*/
class Job{
    private:
        std::string id;//the job has an id.
        int priority;//it has a priority, smalleer the value, the more important it is.
        int length;//how long it takes to process the job.
    public:
        Job(std::string id,int prior, int len);
        int getPriority();//get the priority of the job.
        int getLength();//get the length of the job.
        std::string toString();//print information
};
#endif /* JOB_H */
