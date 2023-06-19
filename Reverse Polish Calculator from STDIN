#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
   ADD,
   MULTIPLY,
   SUBTRACT,
   DIVIDE,
   UNSUPPORTED
} MathOperation;

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
	if (strlen(op) == 1){
    if (*op == '+'){
	    return ADD;
    }
    if (*op == '-'){
	    return SUBTRACT;
    }
    if (*op == 'x'){
	    return MULTIPLY;
    }
    if (*op == '/'){
	    return DIVIDE;
    }
	
    else{
	    IssueBadOperationError();
    }
	}
    else{
	    IssueBadOperationError();
    }

}


double StringToDouble(char *str)
{
   double res = 0;
   double dec_res = 0;
   bool decimal_stat = false;
   bool neg_mark = false;
   int i;
   int count = 0;
   int decimals = 0;
   if (*str == '-'){
	   *str++;
	   neg_mark = true;
   }
   while (*str != '\0'){
	   if ((*str >= '0' && *str <= '9') || (*str == '.')){
		   if (decimal_stat == false){
			   if (*str == '.'){
				   decimal_stat = true;
				   decimals++;
				   str++;
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
				   count++;
				   dec_res = dec_res * 10 + (*str - '0');
				   str++;
			   }
		   }
		   else{
			   IssueBadNumberError();
		   }
					 
}
if (decimals > 1){
	IssueBadNumberError();
}
for (i = 1; i <= count; i++){
	dec_res = dec_res / 10;
}
if (neg_mark == true){
	return res * -1 - dec_res;
}
else{
	return res + dec_res;
}
}

int main(int argc, char *argv[])
{
    double v = StringToDouble(argv[1]);
    MathOperation op = GetOperation(argv[2]);
    double v2 = StringToDouble(argv[3]);
    double result = 0.;
    switch (op)
    {
       case ADD:
         result = v+v2;
         break;
	 case SUBTRACT:
	 result = v-v2;
	 break;
       case MULTIPLY:
	 result = v*v2;
	 break;
       case DIVIDE:
	 result = v/v2;
	 break;
       case UNSUPPORTED:
	 IssueBadOperationError();
	 break;
    }
    printf("%d\n", (int) result);
 
    return 0;
}
