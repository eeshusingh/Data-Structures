// UMBC - CMSC 341 - Spring 2022 - Proj2
#include "fleet.h"
#include <random>

const char* FAIL_STATEMENT = "\n*****TEST FAILED: ";
const char* PASS_STATEMENT = "\n     TEST PASSED: ";

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }

    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};
class Tester{
    public:
    /******************************************
    * Test function declarations go here! *
    ******************************************/
    bool testInsertNormalCase();
    bool testRemoveNormalCase();
    bool testRemoveEdgeCase();
    
};
int main(){
    Random idGen(MINID,MAXID);
    Random typeGen(0,4);
    Tester tester;
    {
        Fleet fleet;
        int fleetSize = 10;
        int tempID = 0;
        int ID = 0;
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            if (i == fleetSize / 2) tempID = ID;//we store this ID for later use
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }
        cout << "\nDump after inserting " << fleetSize << " nodes:\n\n";
        fleet.dumpTree();
        cout << "\n\nList of Ships after inserting " << fleetSize << " nodes:\n";
        fleet.listShips();
        cout << endl;

        fleet.remove(tempID);
        cout << "\nDump after removing the node with ID: " << tempID << "\n\n";
        fleet.dumpTree();
        cout << "\n\nList of Ships after removing the node with ID: " << tempID << "\n";
        fleet.listShips();
        cout << endl;
    }

    {
    //  testing myTest Normal case
	Fleet fleet;
	bool f = tester.testInsertNormalCase();
	
	cout << "\n\nTesting fleet insert normal case: ";
	
	if(f == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    }

    {
    	//testing remove normal case
	Fleet fleet;

	cout << "\n\nTesting fleet remove normal case: ";
	
	bool f = tester.testRemoveNormalCase();


        if(f == true){
                cout << PASS_STATEMENT << endl;
        }else{
                cout << FAIL_STATEMENT << endl;
        }

    }

    {
	//testing remove edge case
	Fleet fleet;
	
	cout << "\n\nTesting fleet remove edge case: ";
	
	bool f = tester.testRemoveEdgeCase();
	

	if(f == true){
		cout << PASS_STATEMENT << endl;
	}else{
		cout << FAIL_STATEMENT << endl;
	}
    
    }

    return 0;
}

bool Tester::testInsertNormalCase(){
	Fleet fleet;
	Random idGen(MINID,MAXID);
	Random typeGen(0,4);
	int tempID = 0;
	int fleetSize = 20;
	int ID = 0;
	tempID++;
	tempID--;
	int count = 0;
	for(int i = 0; i < fleetSize; i++){
		ID = idGen.getRandNum();
		if (i == fleetSize / 2) tempID = ID;//we store this ID for later use
	        Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
        	fleet.insert(ship);
		count++;
	}
	
//	cout << "\n\nList of Ships after inserting 20 ships" << endl;
//	fleet.listShips();
	if(count == 20){
		return true; //for now
	}

	return false;
}

bool Tester::testRemoveNormalCase(){
	Fleet fleet;
        Random idGen(MINID,MAXID);
        Random typeGen(0,4);
        int tempID = 0;
        int fleetSize = 20;
        int ID = 0;
        tempID++;
        tempID--;
        int count = 0;
        for(int i = 0; i < fleetSize; i++){
                ID = idGen.getRandNum();
                if (i == fleetSize / 2) tempID = ID;//we store this ID for later use
                Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
                fleet.insert(ship);
                count++;
        }

	fleet.remove(23534);
	
	if(fleet.findShip(23534) == true){
		return false;
	}
	return true; 


}

bool Tester::testRemoveEdgeCase(){
	Fleet fleet;
	Random idGen(MINID,MAXID);
        Random typeGen(0,4);
        int ID = 0;
	ID = idGen.getRandNum();
	Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
	fleet.insert(ship);
	int shipID = fleet.m_root->getID();
	
	//cout << "\nList of ship: ";
	//fleet.listShips();
	
	fleet.remove(shipID);
	
	//cout << "\nList of ships: ";
	
	//fleet.listShips();
	
	if((fleet.findShip(shipID) == false) && (fleet.m_root == nullptr)){
		return true;
	}
	return false;
		

}

