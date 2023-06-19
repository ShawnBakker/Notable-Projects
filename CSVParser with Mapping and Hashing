/*
 * I believe I have completed:
 *  Map based on linked lists: YES
 *  Double hashing: YES
 *  Performance study: YES
 *
 *    --TIMINGS--
 * Hash Store -> .000362
 * Hash Fetch -> .000427
 * Linked Store -> .000136
 * Linked Fetch -> .040269
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>


typedef struct
{
    char    *symbol;
    char    *name;
    float    lastSale;
    float    marketCap;
    int      IPOyear;
} Company;

void PrintCompany(Company *c)
{
    printf("%s:\n", c->name);
    printf("\tSymbol: %s\n", c->symbol);
    /* .2f: only print two digits after the period. */
    printf("\tLast Sale: %.2f\n", c->lastSale);
    printf("\tMarket Capitalization: %.2f\n", c->marketCap);
    printf("\tYear of Initial Public Offering: %d\n", c->IPOyear);
}

void ReadFile(const char *filename, Company **companies_rv, int *numCompanies_rv)
{
    int  i, j;

    if (filename == NULL)
    {
        fprintf(stderr, "No filename specified!\n");
        exit(EXIT_FAILURE);
    }
    FILE *f_in = fopen(filename, "r");
    if (f_in == NULL)
    {
        fprintf(stderr, "Unable to open file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f_in, 0, SEEK_END);
    int numChars = ftell(f_in);
    // printf("The number of characters is %d\n", numChars);
    fseek(f_in, 0, SEEK_SET);

    char *file_contents = malloc(sizeof(char)*numChars+1);
    fread(file_contents, sizeof(char), numChars, f_in);
    file_contents[numChars] = '\0';
    fclose(f_in);
    /* Note: the memory for this array is used to populate
     * the fields of the companies.  If it is freed, then
     * the company structs all become invalid.  For the
     * context of this program, this array should not be 
     * freed. */

    // Find out how many lines there are
    int numLines = 0;
    for (i = 0 ; i < numChars ; i++)
        if (file_contents[i] == '\n')
            numLines++;
    // printf("Number of lines is %d\n", numLines);

    int      numCompanies = numLines-1; // first line is header info 
    Company *companies    = malloc(sizeof(Company)*numCompanies);

    /* strtok will parse the file_contents array.  
     * The first time we call it, it will replace every '"' with '\0'.
     * It will also return the first word before a 
     */
    int numColumns = 9;
    int numberOfQuotesPerColumn = 2;
    strtok(file_contents, "\"");
    for (i = 0 ; i < numberOfQuotesPerColumn*numColumns-1 ; i++)
         strtok(NULL, "\"");
    for (i = 0 ; i < numCompanies ; i++)
    {
         companies[i].symbol = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].name = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].lastSale = atof(strtok(NULL, "\""));
         strtok(NULL, "\"");
         companies[i].marketCap = atof(strtok(NULL, "\""));
         strtok(NULL, "\""); 

         /* Skip ADR TSO */
         strtok(NULL, "\"");
         strtok(NULL, "\"");

         companies[i].IPOyear = atoi(strtok(NULL, "\""));
         strtok(NULL, "\"");

         /* Skip Sector, Industry, Summary Quote */
         for (j = 0 ; j < 6 ; j++)
             strtok(NULL, "\"");

         //PrintCompany(companies+i);
    }

    /* Set parameters to have output values */
    *companies_rv    = companies;
    *numCompanies_rv = numCompanies;
}

int hash(char *name, long array_size)
{
    int hashval = 0;
    char *p = name;
    while (*p != '\0')
    {
        hashval = 31*hashval + *p;
        p++;
    }

    return hashval%array_size;
}

typedef struct 
{
    int         numElements;
    char      **keys;
    Company    *companies;
} MapBasedOnHashTable;
// Beginning of Hash implementation //
int hash2(char *name, long array_size)
{
	double dmod(double x, double y)
		{
			return x - (int)(x/y) * y;
		}
	int key = 0;
	double A = .53148; // constant value where 0 < A < 1 //
	char *p = name;
	while(*p != '\0')
	{
		key = 31*key + *p;
		p++;
	}
	double kA = key * A;
	double extracted = (dmod(kA, 2));
	return floor(array_size * extracted);
}
// IMPORTANT NOTE!!!! Must use gcc with -lm in order for "floor" to be recognized, so " gcc proj3D.c -lm "// 
// Beginning of Linked List Mapping implementation /
struct node
{
	Company *companies;
	struct node *next;
	char *value;
};
struct node *head;
struct node * PrintList()
{
	struct node *p;
	for (p = head; p != NULL; p = p->next)
		printf("s\n", p->value);
}
struct node *Insert(struct node *head, Company *companies)
{
	struct node *new = (struct node *)malloc(sizeof(struct node));
	new->value = companies->symbol;
	new->companies = companies;
	new->next= head;
	return new;
}
Company *Fetch(struct node *head, char *name)
{
	struct node* p = head;
	while (p != NULL)
	{
	/*	head = p->next;
		free(p->value);
		free(p);*/
	if(strcmp(p->value, name) == 0)
	{
		return p->companies;
	}
	p = p->next;
	}
	return NULL;

/*	struct node *previous = head;
	struct node *cur = head->next;

	while(cur != NULL)
	{
		if(strcmp(cur->value, name) == 0){
			previous->next = cur->next;
			free(cur);
			return head;
		}
		previous = cur;
		cur = cur->next;
	}
	return head;*/	

}
void InitializeMapBasedOnHashTable(MapBasedOnHashTable *map, int numElements)
{
    map->numElements = numElements;
    map->keys = malloc(sizeof(char *)*numElements);
    map->companies = malloc(sizeof(Company)*numElements);
    for (int i = 0 ; i < numElements ; i++)
        map->keys[i] = NULL;
}

