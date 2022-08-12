#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void BadWordEntryError()
{
	printf("This word contains characters that are not permitted.\n");
	exit(EXIT_FAILURE);
}

		char *my_strcat(char *s1, const char *s2){
			if ((s1 == NULL) && (s2 == NULL))
				return NULL;
			char *start = s1;
			while (*start != '\0'){
				start++;
			}
			while (*s2 != '\0'){
			
				*start++ = *s2++;
			}
			*start = '\0';
			return s1;
		}

	int SearchForWord(char *txt, char *search_word){
		char *tester_str = " ,.\n";
		int words = 0;
		int t = 0;
		int excess = 0;
		unsigned char *tmp = malloc(100);
		//if (strcmp(tester_str, search_word) > 0){
		//	BadWordEntryError();
		//}
		int i = 0;
		     while (t < strlen(txt)){
			     for (i = 0; i < strlen(txt); i++){
					if ((txt[t] == ' ') || (txt[t] == ',') || (txt[t] == '.') || (txt[t] == '\n')){
						t++;
					        break;
					}
					if(txt[t] != '\0'){
						tmp[i] = txt[t];
						t++;
					}
			     }

				if (strlen(tmp) == strlen(search_word)){
					if (strncmp(tmp, search_word, strlen(tmp)) == 0){
						words++;
					}

				}
				
			
						int cool_size = strlen(tmp);
						for (int o = 0; o <= cool_size; o++){
							tmp[o] = '\0';
						} 
		     }
			free(tmp);
			return words;
	}
int main(int argc, char *argv[])
{
	int i;
	FILE *f_in = fopen(argv[1], "r");
	if (f_in == NULL)
	{
		printf("%s\" is not a valid file.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	fseek(f_in, 0, SEEK_END);
	int nbytes = ftell(f_in);
	unsigned char *buff = malloc(nbytes);
	fseek(f_in, 0, SEEK_SET);
	fread(buff, sizeof(unsigned char), nbytes, f_in);

	for (i = 2; i < argc; i++){
                int result = SearchForWord(buff, argv[i]);
		printf("The word \"%s\" occurs %d times.\n", argv[i], result);
	}
	fclose(f_in);
	free(buff);

	return 0;
}
