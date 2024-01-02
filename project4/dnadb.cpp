// CMSC 341 - Spring 2022 - Project 4
#include "dnadb.h"
DnaDb::DnaDb(int size, hash_fn hash){
	m_hash = hash;
	
	m_currentSize = 0;

	m_oldTable = nullptr;   //dont know if this is what i need to do
	m_oldCap = 0;
        m_oldSize = 0;
        m_oldNumDeleted = 0;

	if(size < MINPRIME){
		m_currentCap = MINPRIME;
	}else if(size > MAXPRIME){
		m_currentCap = MAXPRIME;
	}else if(isPrime(size) == true ){
		m_currentCap = size;
	}
	else if(isPrime(size) == false){
		//If the user passes a non-prime number the capacity must be set to the smallest prime number greater than user's value.
		m_currentCap = findNextPrime(size);
	}

	m_currentTable = new DNA[m_currentCap];

	for(unsigned int i = 0; i < m_currentCap; i++){
		m_currentTable[i] = EMPTY;
	}
}

DnaDb::~DnaDb(){
        
	delete[] m_currentTable;

	delete[] m_oldTable;

	m_currentTable = nullptr;
	m_currentCap = 0;
	m_currentSize = 0;
	m_currNumDeleted = 0;

	m_oldTable = nullptr;
	m_oldCap = 0;
	m_oldSize = 0;
	m_oldNumDeleted = 0;	
}

bool DnaDb::insert(DNA dna){
        int index;
	bool inserted = false;
	DNA exists = getDNA(dna.getSequence(), dna.getLocId());
        if(exists == dna){ //checking if duplicate exists
	        return false;
        }
	
	for(unsigned int i = 0; i < m_currentCap; i++){
		index = ((m_hash(dna.getSequence()) % m_currentCap) + (i * i)) % m_currentCap;
		if(m_currentTable[index] == EMPTY){
			m_currentTable[index] = dna;
			inserted = true;
			m_currentSize += 1;
			i = m_currentCap + 10; //end loop
		}
		else if(m_currentTable[index] == DELETED){
			m_currentTable[index] = dna;
			inserted = true;
			i = m_currentCap + 10; //end loop
		}
	}      
	//After every insertion we need to check for the proper criteria, and if it is required, we need to rehash the entire table incrementally into a new table.
	//old table doesnt exist yet
		
	//rehash
	//rehash happens when load factor is greater than 0.5	
	//lambda returns the load factor of the current table
	//need to make a test for rehash to see if it works	
	int loadFactor = lambda();

	if(loadFactor > 0.5){
		//rehash into current table
		m_oldTable = new DNA[m_currentCap];
		for(unsigned int i = 0; i < m_currentCap; i++){

			m_oldTable[i] = m_currentTable[i];
		}	
		m_currentCap = findNextPrime((m_currentSize - m_currNumDeleted)*4);
		m_currentTable = new DNA[m_currentCap];
		m_currentSize = 0;
			
	}

	int number;
	//m_oldSize++;

	//transferring into new bigger table
	number = (m_oldCap / 4) * m_oldSize;
	if(m_oldSize == 4){
		number = m_oldCap;
	}
	for(int i = 0; i < number; i++){
		if(m_oldTable[i] == DELETED || m_oldTable[i] == EMPTY){
			//pass
		}else{
			m_currentTable[i] = m_oldTable[i];
                	m_currentSize++;

                	m_oldTable[i] = DELETED;
		}
	}
	if(m_currentSize == 4){
		delete [] m_oldTable;
		m_oldTable = nullptr;
		m_oldSize = 0;
	}	
	
	return inserted; //for now
}

bool DnaDb::remove(DNA dna){
	//This function removes a data point from either the current hash table or the old hash table where the object is stored. 
	bool remove = false; 
	int index;
		
	//current table
	for(unsigned int i = 0; i < m_currentCap; i++){
		index = ((m_hash(dna.getSequence()) % m_currentCap) + (i * i)) % m_currentCap;
		if((m_currentTable[index].getSequence() == dna.getSequence()) && (m_currentTable[index].getLocId() == dna.getLocId())){
			remove = true;
			m_currentTable[index] = DELETED;
			i = m_currentCap + 10;
		} 
	}

	//old table
	for(unsigned int i = 0; i < m_oldCap; i++){
		index = ((m_hash(dna.getSequence()) % m_oldCap) + (i * i)) % m_oldCap;
		if((m_oldTable[index].getSequence() == dna.getSequence()) && (m_oldTable[index].getLocId() == dna.getLocId())){
			remove = true;
			m_oldTable[index] = DELETED;
			i = m_oldCap + 10;
		}		
	}	

	//rehash

	//rehash once the deleted ratio exceeds 80%.
	//When rehashing, 25% transfer refers to 25% of m_oldSize. 
	//We need to scan the table for the live data and transfer as many as required, once a live data is transferred it should be tagged as deleted in the old table.
	if((deletedRatio() > 0.8 && (m_oldTable == nullptr))){
		if(m_oldTable == nullptr){
			m_oldCap = findNextPrime((m_currentSize - m_currNumDeleted) * 4);
			m_oldTable = new DNA[m_oldCap];
			m_oldSize = 0;
		}else if(m_currentTable == nullptr){
			m_currentCap = findNextPrime((m_oldSize - m_oldNumDeleted) * 4);
			m_currentTable = new DNA[m_currentCap];
			m_currentSize = 0;
		}	
	}
	//if the item we want to transfer is in the old table, we dont want to skip looking over the old table cuz we might skip it
	//if in the middle of a rehash, want to make sure we remove that item	
	
	//rehash into the current table	
	//if old table exists it means you are rehashing
	//might have to get rid of this portion if it doesnt work
	if(m_currentTable != nullptr && m_oldTable != nullptr){
		int num;
		num = (m_oldCap / 4) * m_oldSize;
		
		if(m_oldSize == 4){
			num = m_oldCap;

		}
		for(int i = 0; i < num; i++){
			if(m_oldTable[i] == EMPTY || m_oldTable[i] == DELETED){
				//pass
			}else{
				m_currentTable[i] = m_oldTable[i];
				m_oldTable[i] = DELETED;
			}
		}
		if(m_oldSize == 4){
			delete [] m_oldTable;
			m_oldTable = nullptr;
			m_oldSize = 0;
		}
	}	
		
	return remove; //for now
}

