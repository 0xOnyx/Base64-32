

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char base64_map[] =  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};


int return_value_base64(char val)
{

}


char value_from_base64(int val)
{
	return base64_map[val];
}


char *base64_encode(char *data)
{
	char buffer[3];
	char *cipher;

	cipher = (char *)malloc(sizeof(strlen(data) * 4 / 3 + 4 ));
	
	int count_data;
	int count_buffer;
	int count_cipher;

	count_buffer = 0;
	count_cipher = 0;
	count_data   = 0;

	while(data[count_data]!= '\0')
	{
		buffer[count_buffer++] = data[count_data];
		
		if(count_buffer == 3)
		{
			cipher[count_cipher++] = value_from_base64( buffer[0] >> 2 );
			cipher[count_cipher++] = value_from_base64( ((buffer[0] & 0x03) << 4 ) + ( buffer[1] >> 4 ) );
			cipher[count_cipher++] = value_from_base64( ((buffer[1] & 0x0F) << 2 ) + ( buffer[2] >> 6 ) );
			cipher[count_cipher++] = value_from_base64( buffer[2] & 0x3F );
			count_buffer = 0;
		}

		count_data++;
		
	}	

	if(count_buffer > 0)
	{
		cipher[count_cipher++] = value_from_base64( buffer[0] >> 2 );
		
		if(count_buffer == 1)
		{
			cipher[count_cipher++] = value_from_base64( (buffer[0] &0x03 ) << 4 );
			cipher[count_cipher++] = '=';
		}
		
		else
		{
			cipher[count_cipher++] = value_from_base64( ((buffer[0] &0x03) << 4) + (buffer[1] >> 4) );
			cipher[count_cipher++] = value_from_base64( (buffer[1] &0x0F) << 2 );
		}

		cipher[count_cipher++] = '=';
	}
	
	cipher[count_cipher++] = '\0';

	return cipher;
}


char *base64_decrypt(char *cipher)
{
	char *plain;
	char buffer[4];

	int plain_count;
	int count;
	int i;


	plain = (char *)malloc(sizeof(char) * 3 / 4 );

	plain_count = 0;
	count = 0;
	i = 0;

	while(cipher[i] != '\0')
	{
		buffer[count++] = value_from_base54(cipher[i]); 

		if(count == 4)
		{
			plain[plain_count++] = (buffer[0] << 2) + (buffer[1] >> 4);
			
			if( buffer[2])
				plain[plain_count++] = (buffer[1] << 4) + (buffer[2] >> 2 );

			if(buffer[3])
				plain[plain_count++] = (buffer[2] << 6) + buffer[3];

			
			count = 0;
		}
	}
	




}



int main(int argc, char **argv)
{

	char *res;

	res = base64_encode(argv[1]);

	puts(res);

	return 0;
}
