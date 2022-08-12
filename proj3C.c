
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

typedef struct
{
	int num_elements;
	int front;
	int back;
	char **strings;

} Queue;

void InitializeQueue(Queue *q)
{	
	q->num_elements = 0;
	q->front = 0;
	q->back = 0;
	q->strings = malloc(sizeof(char *) * QUEUE_SIZE);
}

void Enqueue(Queue *q, char *val)
{
	q->strings[q->back] = val;
	if (q->back == QUEUE_SIZE-1)
	{
		q->back = 0;
	}

	q->back++;
	q->num_elements++;
}

char * Dequeue(Queue *q)
	{
		char * val = q->strings[q->front];
		q->strings[q->front] = NULL;
		if (q->front == QUEUE_SIZE-1)
		{
			q->front = 0;
		}
		q->front++;
		q->num_elements--;
		return val;
	}
char * Front(Queue *q)
{
	return q->strings[q->front];
}


void
PrintQueue(Queue *q)
{
    int i;
    printf("Printing queue %p\n", q);
    printf("\tThe index for the front of the queue is %d\n", q->front);
    printf("\tThe index for the back of the queue is %d\n", q->back);
    if (q->front == q->back)
    {
        printf("\tThe queue is empty.\n");
        return;
    }
    int back = q->back;
    if (q->back < q->front)
    {
        // wrapped around, so modify indexing 
        back += QUEUE_SIZE;
    }

    for (i = q->front ; i < back ; i++)
    {
        printf("\t\tEntry[%d] = \"%s\"\n", i%QUEUE_SIZE, q->strings[i%QUEUE_SIZE]);
    }
}
 


void
PrettyPrintQueue(Queue *q, char *type)
{
    if (Front(q) == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
        while ((s = Dequeue(q)))
        {
            printf("%s\n", s);
        }
    }
}
 

char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len+1);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}



int main(int argc, char *argv[])
{
/***  STEP #1: Test your queue code.  ***/
    /*Queue q;
    InitializeQueue(&q);
    PrintQueue(&q);
    Enqueue(&q, "hello");
    PrintQueue(&q);
    Enqueue(&q, "world");
    PrintQueue(&q);
    printf("Dequeue: %s\n", Dequeue(&q));
    PrintQueue(&q);*/
/* Gives this output (with different pointers):
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 1
	The index for the back of the queue is 2
		Entry[1] = "world"
 */

/*** STEP #2: read in from the input file (argc/argv stuff). 
     NewString is likely helpful here.
 ***/	
	Queue hospitals;
	Queue male_donors;
	Queue female_donors;
	Queue male_recipients;
	Queue female_recipients;
	InitializeQueue(&hospitals);
	InitializeQueue(&male_donors);
	InitializeQueue(&female_donors);
	InitializeQueue(&male_recipients);
	InitializeQueue(&female_recipients);
	FILE *f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("Invalid file\n");
		exit(EXIT_FAILURE);
	}
	//int nbytes = ftell(f);
	char buff[100];
	char * hosp_name;
	char * recip_name;
	char * donor_name;
	while(fgets(buff, 256, f)){
		if(buff[0] == 'H')
		{
			hosp_name = NewString(buff+2);
			Enqueue(&hospitals, hosp_name);
		}
		else if(buff[0] == 'R')
		{
		       	if(buff[2] == 'F')
			{
				recip_name = NewString(buff+4);
				Enqueue(&female_recipients, recip_name);
			}
			if(buff[2] == 'M')
			{
				recip_name = NewString(buff+4);
				Enqueue(&male_recipients, recip_name);
			}

		}
		else if(buff[0] == 'D')
		{
			if(buff[2] == 'F')
			{
				donor_name = NewString(buff+4);
				Enqueue(&female_donors, donor_name);
			}
			if(buff[2] == 'M')
			{
				donor_name = NewString(buff+4);
				Enqueue(&male_donors, donor_name);
			}
		}
		if(female_donors.num_elements > 0 && female_recipients.num_elements > 0 && hospitals.num_elements > 0){
		char *	donor = Dequeue(&female_donors);
		char *	recip = Dequeue(&female_recipients);
		char *	hosp = Dequeue(&hospitals);
    printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
		}
		if(male_donors.num_elements > 0 && male_recipients.num_elements > 0 && hospitals.num_elements > 0){
		char *	donor = Dequeue(&male_donors);
		char *	recip = Dequeue(&male_recipients);
		char *	hosp = Dequeue(&hospitals);
    printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
		}
	}
	 





/*** STEP #3: *after* your queue code works and *after* you can read the file, 
     implement the prompt ***/
/* Here are some helpful lines of code:
 *
 *  My print statement for a match:
 *
    printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
 *
 *
 *  My print statements for the contents of the queues at the end:
 */
    PrettyPrintQueue(&female_donors, "female donors");
    PrettyPrintQueue(&female_recipients, "female recipients");
    PrettyPrintQueue(&male_donors, "male donors");
    PrettyPrintQueue(&male_recipients, "male recipients");
    PrettyPrintQueue(&hospitals, "hospitals");
    
}
