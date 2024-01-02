// UMBC - CMSC 341 - Spring 2022 - Proj2
#include "fleet.h"
Fleet::Fleet(){
	m_root = nullptr;
}
Fleet::~Fleet(){
	clear(); 
}
void Fleet::insert(const Ship& ship){
	m_root = insertHelper(ship, m_root);
}

Ship* Fleet::insertHelper(const Ship& aShip, Ship*& tracker){
	

	//if tree is empty
	if(tracker == nullptr){
		Ship *newShip = new Ship(aShip.m_id, aShip.m_type, aShip.m_state);
		tracker = newShip;
		return tracker;
	}
	//if inserting ship id is less then current node id
	else if(aShip.getID() < tracker->getID()){
		tracker->setLeft(insertHelper(aShip, tracker->m_left));	
		updateHeight(tracker);
	//	tracker = rebalance(tracker);  
		return tracker;	
	}
	//if inserting ship id is greater than current node id
	else if(aShip.getID() > tracker->getID()){
		tracker->setRight(insertHelper(aShip, tracker->m_right));

		updateHeight(tracker);
	//	tracker = rebalance(tracker); 
		return tracker;
	}
	updateHeight(tracker);
	//tracker = rebalance(tracker);
	return tracker;
}


void Fleet::clear(){
	m_root = clearHelper(m_root); 
}

Ship* Fleet::clearHelper(Ship* aShip){
	if(aShip == nullptr){
		return nullptr;	
	}
	
	clearHelper(aShip->m_right);
	clearHelper(aShip->m_left);
	
	delete aShip;
	aShip = nullptr;
	
	return aShip;

}

void Fleet::remove(int id){
	m_root = removeHelper(m_root, id);
}

Ship* Fleet::removeHelper(Ship* aShip, int id){
	//if tree empty
	if(aShip == nullptr){
		return aShip;
	}else if(id < aShip->getID()){
		aShip->setLeft(removeHelper(aShip->getLeft(), id));
	}else if(id > aShip->getID()){
		aShip->setRight(removeHelper(aShip->getRight(), id));
	}else{
		//no child
		if(aShip->getLeft() == nullptr && aShip->getRight() == nullptr){
			delete aShip;
			aShip = nullptr;
		}
		//one child
		else if(aShip->getLeft() == nullptr){
			Ship *temp = aShip;
			aShip = aShip->getRight();
			delete temp;
		}
		else if(aShip->getRight() == nullptr){
			Ship *temp = aShip;
			aShip = aShip->getLeft();
			delete temp;
		}
		//two children
		else{
			Ship *temp = findMin(aShip->getRight());
			aShip->setID(temp->getID());
			aShip->setType(temp->getType());
			aShip->setHeight(temp->getHeight());
			aShip->setState(temp->getState());
			//delete found node
			aShip->setRight(removeHelper(aShip->getRight(), aShip->getID()));
		}
	}
	//call rebalance on aShip
	//aShip = rebalance(aShip); //probably calling rebalance on nullptr
	return aShip;
}

Ship* Fleet::findMin(Ship* aShip){
	//helper function that find the node with the lowest id value
	return findMin(aShip->getLeft());	
}

void Fleet::updateHeight(Ship* aShip){
	if(aShip == nullptr){
		return;
	}
	

	if(aShip->m_left == nullptr && aShip->m_right == nullptr){
		aShip->m_height = 0; 
	}

	
	int leftHeight1 = 0;
	int rightHeight1 = 0;
	
	if(aShip->m_left == nullptr){
		leftHeight1 = -1;
	}else{
		leftHeight1 = aShip->m_left->m_height;
	}
	
	
	if(aShip->m_right == nullptr){
		rightHeight1 = -1;
	}else{
		rightHeight1 = aShip->m_right->m_height;
	}
		

	if(leftHeight1 > rightHeight1){
		aShip->m_height = 1 + leftHeight1;
	}else{
		aShip->m_height = 1 + rightHeight1;
	}

}


int Fleet::checkImbalance(Ship* aShip){
	int leftHeight = -1;
	int rightHeight = -1;
	
	if(aShip == nullptr){
		return -1; //was originally 0
	}	
	
	if(aShip->getLeft() != nullptr){
	
		leftHeight = aShip->getLeft()->getHeight();
	}
	if(aShip->getRight() != nullptr){
		rightHeight = aShip->getRight()->getHeight();
	}
	
	
	//height of nodes that are nullptr are -1
	

	int balanceFactor = leftHeight - rightHeight;
	
	return balanceFactor;

}
Ship* Fleet::rebalance(Ship* aShip){
	int needBalance = 0;
	needBalance = checkImbalance(aShip);
	if(needBalance > 1){
		if(checkImbalance(aShip->getLeft()) > 0){
			//double left rotation
			
			return leftLeftRotation(aShip);
		}
		else{
			//left right rotation
			aShip->m_left = leftLeftRotation(aShip->m_left);	
			return rightRightRotation(aShip);
		}
	}else if(needBalance < -1){
		if(checkImbalance(aShip->getRight()) > 0){
			//right left rotation

			aShip->m_right = rightRightRotation(aShip->m_right);
			return leftLeftRotation(aShip);
		}
		else{
			//double right rotation
			return rightRightRotation(aShip);
		}
	}

	return aShip;	
}
/*
Ship* Fleet::rebalance(Ship* aShip){
	//rebalance causing seg fault
	int needBalance = 0;
        needBalance = checkImbalance(aShip);
	if(needBalance < -1){
		if(checkImbalance(aShip->m_right) <= 0){
			return leftLeftRotation(aShip); //left rotation
		}
		else if(checkImbalance(aShip->m_right) >= 0){
			//need to change this line
			return rightLeftRotation(aShip); //maybe left right	
		}
	}
	else if(needBalance > 1){
		if(checkImbalance(aShip->m_left) >= 0){
			return rightRightRotation(aShip); //right rotation
		}
		else if(checkImbalance(aShip->m_left) <= 0){
			//need to change this line
			return leftRightRotation(aShip); 
		}
	}else{
		return aShip;
	}
}
*/
/*
Ship* Fleet::rightRotation(Ship* aShip){
	if(aShip == nullptr){
		return nullptr;
	}
	Ship *temp;
	temp = aShip->m_left;
	aShip->m_left = temp->m_right;
	temp->m_right = aShip;

	return temp;
}
*/
/*
Ship* Fleet::leftRotation(Ship* aShip){
	if(aShip == nullptr){
		return nullptr;
	}
	Ship* temp;
        temp = aShip->m_right;
	aShip->m_right = temp->m_left;
	temp->m_left = aShip;

	return temp;
}
*/

