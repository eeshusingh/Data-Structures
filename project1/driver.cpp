// UMBC - CMSC 341 - Spring 2022 - Proj1
#include "elevator.h"
class Tester{
    public:
    /******************************************
    * Test function declarations go here! *
    ******************************************/
};
int main(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    
    //for (int i=1;i<=10;i++)
//	    anElev.insertAtTail(i);
    try{
    	anElev.insertFloor(4);
    }catch(std::out_of_range const& e){
    	cout << e.what() << endl;
    }

    anElev.dump();
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
    return 0;
}
