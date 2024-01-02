// CMSC 341 - Spring 2022 - Project 3
#include "squeue.h"
SQueue::SQueue(prifn_t priFn, HEAPTYPE heapType)
{
	m_heap = nullptr;
	m_size = 0;
	m_priorFunc = priFn;
      	m_heapType = heapType;
}

SQueue::~SQueue()
{
	clear(); 
}

SQueue::SQueue(const SQueue& rhs)
{
	m_heap = copyConstructorHelper(rhs.m_heap);
        m_size = rhs.m_size;
	m_priorFunc = rhs.m_priorFunc;
	m_heapType = rhs.m_heapType;	
}

Node* SQueue::copyConstructorHelper(const Node* rhs){
	//recursive copy constructor helper 
	
	if(rhs == nullptr){
		return nullptr;
	}
	
	Node* newHeap = new Node(rhs->getPost());
	newHeap->m_left = copyConstructorHelper(rhs->m_left);
	newHeap->m_right = copyConstructorHelper(rhs->m_right);
	
	return newHeap;

}

SQueue& SQueue::operator=(const SQueue& rhs)
{
	if(this != &rhs){
		clear();
		//protect against self assignment
		m_heap = copyConstructorHelper(rhs.m_heap);  
		m_size = rhs.m_size;
		m_priorFunc = rhs.m_priorFunc;
		m_heapType = rhs.m_heapType;
	}
	return *this; 
}

void SQueue::insertPost(const Post& post) {
	Node *newNode = new Node(post);
	
	m_heap = mergeWithQueueHelper(m_heap, newNode);	
	m_size++;
}


Post SQueue::getNextPost() {
	//Extract (remove the node) and return the highest priority post from the queue. Must maintain the min-heap or max-heap property. 
	//The function throws an out_of_range exception if the queue is empty when the function is called.
	if(m_heap == nullptr){
		throw std::out_of_range("Empty Queue"); 
	}
		
	return m_heap->getPost(); //for now		    
}

Post SQueue::getNextPostHelper(Node* tracker){
	/*Extract (remove the node) and return the highest priority post from the queue. Must maintain the min-heap or max-heap property. 
	 * The function throws an out_of_range exception if the queue is empty when the function is called.*/
	//re-adjust the tree 	or use insert and send all of the nodes to insert and create a new tree
	//make the most right leaf node as new root and adjust the tree
	//search extract from min or max tree
	//
	//tracker = getNextPostHelper(tracker->m_right);
		
		
	return tracker->getPost(); //for now	
}

void SQueue::mergeWithQueue(SQueue& rhs) {
	if(this->getPriorityFn() != rhs.getPriorityFn()){
		//throw domain error
		throw std::domain_error("Queues have different priority functions.");
	}		
	else{
		m_heap = mergeWithQueueHelper(rhs.m_heap, m_heap);	  
	}
}

Node* SQueue::mergeWithQueueHelper(Node* firstNode, Node* secondNode){
	
	/*This function merges the host queue with the rhs; it leaves rhs empty. Two skew heaps can only be merged if they have the same priority function. 
	 * If the user attempts to merge queues with different priority functions, a domain_error exception should be thrown. 
	 * This function requires protection against self-merging.
	 * Merging a heap with itself is not allowed.*/			
	
	/*
	 * If p1 is Null, return p2; similarly, if p2 is Null, return p1. (done)
	 *Assume that p1 has higher priority than p2; if not, swap, p1 and p2. 
	 *Swap the left and right subtrees of p1.
	 *Recursively merge p2 and the left subtree of p1, replacing the left subtree of p1 with the result of the recursive merge.
	*/

	//this/m_heap - p1
	//mergeQueue - p2
	
		

	Node* temp = nullptr;
	if(firstNode == nullptr){
		return secondNode;
	}
	else if(secondNode == nullptr){
		return firstNode;
	}
	
	//MAXHEAP
	if(m_heapType == MAXHEAP && m_priorFunc(firstNode->getPost()) < m_priorFunc(secondNode->getPost())){ 
		temp = firstNode;
		firstNode = secondNode;
		secondNode = temp;
	}
	
	//MINHEAP
	else if(m_heapType == MINHEAP && m_priorFunc(firstNode->getPost()) > m_priorFunc(secondNode->getPost())){
		temp = secondNode;
		secondNode = firstNode;
		firstNode = temp;
	}

	temp = firstNode->m_left;
	firstNode->m_left = firstNode->m_right;
	firstNode->m_right = temp;

	firstNode->m_left = mergeWithQueueHelper(firstNode->m_left, secondNode);
	
		
	return firstNode;
}

void SQueue::clear() {
	m_heap = clearHelper(m_heap); 
}

Node* SQueue::clearHelper(Node* heap){
	//recursive clear helper
	if(heap == nullptr){
		return nullptr;
	}
	
	clearHelper(heap->m_right);
	clearHelper(heap->m_left);

	delete heap;
	heap = nullptr;

	return heap;
	
}

int SQueue::numPosts() const{
	return m_size; 
}

void SQueue::printPostsQueue() const {
	printPostsQueue(m_heap); 
}

void SQueue::printPostsQueue(Node* heap) const {
	//prints content of queue using preorder traversal
	if(heap == nullptr){
		return; 
	}

	cout << heap->getPost() << endl;
	
	printPostsQueue(heap->m_left);
	printPostsQueue(heap->m_right);
}

prifn_t SQueue::getPriorityFn() const {
      return m_priorFunc;	
}

void SQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
        m_priorFunc = priFn;
	m_heapType = heapType;	
	//use getNextPost 
	//have current heap and create new heap
	//call getnextpost on current heap
	//returns node and insert into new heap with the new priority value already set in insert
	//remove from current heap
	//current heap will be empty and new heap will have all the nodes in a different order
	//make sure at the end m_heap points to the new heap and not the old heap
	//
	
	//dynamically allocate copy of queue with new priority Squeue *curr = new Queue(prifn);
	
	//SQueue *curr = new SQueue(priFn, heapType);

	//send copy queue to set priority helper to insert all objects curr->setPiorityFunctionHelper(m_heap, curr)
	
	//set m_priFn to priFn
	
	//set m_heap to copy queue's m_heap
	
	//copy size
	//
	//set curr m_heap to nullptr
	//delete curr
	//helper has two parameters setPriority(node* curr, Squeue *curr)  (gonna be a void function helper)
	//
}


//set priority fn helper
//
//if(curr == nullptr) { return }
void SQueue::setPriorityFnHelper(Node* heap, Node* curr){
		if(curr == nullptr){
			return;
		}
}


void SQueue::dump() const
{
  if (m_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(m_heap);
    cout << endl;
  }
}

void SQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    cout << m_priorFunc(pos->m_post) << ":" << pos->m_post.getPostID();
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Post& post) {
  sout << "Post ID: " << post.getPostID() 
        << ", number of likes: " << post.getNumLikes()
        << ", interest level: " << post.getInterestLevel() 
        << ", connection level: " << post.getConnectLevel()
        << ", post time: " << post.getPostTime();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getPost();
  return sout;
}
