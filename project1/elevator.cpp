// UMBC - CMSC 341 - Spring 2022 - Proj1
#include "elevator.h"
Elevator::Elevator(){
	m_ground = nullptr;
	m_top = nullptr;

}
Elevator::~Elevator(){
	clear();
		
}
void Elevator::clear(){
	
	while(m_ground != nullptr){
		Floor *curr = m_ground->m_next;
		delete m_ground;
		m_ground = curr;
	}
	m_top = nullptr;
	
	
	//Floor *curr = m_ground;
        //while(curr != nullptr){
        //        m_ground = curr;
        //        curr = curr->m_next;
        //        delete m_ground;
        //}
        //m_ground = nullptr;
        //m_top = nullptr;
    
}
bool Elevator::insertAtHead(int floor, string passenger){
	// 1. create new node
	// 2. make next of new node as head and prev as null
	// 3. change prev of head node to new node
	// 4. move head to point to new node

        // special case: empty list
        if(m_ground == nullptr){
        	m_ground = new Floor(floor, passenger);
        	m_top = m_ground;
        	return true;
        }

        //valid case: in order
        else if(floor < m_ground->m_floorNum){

        	//special case: one-member list
    		if(m_ground == m_top){
        		m_ground = new Floor(floor, passenger);
                	m_ground->m_next = m_top;
                	m_top->m_previous = m_ground;
                	return true;
            	}

                //regular case: shove ground aside
        	else{
                	Floor* m_oldground = m_ground;
                	m_ground = new Floor(floor, passenger);
                	m_ground->m_next = m_oldground;
                	m_oldground->m_previous = m_ground;
			return true;
            	}
    	}
        return false;
}
       	

bool Elevator::insertAtTail(int floor, string passenger){
	
	//special case: empty list
	if(m_ground == nullptr){   //if linked list is empty
		m_ground = new Floor(floor, passenger);
		m_top = m_ground;
		return true;
	}

	//valid case: in order
	else if(floor > m_top->m_floorNum){
		
		//special case: one-member list
		if(m_ground == m_top){
			m_top = new Floor(floor, passenger);
			m_ground->m_next = m_top;
			m_top->m_previous = m_ground;
			return true;
		}

		//regular case: shove top aside
		else{
			Floor *m_oldtop = m_top;
			m_top = new Floor(floor, passenger);
			m_oldtop->m_next = m_top;
			m_top->m_previous = m_oldtop;
			return true;
		}
		
	}	
	return false;
		
}
bool Elevator::removeFloor(int floor){
	if( (floor > m_top->m_floorNum) || (floor < m_ground->m_floorNum)){
		//cout << "inside out of range exception" << endl;
		throw std::out_of_range("\tfloor out of bounds.");
	}
	
	Floor *curr = m_ground;
	while(curr->m_floorNum != floor){
		curr = curr->m_next;
	}
	
	if(m_ground == m_top){
		clear();
		return true;
	}

	//if floor is last node in list
	if(curr->m_next == nullptr){
		m_top = curr->m_previous;
		delete curr;
		curr = nullptr;
		//m_top = nullptr;
		return true;
	}

	//if floor is the beginning  of list
	if(curr == m_ground){
		m_ground = curr->m_next;
		delete curr;
		curr = nullptr;
		//m_ground = nullptr;
		return true;
	}

	//if floor is in the middle of the list
	if(curr != m_ground || curr != m_top){
		curr->m_previous->m_next = curr->m_next;
		curr->m_next->m_previous = curr->m_previous;
		delete curr;
		curr = nullptr;
		return true;
	}
	
	if(curr == nullptr){
		return true;
	}
	//if floor does not exist
	return false;


}
bool Elevator::insertFloor(int floor){
	
	if(((m_top != nullptr) && (m_ground != nullptr)) && ((floor >= m_top->m_floorNum) || (floor <= m_ground->m_floorNum))){
                cout << "inside exception check" << endl;
                throw std::out_of_range("floor out of bounds.");
        }

	bool floorExists = checkFloor(floor);
	
	int diffSumGround = 0;
	int diffSumTop = 0;	
	
	//if floor already exists insert floor is successful
	if(floorExists == true){
		return false;
	}

	//if floor does not already exist
	if(floorExists == false){
		Floor *floorPtr = new Floor(floor);
		diffSumGround = floorPtr->m_floorNum - m_ground->m_floorNum;
		diffSumTop = m_top->m_floorNum - floorPtr->m_floorNum;
		
		if(diffSumTop > diffSumGround){    //if new floor is near lowest floor
			Floor *curr = m_ground;
			while(curr->m_floorNum < floorPtr->m_floorNum){
				curr = curr->m_next;
			}
			curr->m_next->m_previous = floorPtr;
			//curr->m_next = floor;
			floorPtr->m_previous = curr;
			
			return true;
		}
		
		//might delete this later
		if(diffSumTop < diffSumGround){   //if new floor is near highest floor
			Floor *curr = m_top;
			while(curr->m_floorNum > floorPtr->m_floorNum){
				curr = curr->m_previous;
			}
			//write insertion here
			curr->m_next->m_previous = floorPtr;
			floorPtr->m_previous = curr;
			
			return true;	
		}
	}
	
	return false;
}

