

#include "section.h"

const char* FAIL_STATEMENT = "*****TEST FAILED: ";
const char* PASS_STATEMENT = "     TEST PASSED: ";

class Tester{
    public:
    // the following is implemented as an example of measurement
    void measureInsertionTime(int numTrials, int inputSize);
    // the following is implemented as a test case example
    bool testStudentAveErrorCase();


    bool testCreateSectionNormalCase();
    bool testCreateSectionEdgeCase();
    bool testCreateSectionErrorCase(); 
    bool testStudentAveNormalCase();
    bool testCopyConstructorEdgeCase();
    bool testCopyConstructorNormalCase();
    bool testAssignmentOperatorNormalCase();
    bool testAssignmentOperatorEdgeCase();
    bool testQuizAveNormalCase();
    bool testQuizAveErrorCase();
    bool testClassAveNormalCase();
    bool testClassAveErrorCase();    
};


int main(){
    Tester tester;// test object
    {
        // the following is a sample usage of the Section class
        // create an object with 1 grading items and 1 students
        cout << "\nSample usage of the Section class Edge Case:\n\n";
    	if(tester.testCreateSectionEdgeCase() == true)
		cout << PASS_STATEMENT << endl;
	else
		cout << FAIL_STATEMENT << endl;
	

    }
    
    {
        // testing normal case for creating section object
        cout << "\ntesting Section constructor normal case:\n\n";
        if(tester.testCreateSectionNormalCase() == true)
                cout << PASS_STATEMENT << endl;
        else
                cout << FAIL_STATEMENT << endl;

    }

    {
    	// testing error case for creating section object
	cout << "\ntesting Section constructor error case:\n\n";
	if(tester.testCreateSectionErrorCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    
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
        if (tester.testStudentAveErrorCase() == true){
            cout << "\tError case (student index does not exist) of studentAverage() passed!\n";
	}
	else{
            cout << "\tError case (student index does not exist) of studentAverage() failed!\n";
	}
    }
    
    {
    	// testing normal case for calculation of student average
	cout << "\nTesting studentAverage(...), normal case:\n\n";
        if (tester.testStudentAveNormalCase() == false){
            cout << "\tNormal case of studentAverage() passed!\n";
        }
        else{
            cout << "\tNormal case of studentAverage() failed!\n";
        }	
    }

    {
    	// testing copy constructor normal case
	cout << "\nTesting copy constructor, normal case:\n\n";
	if(tester.testCopyConstructorNormalCase() == true){
		cout << "\tNormal case for copy constructor passed!\n";
	}else{
		cout << "\tNormal case for copy constructor failed\n";
	}	
    }

    {
    	// testing copy constructor edge case
	cout << "\nTesting copy constructor, edge case:\n\n";
	if(tester.testCopyConstructorEdgeCase() == false){
		cout << "\tEdge case for copy constructor failed!\n"; 
	}else{
		cout << "\tEdge case for copy constructor passed!\n";
	}
    }

    {
    	// testing assignment operator normal case
	cout << "\nTesting assignment operator, normal case:\n\n";
	if(tester.testAssignmentOperatorNormalCase() == true){
		cout << "\tNormal case for assignment operator passed!\n";
	}else{
		cout << "\tNormal case for assignment operator failed!\n";
	}
    
    }

    {
        // testing assignment operator edge case
        cout << "\nTesting assignment operator, edge case:\n\n";
        if(tester.testAssignmentOperatorEdgeCase() == true){
                cout << "\tEdge case for assignment operator passed!\n";
        }else{
                cout << "\tEdge case for assignment operator failed!\n";
        }
    }

    {
    	cout << "\ntesting quizAverage() normal case:\n\n";
	if(tester.testQuizAveNormalCase() == true){
		cout << "\tNormal case for quizAverage passed!\n";
	}else{
		cout << "\tNormal case for quizAverage failed!\n";
	}
    
    
    }

    {
    	cout << "\ntesting quizAverage() error case:\n\n";
    	if(tester.testQuizAveErrorCase() == true){
                cout << "\tError case for quizAverage passed!\n";
        }else{
                cout << "\tError case for quizAverage failed!\n";
        }
    
    }

    {
	cout << "\ntesting classAverage() normal case:\n\n";    
    	if(tester.testClassAveNormalCase() == true){
		cout << "\tNormal case for classAverage passed!\n";
	}else{
		cout << "\tNormal case for classAverage failed!\n";
	}
    
    }
    {
    	cout << "\ntesting classAverage() error case:\n\n";
	if(tester.testClassAveErrorCase() == true){
		cout << "\tError case for classAverage passed\n";
	}else{
		cout << "\tError case for classAverage failed\n";
	}
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
    cout << "average: " << average << endl;
    if (average == 0.0)
        result = true;
    else
        result = false;
    return result;
}

bool Tester::testStudentAveNormalCase(){
	bool result = true;
	double avg = 0.0;
	// create an object with 2 students and 3 grading items
	Section testObj(3,2);
	testObj.insert();
	avg = testObj.studentAverage(1);	
	
	if(avg >= 0.0){
		result = false;;
	}
	else{
		result = true;
	}

	cout << "first students average: " << avg << endl;	
	return result; //for now	
}

bool Tester::testCreateSectionNormalCase(){
	//How do I access m_numStudents & m)numGradingItems
	Section testObject(10, 10);
	testObject.insert();
	if(testObject.m_numStudents == 10 && testObject.m_numGradingItems == 10){
		return true;
	}

	return false;
	
} 

bool Tester::testCreateSectionEdgeCase(){
	Section testObject(1, 1);
	testObject.insert();
        if(testObject.m_numStudents == 1 && testObject.m_numGradingItems == 1){
                return true;
        }

        return false;
}

bool Tester::testCreateSectionErrorCase(){
	Section testObject(-1, -10);
	testObject.insert();
	if(testObject.m_numStudents == 0 && testObject.m_numGradingItems == 0){
		return true;
	}

	return false;
}

bool Tester::testCopyConstructorEdgeCase(){
	//create normal object
	
	Section testObject(0, 0);
	//testObject.insert();
	//create a copy of previous object using copy constructor
	Section testObject2(testObject);
	if(&testObject2 != &testObject && testObject.m_numStudents == testObject2.m_numStudents && testObject.m_numGradingItems == testObject2.m_numGradingItems){
		return true;
	}


	return false;
}

bool Tester::testCopyConstructorNormalCase(){
	Section testObject(10, 10);
	bool result = false;
	bool result2 = false;
	Section testObject2(testObject);
        
	if(&testObject2 != &testObject && testObject.m_numStudents == testObject2.m_numStudents && testObject.m_numGradingItems == testObject2.m_numGradingItems){
                result = true;
        }
	
	for(int i = 0; i < testObject.m_numStudents; i++){
		for(int j = 0; j < testObject.m_numGradingItems; j++){
			if(testObject.m_grades[i][j] == testObject2.m_grades[i][j]){
				result2 = true;	
			}
		}
	}

	if(result == true && result2 == true){
		return true;
	}

	return false; 
}

bool Tester::testAssignmentOperatorNormalCase(){
	Section testObject(10, 10);
	testObject.insert();
        bool result = false;
        bool result2 = false;
        Section testObject2 = testObject;
        if(&testObject2 != &testObject && testObject.m_numStudents == testObject2.m_numStudents && testObject.m_numGradingItems == testObject2.m_numGradingItems){
                result = true;
        }

        for(int i = 0; i < testObject.m_numStudents; i++){
                for(int j = 0; j < testObject.m_numGradingItems; j++){
                        if(testObject.m_grades[i][j] == testObject2.m_grades[i][j]){
                                result2 = true;
                        }
                }
        }

        if(result == true && result2 == true){
                return true;
        }

        return false;
}

bool Tester::testAssignmentOperatorEdgeCase(){
	Section testObject(0, 0);
        bool result = false;
        bool result2 = false;
        Section testObject2 = testObject;
        if(&testObject2 != &testObject && testObject.m_numStudents == testObject2.m_numStudents && testObject.m_numGradingItems == testObject2.m_numGradingItems){
                result = true;
        }

        for(int i = 0; i < testObject.m_numStudents; i++){
                for(int j = 0; j < testObject.m_numGradingItems; j++){
                        if(testObject.m_grades[i][j] == testObject2.m_grades[i][j]){
                                result2 = true;
                        }
                }
        }

        if(result == true){
                return true;
        }

        return false;
}

bool Tester::testQuizAveNormalCase(){
	bool result = false;
        double avg = 0.0;
        // create an object with 2 students and 3 grading items
        Section testObj(3, 2);
        testObj.insert();
        avg = testObj.quizAverage(1);

        if(avg >= 0.0){
                result = true;
        }
        else{
                result = false;
        }

        cout << "second students quiz average: " << avg << endl << endl;;
        return result; //for now
}

bool Tester::testQuizAveErrorCase(){
	bool result = false;
        double avg = 0.0;
        // create an object with 2 students and 3 grading items
        Section testObj(3, 2);
        testObj.insert();
        avg = testObj.quizAverage(5);

        if(avg == 0.0){
                result = true;
        }
        else{
                result = false;
        }

        //cout << "second students quiz average: " << avg << endl;
        return result; 	
}

bool Tester::testClassAveNormalCase(){
	bool result = false;
	double avg = 0.0;
	Section testObj(5, 5);
	testObj.insert();
	
	avg = testObj.classAverage();

	if(avg == 0.0){
		result = false;
	}else{
		result = true;
	}

	return result;
}

bool Tester::testClassAveErrorCase(){
	bool result = false;
	double avg = 0.0;
	Section testObj(-1, -1);
	testObj.insert();
	avg = testObj.classAverage();

	if(avg == 0.0){
		result = true;
	}else{
		result = false;
	} 

	return result;

}
