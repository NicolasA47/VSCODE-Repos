#include<iostream>
#include<cstring>//to use string compare
#include<string>
#include "Batch.h"
#include "Job.h"
/*
 TestBatch.cpp

 It runs a sequence of tests.  If you include it will tests on your code.
 Should you need to run a given test (and all those after it), you may pass that number as a command-line argument
 for this program.  It is recommended looking at what each test does before asking about any one test.

 By Dr. Daniel Page
 Fall 2021
*/

/*
  Test 1 - constructor test
  Just checking that the constructor is set up properly
*/
bool testOne() {

    bool result = false;//assume the tests fails...
    try {
        Batch* batch = new Batch();//create a new batch we will use for merging
        if (batch->getNumJobs() == 0 && batch->getTotalLength() == 0 && batch->getSize() == 0) {
            result = true;//passed
        }
        else {
            result = false;//failed
        }
        delete batch;//we don't need this batch, it's empty, so delete it.

    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 1: An exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}


/*
  Test 2 - inserts a sequence of jobs with priorities 0, 1, 2, 3, 4, 5, 6, ..., 10000
  In this situation, no elements will be swapped!
*/
bool testTwo() {

    bool result = false;//assume the tests fails...
    try {
        Batch* batch = new Batch();//create a new batch
        int count = 0;
        int maxNumJobs = 10000;

        while (count < maxNumJobs) {
            Job* job = new Job("id:" + std::to_string(count), count, count);//job has priority count
            batch->insertJob(*job);
            count++;
        }
        std::string heapString = batch->toString();//will check the heap to see if it matches what should be expected!
        // building the expected output...
        std::string testResult = "";
        for (int i = 0; i < maxNumJobs; i++) {
            std::string numVal = std::to_string(i);
            testResult += "[id:" + std::to_string(i) + "," + numVal + "]";
        }
        //check if the output matches the expected result.
        if (heapString.compare(testResult) == 0) {
            result = true;//TEST PASSES!
        }
        else {
            //a mismatch occurred!
            std::cout << "---TEST 2: toString does not match expected output..." << std::endl;
            result = false;
        }
        delete batch;

    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 2: An exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}

/*
  Test 3 - inserts some elements, all with the same key/priority, then removes them, but will throw the exception by removing one extra.
*/
bool testThree() {

    bool result = false;//assume the tests fails...
    try {
        Batch* batch = new Batch();//create a new batch
        int count = 0;
        int maxNumJobs = 100;

        while (count < maxNumJobs) {
            Job* job = new Job("id:" + std::to_string(count), count, count);//job has priority count
            batch->insertJob(*job);
            count++;
        }
        //when we remove the next smallest job, it should give us 0,1,2,3,4,...
        count = 0;
        while (count < maxNumJobs) {
            Job nextJob = batch->removeMinJob();
            if (nextJob.getPriority() != count) {
                std::cout << "---TEST 3: The next job removed is not correct..." << std::endl;
                return false;
            }
            count++;
        }
        //now let us cause an exception
        batch->removeMinJob();
        std::cout << "---TEST 3: There is an exception that should be thrown, see specifications" << std::endl;
        return false;

    }
    catch (char const* e) {//this will occur on the last removeMinJob
        if (strcmp(e, "No jobs are present") == 0 || strcmp(e, "No jobs present") == 0 || strcmp(e, "No Jobs present") == 0 || strcmp(e, "No jobs are present") == 0 || std::string(e) == "No jobs are present") {
            return true;
        }
        else {
            std::cout << "---TEST 3:  Error message thrown does not match what was stated in specifications" << std::endl;
            return false;
        }
    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 3: An unexcepted exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}

/*
  Test 4 - Checking to make sure that the size of the list matches the number of jobs.
  It performs a series of insertions and removals...
*/
bool testFour() {

    bool result = false;//assume the tests fails...
    try {
        Batch* batch = new Batch();//create a new batch
        int count = 0;
        int maxNumJobs = 1000;
        int numFails = 0;
        //we insert 1000 jobs, but we remove the min each time we put one in, except for the last one (which has priority 1)
        while (count < maxNumJobs) {
            Job* job = new Job("id:" + std::to_string(maxNumJobs - count), maxNumJobs - count, count);//job has priority count
            batch->insertJob(*job);

            if (count < maxNumJobs - 1) {//Do not remove the last job
                Job removedJob = batch->removeMinJob();
                if (batch->getSize() != batch->getNumJobs()) {
                    if (numFails <= 0) {
                        std::cout << "---TEST 4: Oops, when job [" << removedJob.toString() << "] was removed, the size of the vector was " << batch->getSize() << ", but the number of jobs is " << batch->getNumJobs() << "." << std::endl;
                    }
                    else if (numFails == 1) {
                        std::cout << "---TEST 4: More than one mismatch of the vector's size and the number jobs has occurred." << std::endl;
                    }
                    numFails++;
                    result = false;//mismatching sizes
                }
                delete job;//we don't need this any more!
            }
            count++;
        }
        std::string heapString = batch->toString();//will check the heap to see if it matches what should be expected!
        // building the expected output...
        std::string testResult = "[id:1,1]";//there should be only one job left!
        //check if the output matches the expected result.
        if (heapString.compare(testResult) == 0) {
            result = true;//TEST PASSES!
        }
        else {
            //a mismatch occurred!
            std::cout << "---TEST 4: toString does not match expected output..." << std::endl;
            result = false;
        }
        delete batch;

    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 4: An exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}

/*
  Test 5 - Some insertions happen, and some removals happen, the isEmpty method is checked.
  Checking isEmpty
*/
bool testFive() {

    bool result = true;//assume the test passes...
    try {
        Batch* batch = new Batch();//create a new batch
        int count = 0;
        int maxNumJobs = 1000;
        int numFails = 0;
        //we insert 1000 jobs, but we remove the min each time we put one in, except for the last one (which has priority 1)
        while (count < maxNumJobs) {
            Job* job = new Job("id:" + std::to_string(count), count, count);//job has priority count
            batch->insertJob(*job);
            //the batch should not be empty.
            if (batch->isEmpty() && numFails <= 1) {
                std::cout << "---TEST 5: The batch should not be empty at this time." << std::endl;
                result = false;
                numFails++;
            }
            Job removedJob = batch->removeMinJob();
            //the batch is empty
            if (!batch->isEmpty() && numFails <= 1) {
                std::cout << "---TEST 5: The batch should be empty at this time." << std::endl;
                result = false;
                numFails++;
            }
            delete job;
            count++;
        }
        delete batch;

    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 5: An exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}

/*
  Test 6 - We check the min job of the batch, and we cause it to throw the exception when the batch is empty.
*/
bool testSix() {

    bool result = false;//assume the tests fails...
    try {
        Batch* batch = new Batch();//create a new batch
        int count = 0;
        int maxNumJobs = 10000;


        while (count < maxNumJobs) {
            Job* job = new Job("id:" + std::to_string(maxNumJobs - count), maxNumJobs - count, count);//job has priority count
            batch->insertJob(*job);
            count++;
        }
        //when we remove the next smallest job, it should give us 1,2,3,4,5,...
        count = 0;
        while (count < maxNumJobs) {
            Job nextJob = batch->minJob();
            if (nextJob.getPriority() != count + 1) {
                std::cout << "---TEST 6: The smallest job is not correct..." << std::endl;
                return false;
            }
            //now remove that job
            batch->removeMinJob();
            count++;
        }
        //now let us cause an exception
        batch->minJob();
        std::cout << "---TEST 6: There is an exception that should be thrown, see specifications" << std::endl;
        return false;

    }
    catch (char const* e) {//this will occur on the last minJob call
        if (strcmp(e, "No jobs present") == 0 || strcmp(e, "No Jobs present") == 0 || std::string(e) == "No jobs present" || std::string(e) == "No jobs are present" || strcmp(e, "No jobs are present") == 0) {
            return true;
        }
        else {
            std::cout << "---TEST 6:  Error message thrown does not match what was stated in specifications" << std::endl;
            return false;
        }
    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 6: An unexcepted exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}

/*
  Test 7 - Some insertions happen, and some removals happen, and the number of jobs is checked
*/
bool testSeven() {

    bool result = false;//assume the test fails...
    try {
        Batch* batch = new Batch();//create a new batch
        int count = 0;
        int maxNumJobs = 10000;
        int expectedLength = 0;
        //we insert 1000 jobs, and check the total length each time
        while (count < maxNumJobs) {
            Job* job = new Job("id:" + std::to_string(maxNumJobs - 8 * count), maxNumJobs - 8 * count, maxNumJobs);//job has priority count
            batch->insertJob(*job);
            expectedLength += 1;
            //check if the total length matches what should be expected!
            if (batch->getNumJobs() != expectedLength) {
                std::cout << "---TEST 7: The total number of jobs in the batch does not match upon insertion." << std::endl;
                return false;
            }
            count++;
        }
        //next let us remove each job from the batch and check the number of jobs
        count = 0;
        while (count < maxNumJobs) {
            //just to make sure min doesn't remove anything
            batch->minJob();
            if (batch->getNumJobs() != expectedLength) {
                std::cout << "---TEST 7: minJob is removing a job, when it should not." << std::endl;
                return false;
            }
            //now decrease the number of jobs by 1
            batch->removeMinJob();
            expectedLength -= 1;//one less job
            if (batch->getNumJobs() != expectedLength) {
                std::cout << "---TEST 7: The total number of jobs in the batch does not match upon removeMin." << std::endl;
                return false;
            }
            count++;
        }
        if (batch->getNumJobs() == 0) {
            result = true;//no jobs should be left
        }
        else {
            std::cout << "---TEST 7: The total number of jobs in the batch is wrong." << std::endl;
            result = false;
        }
        delete batch;

    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 7: An exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}

/*
  Test 8 - Some insertions happen, and some removals happen, and the total length of the batch is checked sometimes.
  Checking getTotalLength
*/
bool testEight() {

    bool result = false;//assume the test fails...
    try {
        Batch* batch = new Batch();//create a new batch
        int count = 0;
        int maxNumJobs = 1000;
        int expectedLength = 0;
        //we insert 1000 jobs, and check the total length each time
        while (count < maxNumJobs) {
            Job* job = new Job("id:" + std::to_string(maxNumJobs - count), maxNumJobs - count, maxNumJobs - count);//job has priority count
            batch->insertJob(*job);
            expectedLength += maxNumJobs - count;
            //check if the total length matches what should be expected!
            if (batch->getTotalLength() != expectedLength) {
                std::cout << "---TEST 8: The total length of the batch does not match what is expressed on insertion." << std::endl;
                return false;
            }
            count++;
        }
        //next let us remove each job from the batch and check the total length
        count = 0;
        while (count < maxNumJobs) {
            batch->removeMinJob();
            count++;
        }
        if (batch->getTotalLength() == 0) {
            result = true;
        }
        else {
            std::cout << "---TEST 8: The total length of the batch does not match what is expressed on removeMin." << std::endl;
            result = false;
        }
        delete batch;

    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 8: An exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}

/*
  Test 9 - merge test
  Some merges occur, we keep an eye on how many jobs there are.
*/
bool testNine() {

    bool result = false;//assume the tests fails...
    try {
        Batch* mergeBatch = new Batch();//create a new batch we will use for merging
        int count = 0;
        int maxNumJobs = 3;
        int batchCount = 10000;
        for (int i = 0; i < batchCount; i++) {
            Batch* batch = new Batch();//we will merge this batch...
            count = 0;
            while (count < maxNumJobs) {
                Job* job = new Job("id:" + std::to_string(count), count, count);//job has priority count
                batch->insertJob(*job);
                count++;
            }
            mergeBatch->merge(*batch);//merge batch with mergeBatch
            delete batch;//we don't need this batch, it's empty, so delete it.
        }
        std::string heapString = mergeBatch->toString();//will check the heap to see if it matches what should be expected!
        // expected output
        //std::string testResult = "[id:0,0][id:0,0][id:0,0][id:0,0][id:0,0][id:0,0][id:0,0][id:1,1][id:0,0][id:1,1][id:0,0][id:0,0][id:1,1][id:1,1][id:2,2][id:1,1][id:1,1][id:2,2][id:2,2][id:1,1][id:2,2][id:1,1][id:1,1][id:2,2][id:2,2][id:2,2][id:2,2][id:2,2][id:1,1][id:2,2]";

        //check if the number of jobs in mergeBatch are what is expected
        if (mergeBatch->getNumJobs() == 30) {
            result = true;//TEST PASSES!
        }
        else {
            //a mismatch occurred!
            std::cout << "---TEST 9: toString does not have the number of jobs that would be expected..." << std::endl;
            result = false;
        }
        delete mergeBatch;

    }
    catch (std::exception& e) {
        //something unexpected happened, the test fails!
        std::cerr << "---TEST 9: An exception occurred..." << e.what() << std::endl;
        result = false;
    }
    return result;
}

/*
  Printing results of tests by number
  Inputs:  An integer for said said, and the result of that test as a boolean value.
  Output: Prints to the console the result of that test (the test is computed prior to calling this).
*/
void testResult(const int numTest, const bool result) {
    if (result) {
        std::cout << "TEST " << numTest << " PASSES" << std::endl;
    }
    else {
        std::cout << "TEST " << numTest << " FAILS" << std::endl;
    }
}


/*
    Main

    Runs tests for batch
    Inputs:  Takes one integer, it will run tests from that number and on (1 to 9)
*/
int main(int argc, char* argv[]) {

    int testNum = 1;//it is assumed all tests will be run, if a command line argument is passed (a number) this will change.
    if (argc >= 2) {
        testNum = std::atoi(argv[1]);//we begin at this test number...
    }

    std::cout << "TESTING BEGINS AT TEST " << testNum << std::endl;
    std::cout << "--------------" << std::endl;
    //CONSTRUCTOR TEST
    if (testNum <= 1) {
        testResult(1, testOne());
    }
    //INSERT TEST
    if (testNum <= 2) {
        testResult(2, testTwo());
    }
    //REMOVE TEST
    if (testNum <= 3) {
        testResult(3, testThree());
    }
    //VECTOR SIZE TEST -- Checking that the internal vector being used always stays the same size as the number of jobs!
    if (testNum <= 4) {
        testResult(4, testFour());
    }
    //ISEMPTY TEST 
    if (testNum <= 5) {
        testResult(5, testFive());
    }
    //MINJOB TEST
    if (testNum <= 6) {
        testResult(6, testSix());
    }
    //GETNUMJOBS TEST 
    if (testNum <= 7) {
        testResult(7, testSeven());
    }
    //GETTOTALLENGTH TEST
    if (testNum <= 8) {
        testResult(8, testEight());
    }
    //MERGE TEST
    if (testNum <= 9) {
        testResult(9, testNine());
    }
    std::cout << "--------------" << std::endl;
    std::cout << "TESTS HAVE ENDED" << std::endl;
    return 0;
}