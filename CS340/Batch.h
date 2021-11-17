#include<string>
#include<vector>
#include "Job.h"
/*
    Batch

    A wacky machine will process a batch, which contains jobs.
    Is an implementation of a priority queue/binary heap.

    Author: Dr. Daniel Page
    Fall 2021
*/
#ifndef MACHINE_H
#define MACHINE_H
class Batch {
private:
    std::vector<Job> jobs;
    int numJobs;//number of jobs in the batch
    int totalLength;//the total length of all jobs in the batch.
    void bubbleUp(int pos);//for bubbling up jobs.
    void bubbleDown(int pos, int end);//for bubbling down jobs.
    void swap(int j, int p);//swap the contents of the two positions.
public:
    Batch();//Constructor
    void insertJob(Job job);//insert a new job
    Job minJob();//return the job with highest priority (lowest value), throws message if empty.
    Job removeMinJob();//remove the job with the highest priority (lowest value), throws message if empty.
    void merge(Batch batch);//merge the jobs 
    int getNumJobs();//number of jobs currently in the batch.
    int getTotalLength();//the total length of all the jobs in the batch.
    bool isEmpty();//is the batch of job empty?
    int getSize();//the size of the vector
    std::string toString();//output job information of batch
};
#endif /* BATCH_H */
