
#include "section.h"

class Tester{
    public:
    // the following is implemented as an example of measurement
    void measureInsertionTime(int numTrials, int inputSize);
    // the following is implemented as a test case example
    bool testStudentAveErrorCase();

    /******************************************
    * Test function declarations go here! *
    ******************************************/

};
int main(){
    Tester tester;// test object
g++ mytest.cpp section.cpp section.h    {
        // the following is a sample usage of the Section class
        // create an object with 5 grading items and 8 students
        cout << "\nSample usage of the Section class:\n\n";
        Section aSection(5,8);
        aSection.insert();
        aSection.dump();
    }
    {
        // measuring the running time of insertion
        cout << "\nMeasuring the performance of insertion function:\n\n";
        // measuring the insertion of 100x100 grades, and 200x200 grades
        // the 100x100 grades is determined by 100 items times 100 students
        tester.measureInsertionTime(2,100);
    }
    {
        // testing error case for calculation of student average
        cout << "\nTesting studentAverage(...), error case:\n\n";
        if (tester.testStudentAveErrorCase() == true)
            cout << "\tError case (student index does not exist) of studentAverage() passed!\n";
        else
            cout << "\tError case (student index does not exist) of studentAverage() failed!\n";
    }
    cout << endl;
    return 0;
}

void Tester::measureInsertionTime(int numTrials, int inputSize)
{
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++)
    {
        Section testObject(inputSize,inputSize);
        start = clock();
        testObject.insert();//the algorithm to be analyzed for efficiency
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "\tInserting " << inputSize * inputSize << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        inputSize = inputSize * a;//increase the input size by the scaling factor
    }
}

bool Tester::testStudentAveErrorCase(){
    bool result = true;
    // create an object with 1 student and 10 grading items
    Section testObject(10,1);
    testObject.insert();
    double average = testObject.studentAverage(1);// out of range index
    if (average == 0.0)
        result = true;
    else
        result = false;
    return result;
}
