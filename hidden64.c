

#include <stdio.h>
#include <stdlib.h>



char find_next(char **left , char **right, char sep)
{
	while(**left != sep && **right != '\0')
	{
		printf("left => %c\n", **left);
		printf("left => %c\n", **right);

		*left++;
		*right++;
	}

	while(**right != '=' && **right != '\0')
	{

		*left++;
		*right++;

	}
	printf("return value => %c\n", **right);

	return **right;
}




char *base64_hidden_decrypt(char *cipher, char sep)
{
	char *plain; 

	plain = (char *)malloc(sizeof(char) * 255);


	int i;
	int count;

	char *left;
	char *right;
	char *start;


	count = 8;
	i = 0;

	*left = cipher[0];
	*right = cipher[1];

	char buff;
	

	while(*right != '\0' )
	{

		if(find_next(&left, &right, sep) == '\0' )
			break;
		

			printf("value char left => %c\n", *left );
			printf("value char right => %c\n", *right );
		

		if( right[1] == '=' )
		{
			char tmp;
			count -= 4;

			tmp = left[0] & 0x0F;
			buff = (buff << (8 - count)) | tmp;



		
		}
		else if(right[0] == '=' )
		{
			char tmp;
			count -= 2;
			
			tmp = left[0] & 0x03;
			buff = (buff << (8 - count)) | tmp;
		}


		if(count == 0 )
		{
			plain[i] = buff;
			count = 8;
			i++;

		}

	}

	

	return plain;

}





int main(int argc, char **argv)
{
	char *res;
 	res = base64_hidden_decrypt(argv[2], '\n');
	puts(res);


	return 0;

}
