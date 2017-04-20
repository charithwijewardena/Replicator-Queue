#pragma once
#pragma once
#define VIEW_QUEUE_TARGET_FILE "C:/Users/hansc/Desktop/test.txt"

typedef struct _experiment *link;

typedef struct _experiment {
	char *name;
	int number;
	char *foulant;
	char *type;
	double startTime;
	double endTime;
	double duration;
	link next;
} experiment;

/*
a queue is represented by a pointer to a struct which contains
a pointer to the first experiment of the queue called the "head"
*/
typedef struct _queue {
	link head;
} *queue;

extern queue myQueue;
extern experiment myExperiment[100];
//extern char expName[100];
//extern char expFoulant[100];

void deleteQueue(queue myQueue);
void saveQueue(queue myQueue);
void rearrangeQueue(queue myQueue, link a, link b);
void deleteExperiment(queue myQueue, link a);
void addExperiment(queue myQueue, int free);
void viewQueue(queue myQueue);
int getFreeExperiment(queue myQueue);
link getLastExperiment(queue myQueue);