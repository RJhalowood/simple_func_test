#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	char buffer[] = ",,,zhang femal 23, ming femal 24, hui femal 25,,,";
	char *buf = buffer;
	char *our_ptr = NULL;
	char *inner_ptr = NULL;
	char *temp = NULL;
	char *result[20];
	int i = 0;
	int j = 0;
	
	while ((temp = strtok_r(buf, ",", &our_ptr)) != NULL) {
		
		buf = temp;
		while ((result[i] = strtok_r(buf, " ", &inner_ptr)) != NULL) {
			i++;
			buf = NULL;
		}
		buf = NULL;
	}
	
	for (; j < i; j++) {
		printf("%s\n", result[j]);
	}
	
	i = 011;
	printf("i = 0x%x\n", i);
	return 0;
}