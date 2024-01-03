// UMBC - CMSC 341 - Spring 2022 - Proj1
#include "elevator.h"

const char* FAIL_STATEMENT = "*****TEST FAILED: ";
const char* PASS_STATEMENT = "     TEST PASSED: ";

class Tester{
    public:
    /******************************************
    * Test function declarations! *
    ******************************************/
    bool testInsertHeadNormalCase();
    bool testInsertHeadErrorCase();
    bool testInsertTailNormalCase();
    bool testInsertTailErrorCase();
    bool testremoveFloorNormalCase();
    bool testremoveFloorErrorCase();
    bool testinsertFloorNormalCase();
    bool testAssignmentOperatorNormalCase();
    bool testAssignmentOperatorEdgeCase();
    bool testCopyConstructorNormalCase();
    bool testCopyConstructorEdgeCase();
};
int main(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i=1;i<=10;i++)
        anElev.insertAtTail(i);
    cout << "\nCarrying Alice from 6th floor to 10th floor:\n";
    cout << "\tAlice enters the elevator:\n";
    anElev.enter(6,"Alice");
    anElev.dump();
    cout << "\n\tMoving to 10th floor:\n";
    anElev.move(6,10);
    anElev.dump();
    anElev.exit(10,"Alice");
    cout << "\n\tRemoving the 2nd floor:\n";
    anElev.removeFloor(2);
    anElev.dump();


    Tester tester; //test object
   	
    {
    	//testing insertHead() normal case
	cout << endl;
	cout << "testing insertHead() normal case" << endl;

    	if(tester.testInsertHeadNormalCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    
    
    }

    {
    	//testing insertHead() error case
	cout << endl;
	cout << "testing insertHead() error case" << endl;
	if(tester.testInsertHeadErrorCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}


    } 
    
    {
    	//testing insertTail() normal case
	cout << endl;
	cout << "testing insertTail() normal case" << endl;
	if(tester.testInsertTailNormalCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    
    
    
    }

    {
    	//testing insertTail() error case
	cout << endl;
	cout << "testing insertTail() error case" << endl;
	if(tester.testInsertTailErrorCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    
    
    }

    {
    	//testing removeFloor() normal case
	cout << endl;
	cout << "testing removeFloor() normal case" << endl;
	if(tester.testremoveFloorNormalCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    }

    {
    	//testing removeFloor() error case
	cout << endl;
	cout << "testing removeFloor() error case" << endl;
	try{	
		tester.testremoveFloorErrorCase();
		cout << FAIL_STATEMENT << endl;	
	}catch(exception &e){
		cout << PASS_STATEMENT << endl;
		cout << e.what() << endl;
	}
    }

    {
    	//testing insertFloor() normal case
	cout << endl;
	cout << "testing insertFloor() normal case" << endl;
	if(tester.testinsertFloorNormalCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    }

    {
    	//testing assignment operator normal case
	cout << endl;
	cout << "testing assignment operator normal case" << endl;
	if(tester.testAssignmentOperatorNormalCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    }

    {
    	//testing assignment operator edge case
        cout << endl;
	cout << "testing assignment operator edge case" << endl;
        if(tester.testAssignmentOperatorEdgeCase() == true){
                cout << PASS_STATEMENT << endl;
        }else{
                cout << FAIL_STATEMENT << endl;
        }
    }

    {
    	//testing copy constructor normal case
	cout << endl;
	cout << "testing copy constructor normal case" << endl;
	if(tester.testCopyConstructorNormalCase() == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    }

    {
        //testing copy constructor edge case
        cout << endl;
        cout << "testing copy constructor edge case" << endl;
        if(tester.testCopyConstructorEdgeCase() == true){
                cout << PASS_STATEMENT << endl;
        }else{
                cout << FAIL_STATEMENT << endl;
        }
    }

    return 0;
}

bool Tester::testInsertHeadNormalCase(){
	//check if all floors are in order 
		
	Elevator anElev;
	for(int i = 300; i >= 1; i--){
		anElev.insertAtHead(i);
	}
	if(anElev.insertAtHead(2) == false){
		return true;
	}
	
	
	return false;	
	

}

bool Tester::testInsertHeadErrorCase(){
	Elevator anElev;
	for(int i = 300; i >= 1; i--){
		anElev.insertAtHead(i);
	}

	if(anElev.insertAtHead(5) == false){
		return true;
	}

	return false;
}

bool Tester::testInsertTailNormalCase(){
	Elevator anElev;
	for(int i = 1; i < 300; i++){
		anElev.insertAtTail(i);
	}	

	if(anElev.insertAtTail(301) == true){
		return true;
	}

	return false;
}

bool Tester::testInsertTailErrorCase(){
	Elevator anElev;
	for(int i = 1; i < 300; i++){
		anElev.insertAtTail(i);
	}

	if(anElev.insertAtTail(1) == false){
		return true;
	}

	return false;
}

bool Tester::testremoveFloorNormalCase(){
	Elevator anElev;
	for(int i = 1; i < 300; i++){
		anElev.insertAtTail(i);
	}
	
	for(int i = 1; i < 300; i++){
		if(anElev.removeFloor(i) == true){
			return true;
		}
	}
	return false;

}

bool Tester::testremoveFloorErrorCase(){
	Elevator anElev;
	for(int i = 1; i < 300; i++){
		anElev.insertAtTail(i);
	}

	if(anElev.removeFloor(301) == false){
		return true;
	}
	return false;
}

bool Tester::testinsertFloorNormalCase(){
	//try to insert a floor that already exists or one that doesnt exist
	//if floor that doesn't exist returns true and is in order then function passed
	//else return false
	Elevator anElev;
	for(int i = 1; i < 300; i++){
		anElev.insertAtTail(i);
	}

	if(anElev.insertFloor(2) == false || anElev.insertFloor(301) == true){
		//cout << "inside if statement" << endl;
		return true;
	}
	return false;

	
}

bool Tester::testAssignmentOperatorNormalCase(){
	Elevator anElev;
	bool dataMatch = false;
	for(int i = 1; i < 300; i++){
		anElev.insertAtTail(i);
	}

	Elevator newElev = anElev;
	
	Floor *curr = anElev.m_ground;
	Floor *newCurr = newElev.m_ground;
	
	while(curr != nullptr && newCurr != nullptr){
		if(curr->m_floorNum == newCurr->m_floorNum && curr->m_passenger == newCurr->m_passenger){
			dataMatch = true;
			//curr = curr->m_next;
		}
		curr = curr->m_next;
		newCurr = newCurr->m_next;
	}		

	//cout << "&anElev: " <<&anElev << endl;
	//cout << "&newElev: " << &newElev << endl;	
	if(&anElev != &newElev && dataMatch == true){
		return true;
	}
	return false; 
}

bool Tester::testAssignmentOperatorEdgeCase(){
	Elevator anElev;
        bool dataMatch = false;
        //problem with for loop when i < 1 or i < 2
	for(int i = 1; i <= 2; i++){
        	//cout << "inside for loop" << endl;
		anElev.insertAtTail(i);
        }

        Elevator newElev = anElev;

        Floor *curr = anElev.m_ground;
        Floor *newCurr = newElev.m_ground;

        while(curr != nullptr && newCurr != nullptr){
                if(curr->m_floorNum == newCurr->m_floorNum && curr->m_passenger == newCurr->m_passenger){
                        dataMatch = true;
                        curr = curr->m_next;
                }
                curr = curr->m_next;
                newCurr = newCurr->m_next;
        }

        //cout << "&anElev: " <<&anElev << endl;
        //cout << "&newElev: " << &newElev << endl;
        if(&anElev != &newElev && dataMatch == true){
                return true;
        }
        return false;
	
}

bool Tester::testCopyConstructorNormalCase(){
	Elevator anElev;
        bool dataMatch = false;
        for(int i = 1; i < 300; i++){
                anElev.insertAtTail(i);
        }

        Elevator newElev(anElev);

        Floor *curr = anElev.m_ground;
        Floor *newCurr = newElev.m_ground;

        while(curr != nullptr && newCurr != nullptr){
                if(curr->m_floorNum == newCurr->m_floorNum && curr->m_passenger == newCurr->m_passenger){
                        dataMatch = true;
                        curr = curr->m_next;
                }
                curr = curr->m_next;
                newCurr = newCurr->m_next;
        }

        //cout << "&anElev: " <<&anElev << endl;
        //cout << "&newElev: " << &newElev << endl;
        if(&anElev != &newElev && dataMatch == true){
                return true;
        }
        return false;
}

bool Tester::testCopyConstructorEdgeCase(){
	Elevator anElev;
        bool dataMatch = false;
        for(int i = 1; i <= 2; i++){
                anElev.insertAtTail(i);
        }

        Elevator newElev(anElev);

        Floor *curr = anElev.m_ground;
        Floor *newCurr = newElev.m_ground;

        while(curr != nullptr && newCurr != nullptr){
                if(curr->m_floorNum == newCurr->m_floorNum && curr->m_passenger == newCurr->m_passenger){
                        dataMatch = true;
                        curr = curr->m_next;
                }
                curr = curr->m_next;
                newCurr = newCurr->m_next;
        }

        //cout << "&anElev: " <<&anElev << endl;
        //cout << "&newElev: " << &newElev << endl;
        if(&anElev != &newElev && dataMatch == true){
                return true;
        }
        return false;

}
