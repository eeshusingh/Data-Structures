
#include "section.h"
Section::Section(){
	m_numStudents = 0;
	m_numGradingItems = 0;
	m_grades = nullptr;

}

Section::Section(int items, int students){
	//if(items <= 0){
	//	m_numGradingItems = 0;
	//}
	//if(students <= 0){
	//	m_numStudents = 0;
	//}
	m_numGradingItems = items;
	m_numStudents = students;	
	if(m_numGradingItems <= 0 && m_numStudents <= 0){
		m_numGradingItems = 0;
		m_numStudents = 0;
		m_grades = nullptr;
	}else{

		m_numGradingItems = items;
		m_numStudents = students;
		m_grades = new double*[m_numStudents];
		for(int i = 0; i < m_numStudents; i++){
			
			m_grades[i] = new double[m_numGradingItems];
			for(int j = 0; j < m_numGradingItems; j++){
				m_grades[i][j] = 0;
			}
		}
	}
    
}

Section::~Section(){
	if(m_grades){
		for(int i = 0; i < m_numStudents; i++){
			delete [] m_grades[i];
		}
	}	
	delete[] m_grades;
	m_grades = nullptr;
}

void Section::clear(){
	if(m_grades){
                for(int i = 0; i < m_numStudents; i++){
                        delete [] m_grades[i];
                }
        }

	delete[] m_grades;
       	
	m_numStudents = 0;
	m_numGradingItems = 0;
}

void Section::insert(){
	
	Random randNum = Random(0, 100, UNIFORMREAL);
	
	for(int i = 0; i < m_numStudents; i++){
		for(int j = 0; j < m_numGradingItems; j++){
			m_grades[i][j] = randNum.getRealRandNum();
		}
	}
		    
}

double Section::studentAverage(int student){
   	//need to know which student i want to average grade
	//int student is the student id, go over a loop of alll grading item and each time i get 
	//the m_grade of that student and all the grading items of that student
	double total_grade = 0; 
	double avg = 0;
	
	if( (m_numStudents == 0) || (student > (m_numStudents - 1) ) || (student < 0)){
		return 0.0;
	}else{
	
		for(int j = 0; j < m_numGradingItems; j++){
		 	total_grade += m_grades[student][j];
		 }

		avg = total_grade/m_numStudents;
	}
	
	return avg;
	
}

double Section::quizAverage(int quiz){
	
	double quiz_total = 0;
	double quiz_avg = 0.0;
	
	if( (m_numStudents == 0) || (quiz > (m_numGradingItems - 1) ) || (quiz < 0)){
                return quiz_total;
	}else{

		for(int i = 0; i < m_numStudents; i++){
			quiz_total += m_grades[i][quiz - 1];
		}
	
		quiz_avg = quiz_total/m_numGradingItems;
	}
	return quiz_avg;	
}

double Section::classAverage(){
	
	double sum = 0;
	double class_avg = 0.0;	
	if(m_numStudents <= 0){
		return class_avg;
	}else{
	
		for(int i = 0; i < m_numStudents; i++){
			sum += studentAverage(i);
		}
	
		class_avg = sum/m_numStudents;
	}
	return class_avg;

       	
}

Section::Section(const Section& rhs){
	m_numStudents = rhs.m_numStudents;
	m_numGradingItems = rhs.m_numGradingItems;
	
	m_grades = new double*[m_numStudents];
        for(int i = 0; i < m_numStudents; i++){
                m_grades[i] = new double[m_numGradingItems];
        }
	
	for(int i = 0; i < rhs.m_numStudents; i++){
		for(int j = 0; j < rhs.m_numGradingItems; j++){
			m_grades[i][j] = rhs.m_grades[i][j];	
		}
	}
		
}

const Section& Section::operator=(const Section& rhs){
	if(&rhs != this){
		clear();
		m_numStudents = rhs.m_numStudents;
        	m_numGradingItems = rhs.m_numGradingItems;
        
        	m_grades = new double*[m_numStudents];
        	for(int i = 0; i < m_numStudents; i++){
                	m_grades[i] = new double[m_numGradingItems];
        	}
        
        	for(int i = 0; i < rhs.m_numStudents; i++){
        	        for(int j = 0; j < rhs.m_numGradingItems; j++){
                	        m_grades[i][j] = rhs.m_grades[i][j];
               		}
        	}
	}

	return *this;
}

void Section::dump(){
    if (m_numGradingItems > 0 && m_numStudents > 0 && m_grades != nullptr){
        cout << setw(8) << "        ";
        for (int a=1;a<=m_numGradingItems;a++)
            cout << setw(8) << "Quiz" << a;
        cout << endl;
        for (int i=1;i <= m_numStudents;i++){
            cout << setw(8) << "Student" << i << " ";
            for (int j=1;j<=m_numGradingItems;j++){
                cout << setw(8) << m_grades[i-1][j-1] << " ";
            }
            cout << endl;
        }
    }
}
