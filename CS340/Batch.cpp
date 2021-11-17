#include "Batch.h"

Batch::Batch() { //constructor 
	std::vector<Job> jobs;
	this->numJobs = 0;
	this->totalLength = 0;
}

void Batch::bubbleUp(int pos) //for bubbling up jobs.
{
	int parentPos;
	do
	{
		parentPos = ((pos - 1) / 2);		//get parent position
		if (jobs[pos].getPriority() >= jobs[parentPos].getPriority())		//if priority is greater or equal then break out
		{ 
			break;
		}
		else                                                                //else swap the jobs at position with the job at parent position then make position = parents position
		{
			swap(pos, parentPos);
			pos = parentPos;
		}

	} while (pos > 0);		//while the position is greater than zero
}

void Batch::bubbleDown(int pos, int end) 
{
	int leftChildIndex = (2 * pos) + 1;		//define left and right child indicies 
	int rightChildIndex = (2 * pos) + 2;
	int smallestChildIndex = leftChildIndex;	//smallest child is the left 


	while (leftChildIndex <= end)
	{
		smallestChildIndex = leftChildIndex;
		if (rightChildIndex <= end)		//position j has a right child and right child�s index is at most end
		{
			if (jobs[leftChildIndex].getPriority() > jobs[rightChildIndex].getPriority())	//if rightChildisSmaller
			{
				smallestChildIndex = rightChildIndex;	//change smallest index
			}
		}
		if (jobs[pos].getPriority() <= jobs[smallestChildIndex].getPriority())	//if priority is <= smallest child priority its a heap
		{
			break;	//heap!
		}
		
		swap(pos, smallestChildIndex);	//swap current with smallest
		pos = smallestChildIndex;	//current = smallest
		leftChildIndex = (2 * pos) + 1;
		rightChildIndex = (2 * pos) + 2;

	}		//position 'pos' has a left child and the left child�s index is at most end
}


void Batch::swap(int j, int p) //swap the contents of the two positions.
{
	Job swappedValue = jobs[j];
	jobs[j] = jobs[p];
	jobs[p] = swappedValue;
}

void Batch::insertJob(Job job) //insert a new job
{
	jobs.push_back(job); //push job to back of heap
	this->totalLength += job.getLength(); //adds the job length to total
	this->numJobs++;
	bubbleUp(numJobs - 1); //fix the heap

}

Job Batch::minJob() //return the job with highest priority (lowest value), throws message if empty.
{
	if (isEmpty()) 
	{
		throw ("No jobs present");	//throw error if empty
	}
	else 
	{
		return (jobs[0]);		//return job at zeroth position
	}

}

Job Batch::removeMinJob() //remove the job with the highest priority (lowest value), throws message if empty.
{
	if (isEmpty()) {
		throw ("No jobs present");
	}
	Job minElement = jobs[0];//store for later
	jobs[0] = jobs[numJobs - 1];
	this->totalLength -= minElement.getLength(); //subs the job length to total
	this->numJobs--;
	this->jobs.pop_back();
	bubbleDown(0, numJobs - 1);
	return minElement;
}

void Batch::merge(Batch batch) //merge the jobs 
{
	Job minimumJob = batch.minJob();
	while(!(batch.isEmpty()))
	{
		minimumJob = batch.removeMinJob();
		insertJob(minimumJob);
	}
}

int Batch::getNumJobs() //number of jobs currently in the batch.
{
	return this->numJobs;
}

int Batch::getTotalLength() //the total length of all the jobs in the batch.
{
	return this->totalLength;
}

int Batch::getSize() //the size of the vector
{
	return this->jobs.size();
}

bool Batch::isEmpty() //is the batch of job empty?
{
	return ( ( this->numJobs == 0 ) ? true : false);
}



std::string Batch::toString() //output job information of batch
{
	std::string output = "";
	for (int i = 0; i < getSize(); i++)			//for each member of vector
	{
		output += ("[" + this->jobs[i].toString() + "]");	//sets output string
	}
	return output;
}
