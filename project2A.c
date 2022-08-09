#include <stdio.h>

int main()
{
	int n;
	int x;
	for (n = 15; n < 500; n = n + 2){
		for (x = 2; x < n; x = x+1){
	if (n % x == 0){
				printf("%d is a composite number.\n", n);
			break;	
				}
	}
	}
	return 0;

}