bool Elevator::checkFloor(int floor){
	
	if(((m_top != nullptr) && (m_ground != nullptr)) && ((floor > m_top->m_floorNum) || (floor < m_ground->m_floorNum))){
                throw std::out_of_range("floor out of bounds.");
        }

	Floor *curr = m_ground;
	
	while(curr->m_floorNum != floor){
		curr = curr->m_next;
	}
	
        	
	if(curr != nullptr && curr->m_floorNum == floor){
		return true;
	}	

	return false;
}
bool Elevator::move(int origin, int destination){
	bool originExists = checkFloor(origin);
	bool destinationExists = checkFloor(destination);
	
	if(origin < m_ground->m_floorNum || destination > m_top->m_floorNum){
		throw std::out_of_range("Origin or Destination out of bounds.");
	}else{
		if(originExists == false || destinationExists == false){
                	return false;
  	      	}

	}
	//if destination is greater than origin start from bottom
	//if destination is less than origin start from top
	//start from either end of linked list then get to origin then to destination	
	if(origin == destination){
		return true;
	}
	if(originExists == true && destinationExists == true && origin < destination){
		Floor *curr = m_ground;
		if(origin == m_ground->m_floorNum){
			curr = m_ground;
			while(curr->m_floorNum != destination){
				curr = curr->m_next;
			}
			return true;	
		}else if(origin != m_ground->m_floorNum){
			curr = m_ground;
			while(curr->m_floorNum != origin){
				curr = curr->m_next;
			}
		}
		
		return false; //just doing this for now, not actually what im supposed to implement
				
	}

	if(originExists == true && destinationExists == true && origin > destination){
		Floor *curr = m_top;
		if(origin == m_top->m_floorNum){
			curr = m_top;
			while(curr->m_floorNum != destination){
				curr = curr->m_previous;
			}
			return true;
		}else if(origin != m_top->m_floorNum){
			curr = m_top;
			while(curr->m_floorNum != origin){
				curr = curr->m_previous;
			}
			//return true;
		}
	}
	return false;	


}
string Elevator::exit(int floor, string passenger){
	bool floorExists = checkFloor(floor);
	string emptyString = "";
	//Floor *newFloor = new Floor(floor, passenger);
	//traverse through list to get to floor and then set passenger to empty string at that floor
	if(floorExists == true){
		Floor *curr = m_ground;
		while(curr->m_floorNum != floor){
			curr = curr->m_next;
		}		
		curr->m_passenger = emptyString;	
		return passenger;	
	}
	//delete newFloor;
	//newFloor = nullptr;	
	return emptyString;
       
}
bool Elevator::enter(int floor, string passenger){
	bool floorExists = checkFloor(floor);
	//Floor *newFloor = new Floor(floor, passenger);
	if(floorExists == true){
		Floor *curr = m_ground;
		while(curr->m_floorNum != floor){
			curr = curr->m_next;
		}
		curr->m_passenger = passenger;
		return true;
	}
	//delete newFloor;
	//newFloor = nullptr;	
	return false;	
}
Elevator::Elevator(const Elevator & rhs){
   	m_top = nullptr;
	m_ground = nullptr;
	if(rhs.m_ground != nullptr){
		Floor *curr = rhs.m_ground;

		while(curr != nullptr){
			insertAtTail(curr->m_floorNum, curr->m_passenger);
			curr = curr->m_next;
		}
	}	
}
const Elevator & Elevator::operator=(const Elevator & rhs){
        Floor *curr;
	if(rhs.m_ground != nullptr){
		curr = rhs.m_ground;
	}

	if(this != &rhs){
		clear();
		cout << "inside first if" << endl;
		if(rhs.m_ground != nullptr){
			while(curr != nullptr){
				insertAtTail(curr->m_floorNum, curr->m_passenger);
				curr = curr->m_next;
				cout << "print" << endl;
			}
		}

	}else{
		cout << "No copy needed" << endl;
	}

	return *this;
       	
}
void Elevator::dump(){
    if (m_top != nullptr){
        Floor *temp = m_top;
        cout << "Top Floor " ;
        while(temp->m_previous != nullptr){
            cout << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
            temp = temp->m_previous;
        }
        cout << "Ground Floor " << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
    }
}
