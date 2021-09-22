

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char base64_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};


int return_value_base64(char val)
{
	int i;
	i = 0;

	while(i < 64)
	{
		if(base64_map[i] == val)
			return i;
		i++;
	
	}

	return 64;
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
		buffer[count++] = return_value_base64(cipher[i]); 

		if(count == 4)
		{
			plain[plain_count++] = (buffer[0] << 2) + (buffer[1] >> 4);
			
			if( buffer[2] != 64)
				plain[plain_count++] = (buffer[1] << 4) + (buffer[2] >> 2 );

			if( buffer[3] != 64)
				plain[plain_count++] = (buffer[2] << 6) + buffer[3];

			
			count = 0;
		}

		i++;
	}

	plain[plain_count++] = '\0';

	return plain;


}

char* base64_decode(char* cipher) {

    char counts = 0;
    char buffer[4];
    char* plain = malloc(strlen(cipher) * 3 / 4);
    int i = 0, p = 0;

    for(i = 0; cipher[i] != '\0'; i++) {
        char k;
        for(k = 0 ; k < 64 && base64_map[k] != cipher[i]; k++);
        buffer[counts++] = k;
        if(counts == 4) {
            plain[p++] = (buffer[0] << 2) + (buffer[1] >> 4);
            if(buffer[2] != 64)
                plain[p++] = (buffer[1] << 4) + (buffer[2] >> 2);
            if(buffer[3] != 64)
                plain[p++] = (buffer[2] << 6) + buffer[3];
            counts = 0;
        }
    }

    plain[p] = '\0';    /* string padding character */
    return plain;
}

int main(int argc, char **argv)
{

	char *res;

	res = base64_encode(argv[1]);
	
	puts(res);
	
	

	puts(base64_decrypt(res));
	puts(base64_decode(res));

	return 0;
}
