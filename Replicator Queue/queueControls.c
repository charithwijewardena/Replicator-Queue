#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "resource.h"
#include "queueDefs.h"

// ***queue functions***

// deletes the queue and frees memory 
void deleteQueue(queue myQueue) {

}

// saves queue details for later use
void saveQueue(queue myQueue) {

}

// rearranges experiments within the queue
void rearrangeQueue(queue myQueue, link a, link b) {

}

// deletes a given experiment within the queue
void deleteExperiment(queue myQueue, link a) {

}

// adds an experiment to the queue
void addExperiment(queue myQueue, int free) {
	// depending on the duration, start and end times are added here
	if (myQueue->head == NULL) {
		myQueue->head = &myExperiment[free];
		//assert(myQueue->head->name == name);
	}
	else {
		link temp = myQueue->head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		assert(temp->next == NULL);
		temp->next = &myExperiment[free];
		//assert(temp->name == name);
	}
	//assert(myQueue->head->name == "t");
	/*const char *tempTargetFile = VIEW_QUEUE_TARGET_FILE;
	FILE *f = fopen(tempTargetFile, "w");
	fprintf(f, "%s\n", myQueue->head->name);
	fclose(f);*/
	//fprintf(f, L"%S\n", temp->name);
}

// returns a pointer to the last experiment added to the queue
link getLastExperiment(queue myQueue) {
	link temp = myQueue->head;
	if (myQueue->head == NULL) {
		link temp2 = malloc(sizeof(link));
		return temp2;
	}
	else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		return temp;
	}
}

// returns the number of the next free experiment on the queue
// *** NOTE: if 3 is the return value, this is nodes[3] (4th experiment) ***
int getFreeExperiment(queue myQueue) {
	int i = 0;
	link temp = myQueue->head;
	assert(temp == myQueue->head);
	if (myQueue->head == NULL) {
		return i;
	}
	else {
		while (temp->next != NULL) {
			temp = temp->next;
			i = i + 1;
		}
		return (i + 1);
	}
}

void viewQueue(queue myQueue) {
	const char *tempTargetFile = VIEW_QUEUE_TARGET_FILE;
	FILE *f = fopen(tempTargetFile, "w"); // create text file
	link temp = myQueue->head;
	//fprintf(f, L"%S\n", myQueue->head->name);
	//fprintf(f, L"%S\n", temp->name);
	if (temp == NULL) {
		fprintf(f, "%s\n", "The queue is empty.");
	}
	else {
		while (temp != NULL) {
			//assert(temp->name == "test");
			fprintf(f, "%s", "Experiment Number: ");
			fprintf(f, "%d\n", temp->number);
			fprintf(f, "%s", "Experiment Name: ");
			fprintf(f, "%s\n", temp->name);
			fprintf(f, "%s", "Experiment Type: ");
			fprintf(f, "%s\n", temp->type);
			fprintf(f, "%s", "Foulant: ");
			fprintf(f, "%s\n", temp->foulant);
			fprintf(f, "%s", "Duration: ");
			fprintf(f, "%d\n", temp->duration);
			temp = temp->next;
			fprintf(f, "\n");
		}
	}
	fclose(f);
}