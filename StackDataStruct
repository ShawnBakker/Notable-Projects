#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef enum
{
   ADD,
   MULTIPLY,
   SUBTRACT,
   DIVIDE,
   UNSUPPORTED
} MathOperation;

typedef struct
{
int top;
double *stack;
int max;
} Stack;

int is_empty(Stack *s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}

int is_full(Stack *s)
{
	if (s->top == s->max)
		return 1;
	else
		return 0;
}

void Initialize(Stack *s, int max)
{
	//s = malloc(sizeof(Stack));
	s->top = -1;
	s->max = max;
	s->stack = malloc(sizeof(double) * s->max);
}

void Push(Stack *s, double X)
{
	if (is_full(s))
	{
		//printf("Stack pushed %d\n", X);
		printf("Overflow, stack is full\n");
		exit(EXIT_FAILURE);
	}
	else {
		s->stack[++s->top] = X;
	}
		

}

double Pop(Stack *s)
{
	if (!is_empty(s))
	{
		double rv = s->stack[s->top--];
		return rv;
		// printf("Stack popped %d\n", rv);
        }
	else {
		printf("Underflow, stack is empty.\n");
		exit(EXIT_FAILURE);
	}
}


void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}

MathOperation GetOperation(char *op)
{
    if (*op  == '+')
	    return ADD;
    if (*op  == '-')
	    return SUBTRACT;
    if (*op  == 'x')
	    return MULTIPLY;
    if (*op == '/')
	    return DIVIDE;
    else{
	   return UNSUPPORTED;
}
}


double StringToDouble(char *str)
{
    double res = 0;
    double dec_res = 0;
    bool ret_bool = false;
    int count = 0;
    int i;
    bool neg_mark = false;
    int decimals = 0;
    
if (str[0] == '-'){
*str++;
neg_mark = true;
}
    while (*str != '\0'){
	    if ((*str >= '0' && *str <= '9') || (*str == '.')){
		    if (ret_bool == false){
			    if (*str == '.'){
				    ret_bool = true;
				    str++;
				    decimals++;
				    
				    // printf("Check decimals: %d\n", decimals);
			    }
			    else{
				    res = res * 10 + (*str - '0');
				    str++;
				    
			    }
		    }
			    else{
				    if (*str == '.'){
					    decimals++;
				    }
				    dec_res = dec_res * 10 + (*str - '0');
				    str++;
				    count++;
				 //   printf("COUNT : %d\n", count);
				    
			    }
	    }
		    }
   
	    



for (i = 1; i <= count; i++){
	dec_res = dec_res/10;
}
if (neg_mark == true){
	return (res + dec_res) * -1;
	
}
else{
	return res + dec_res;

}
}
int main(int argc, char *argv[])
{
  //  Stack *s = malloc(sizeof(Stack));
    Stack s;
    Initialize(&s, argc);
    /*double v = StringToDouble(argv[1]);*/
   //  Push(&s, v);
    //MathOperation op = GetOperation(argv[3]);
   //  double v2 = StringToDouble(argv[2]);
   //  Push(&s, v2);
    double result = 0.;
    int i;
    double x= 0.;
    double v =0.;
    double v2= 0.;
    MathOperation op;	    


for (i = 1; i < argc; i++)
{

    op = GetOperation(argv[i]);
    switch (op)
    {
       case ADD:
      	 v2 = Pop(&s);
	 v = Pop(&s);	 
         result = v + v2;
	 Push(&s, result);
         break;
       case SUBTRACT:
      	 v2 = Pop(&s);
	 v = Pop(&s);	 
	 result = v - v2;
	 Push(&s, result); 
	 break;
       case MULTIPLY:
      	 v2 = Pop(&s);
	 v = Pop(&s);	 
	 //fprintf(stderr, "v's value %f , %f\n", v , v2);
	 result = v * v2;
	 Push(&s, result);
	 break;
       case DIVIDE:
      	 v2 = Pop(&s);
	 v = Pop(&s);	 
	 result = v/v2;
	 Push(&s, result);
	 break;
       case UNSUPPORTED:
	 x = StringToDouble(argv[i]);
	 Push(&s, x);
	 break;
    }

    }
    printf("The total is %d\n", (int) result);
 
    return 0;
}
