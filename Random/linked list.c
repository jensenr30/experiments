



#include <stdio.h>


//this is the linked list node
struct myNode{
	int data;
	struct myNode *nextNode;
};


int main(){
	
	//declares nodes in linked list
	struct myNode node1, node2, node3, node4;
	// declares the current node pointer that points to the current node (a thing that does a thing)
	struct myNode *currentNode;
	
	// initialize data
	node1.data = 1;
	node2.data = 4;
	node3.data = 9;
	node4.data = 16;
	
	//set up the links from node to node
	node1.nextNode = &node3;
	node2.nextNode = &node4;
	node3.nextNode = &node2;
	node4.nextNode = NULL;
	// initial node that you start on
	currentNode = &node1;
	
	while(1){
		printf("%d\n", currentNode->data);
		
		//if this is the end of the list, break out of the while(1) loop
		if(currentNode->nextNode == NULL) break;
		else{
			// go to the next node if you have a valid node next.
			currentNode = currentNode->nextNode;
		}
	}
	
	return 0; // ze eand
}




















































//dalmatians