DNA DnaDb::getDNA(string sequence, int location){
	//This function looks for the DNA object with sequence and location in the hash table, if the object is found the function returns it, otherwise the function returns empty object. 
	//If there are two hash tables at the time, the function needs to look into both tables.
	
	string emptyString = "";
	int emptyObjLocation = 0;
	DNA emptyObject(emptyString, emptyObjLocation);	
	
	int index;
	if(m_oldTable != nullptr){
		index = m_hash(sequence) % m_oldCap;
		for(unsigned int i =0; i < m_oldCap; i++){
			index = ((m_hash(sequence) % m_oldCap) + (i * i)) % m_oldCap;
			if(m_oldTable[index] == EMPTY){
				return m_oldTable[index];
			}
			else if((m_oldTable[index].getSequence() == sequence) && (m_oldTable[index].getLocId() == location)){
				return m_oldTable[index];
			}
		}
	}
	
	if(m_currentTable != nullptr){
		index = m_hash(sequence) % m_currentCap;
		for(unsigned int i = 0; i < m_currentCap; i++){
			index = ((m_hash(sequence) % m_currentCap) + (i * i)) % m_currentCap;
			if(m_currentTable[index] == EMPTY){
				return m_currentTable[index];
			}
			else if((m_currentTable[index].getSequence() == sequence) && (m_currentTable[index].getLocId() == location)){
				return m_currentTable[index];
			}
		}
	}

	return emptyObject;	

}

float DnaDb::lambda() const {
	/*This function returns the load factor of the current hash table. The load factor is the ratio of occupied buckets to the table capacity. 
	 * The number of occupied buckets is the total of available buckets and deleted buckets. 
	 * An occupied bucket is a bucket which can contain either a live data node (available to be used) or a deleted node.*/ 
   //based on whichever table is the current
   //current size and current num deleted	
   //  ---/m_currentCap
   //  num of occupiued buckets is current size;
   //
   // available buckets = current cap - current size
   // table capacity = current cap
   //ratio is occupied buckets / table capacity current cap
   //
   float loadFactor = 0.0;
   loadFactor = m_currentSize / m_currentCap;

   return loadFactor;

}

float DnaDb::deletedRatio() const {
	//This function returns the ratio of the deleted buckets to the total number of occupied buckets.
	// Returns the ratio of deleted slots in the new table
	// deleted ratio would be currNumDeleted / num of occupied buckets
	//  num of occupiued buckets is current size;
	
	float deleted = 0.0;
	deleted = m_currNumDeleted / m_currentSize;

	return deleted;
}

void DnaDb::dump() const {
    cout << "Dump for current table: " << endl;
    if (m_currentTable != nullptr)
        for (unsigned int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for old table: " << endl;
    if (m_oldTable != nullptr)
        for (unsigned int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}

bool DnaDb::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int DnaDb::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

DNA::DNA(string sequence, int location) {
    if ((location >= MINLOCID && location <= MAXLOCID) ||
        (location == 0 && sequence == "DELETED")){
        // this is a normal or a DELETED object
        m_sequence = sequence;
        m_location = location;
    }
    else{
        // this is the empty object
        m_sequence = "";
        m_location = 0;
    }
}

string DNA::getSequence() const {
    return m_sequence;
}

int DNA::getLocId() const {
    return m_location;
}

// Overloaded assignment operator
const DNA& DNA::operator=(const DNA& rhs){
    if (this != &rhs){
        m_sequence = rhs.m_sequence;
        m_location = rhs.m_location;
    }
    return *this;
}

// Overloaded insertion operator.  Prints DNA's sequence (key),
// and the location ID. This is a friend function in DNA class.
ostream& operator<<(ostream& sout, const DNA &dna ) {
    if (!dna.m_sequence.empty())
        sout << dna.m_sequence << " (Location ID " << dna.m_location << ")";
    else
        sout << "";
  return sout;
}

// Overloaded equality operator. This is a friend function in DNA class.
// To test inequality we may negate the results of this operator.
bool operator==(const DNA& lhs, const DNA& rhs){
    return ((lhs.m_sequence == rhs.m_sequence) && (lhs.m_location == rhs.m_location));
}