Ship* Fleet::rightRightRotation(Ship* aShip){  //single right rotation
	
	if(aShip == nullptr){
		return nullptr;
	}	

	Ship* temp = aShip;
	Ship* left = aShip->getLeft();
	temp->setLeft(aShip->getRight());
	left->setRight(temp);
	updateHeight(temp);
	updateHeight(left);
	return left;
}


Ship* Fleet::leftRightRotation(Ship* aShip){
	if(aShip == nullptr){
		return nullptr;
	}
	
	Ship* temp;
	temp = aShip->getLeft();
	aShip->setLeft(rightRightRotation(temp));
	return leftLeftRotation(aShip);
	//aShip->setLeft(leftLeftRotation(temp));
        //return rightRightRotation(aShip);
}

Ship* Fleet::rightLeftRotation(Ship* aShip){
	if(aShip == nullptr){
		return nullptr;
	}
	
	Ship *temp = nullptr;
	temp = aShip->getRight();
	aShip->setRight(leftLeftRotation(temp));
	return rightRightRotation(aShip);
	//aShip->setRight(rightRightRotation(temp));
	//return leftLeftRotation(aShip);

}


Ship* Fleet::leftLeftRotation(Ship* aShip){ //single left rotation

	if(aShip == nullptr){
		return nullptr;
	}

	Ship* temp = aShip;
	Ship* right = aShip->getRight();
	//temp->getRight() = right->getLeft();
	temp->setRight(right->getLeft());
	//right->getLeft() = temp;
	right->setLeft(temp);
	updateHeight(temp);
	updateHeight(right);
	return right;

}

void Fleet::dumpTree() const {
    dump(m_root);
}

void Fleet::dump(Ship* aShip) const{
    if (aShip != nullptr){
        cout << "(";
        dump(aShip->m_left);//first visit the left child
        cout << aShip->m_id << ":" << aShip->m_height;//second visit the node itself
        dump(aShip->m_right);//third visit the right child
        cout << ")";
    }
}
void Fleet::listShips() const {
	listShipsHelper(m_root); 
}

void Fleet::listShipsHelper(Ship* aShip) const{
	if(aShip == nullptr){
		return;
	}	
	listShipsHelper(aShip->m_left);
	cout << aShip->m_id << ":" << aShip->getStateStr() << ":" << aShip->m_type <<  endl;
	listShipsHelper(aShip->m_right);
}

bool Fleet::setState(int id, STATE state){
       bool setter = setStateHelper(m_root, id, state);

       if(setter == false){
       		return false; 
       }
       return true; 	
}

bool Fleet::setStateHelper(Ship* aShip, int id, STATE state){
	if(aShip == nullptr){
		return false;
	}
	else if(aShip->getID() == id){
		aShip->setState(state);
		return true;
	}
	else if(aShip->getID() < id){
		setStateHelper(aShip->getLeft(), id, state);
		return true;
	}
	else if(aShip->getID() > id){
		setStateHelper(aShip->getRight(), id, state);
		return true;
	}

	return false;
}


void Fleet::removeLost(){
	m_root = removeLostHelper(m_root);	 
}

Ship* Fleet::removeLostHelper(Ship* aShip){
	if(aShip == nullptr){
		return aShip;	
	}
	//case: no children
	if(aShip->getStateStr() == "LOST" && aShip->getLeft() == nullptr && aShip->getRight() == nullptr){
		delete aShip;
	}
	//case: one child
	else if(aShip->getStateStr() == "LOST" && aShip->getLeft() != nullptr && aShip->getRight() == nullptr){
		Ship *temp = aShip;
		aShip = aShip->getLeft();
		delete temp;
	}
	else if(aShip->getStateStr() == "LOST" && aShip->getLeft() == nullptr && aShip->getRight() != nullptr){
		Ship *temp = aShip;
		aShip = aShip->getRight();
		delete temp;
	}
	//case: two children
	else if(aShip->getStateStr() == "LOST" && aShip->getLeft() != nullptr && aShip->getRight() != nullptr){
		Ship *temp = findMin(aShip->getRight());
		aShip->setID(temp->getID());
		aShip->setType(temp->getType());
		aShip->setHeight(temp->getHeight());
		aShip->setState(temp->getState());
		//delete found node
		aShip->setRight(removeLostHelper(aShip->getRight()));
	}

	aShip = rebalance(aShip);
	
	return aShip;	
}

bool Fleet::findShip(int id) const {
	if(findShipHelper(m_root, id) == false){
		return false;
	}
	return true; 
}

bool Fleet::findShipHelper(Ship* aShip, int id) const{
	if(aShip == nullptr){
		return false;
	}
	if(aShip->getID() == id){
		return true;
	}
	else if(aShip->getID() < id){
		return findShipHelper(aShip->m_right, id);
	}
	return findShipHelper(aShip->m_left, id);	
}