void StoreTo_MapBasedOnHashTable(MapBasedOnHashTable *map, Company *companies)
{
    int hashval = hash(companies->symbol, map->numElements);
    int hashkey = hash2(companies->symbol, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval+i*hashkey)%(map->numElements);
        if (idx < 0) idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            map->keys[idx]      = companies->symbol;
            map->companies[idx] = *companies;
            return;
        }
    }
}

Company *
FetchFrom_MapBasedOnHashTable(MapBasedOnHashTable *map, char *key)
{
    int hashval = hash(key, map->numElements);
    int hashkey = hash2(key, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval+i*hashkey)%(map->numElements);
        if (idx < 0) idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            return NULL;
        }

        if (strcmp(map->keys[idx], key) == 0)
        {
            return &(map->companies[idx]);
        }
    }
    
    return NULL;
}

void FetchAndPrint(MapBasedOnHashTable *mfht, char *key)
{
    Company *c = FetchFrom_MapBasedOnHashTable(mfht, key);
    if (c == NULL)
    {
        printf("Key %s has no corresponding company\n", key);
    }
    else
    {
        PrintCompany(c);
    }

}

int main(int argc, char *argv[])
{
    Company *companies = NULL;
    int      numCompanies;
    ReadFile(argv[1], &companies, &numCompanies);
    MapBasedOnHashTable mfht;
    struct timeval startTime;
    struct timeval endTime;
    struct node *cur = NULL;
    printf("num companies is %d\n", numCompanies);
    InitializeMapBasedOnHashTable(&mfht, numCompanies*2);
    // TIMERS //
    double hash2_store = 0., hash2_fetch = 0., ll_store = 0., ll_fetch = 0.;

    //Hash2 Store Time
    gettimeofday(&startTime, 0);
    for (int i = 0 ; i < numCompanies ; i++)
    {
        StoreTo_MapBasedOnHashTable(&mfht, companies+i);
    }
    gettimeofday(&endTime, 0);
    hash2_store = (double)(endTime.tv_sec - startTime.tv_sec) + (double)(endTime.tv_usec - startTime.tv_usec) / 1000000;
    printf("Hash Table Timing (Store): %f\n", hash2_store);

    //Hash2 Fetch Time
    gettimeofday(&startTime, 0);
    for (int i = 0 ; i < numCompanies ; i++)
    {
        FetchFrom_MapBasedOnHashTable(&mfht, (companies+i)->symbol);
    }
    gettimeofday(&endTime, 0);
    hash2_fetch = (double)(endTime.tv_sec - startTime.tv_sec) + (double)(endTime.tv_usec - startTime.tv_usec) / 1000000;
    printf("Hash Table Timing (Fetch): %f\n", hash2_fetch);

    //Linked List Store Time
    gettimeofday(&startTime, 0);
    for (int i = 0 ; i < numCompanies ; i++)
    {
        cur = Insert(cur, (companies + i));
    }
    gettimeofday(&endTime, 0);
    ll_store = (double)(endTime.tv_sec - startTime.tv_sec) + (double)(endTime.tv_usec - startTime.tv_usec) / 1000000;
    printf("Linked List Timing (Store): %f\n", ll_store);

    //Linked List Fetch Time
    gettimeofday(&startTime, 0);
    for (int i = 0 ; i < numCompanies ; i++)
    {
        Fetch(cur, (companies + i)->symbol);
    }
    gettimeofday(&endTime, 0);
    ll_fetch = (double)(endTime.tv_sec - startTime.tv_sec) + (double)(endTime.tv_usec - startTime.tv_usec) / 1000000;
    printf("Linked List Timing (Fetch): %f\n", ll_fetch);
    FetchAndPrint(&mfht, "ZNWAA");
    FetchAndPrint(&mfht, "Z");
    FetchAndPrint(&mfht, "ZIOP");
    FetchAndPrint(&mfht, "ZIOQ");
    FetchAndPrint(&mfht, "YIOQ");
    FetchAndPrint(&mfht, "QIOQ");
    FetchAndPrint(&mfht, "WIOQ");
    FetchAndPrint(&mfht, "XIOQ");
    FetchAndPrint(&mfht, "TIOQ");
    FetchAndPrint(&mfht, "UIOQ");
    FetchAndPrint(&mfht, "VIOQ");
    
}

/* YOUR PERFORMANCE STUDY WRITEUP GOES HERE:
 	The second hash function I used was based on "multiplication method hashing". It involved using a constant value, A, a key value, and then extracting the remainder that the product of k and A (kA) would give. This remiander wiould be the resulting hash value.

	Based on the timings of the hash table and linked lists, it seems that the linked list was faster than the hash tables in regards to storing, but when it came to fetching, the hash table was faster. I would assume that this is because the time complexity of Fetch() for hash tables are O(n), but also because we aren't using a search function, which would benefit the hash table. Lastly, insertions and deletions are always O(1) for linked lists, but sometimes are O(n) for hash tables.
	-Shawn
 */

