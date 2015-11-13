#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY "SVIm6KnbQFiI4xHXaGYUvF55bryrgEbIiggOpLEjLBs="

char *xor_encode(const char *strings, int len)
{
	char *key = KEY;
	int key_len = strlen(KEY);	
	int i = 0;
	char *data = NULL;

	if (strings == NULL) {
		return NULL;
	}

	data = malloc(len + 1);
	if (data == NULL) {
		fprintf(stderr, "%s: failed to allocate memory\n", __func__);
		return NULL;
	}
	memset(data, '\0', len + 1);
	memcpy(data, strings, len);
	
	if (len <= key_len) {
		for (i = 0; i< len; i++) {
			data[i] = data[i] ^ key[i];
		}
	} else {
		int j = len / key_len;
		int k = len % key_len;
		int v = 0;
		int z = 0;
		for (i = 0; i < j; i++) {
			v = i * key_len;
			for (z = 0 ; z < key_len; z++) {
				data[v+z] = data[v+z] ^ key[z];
			}
		}
		v = j * key_len;
		for (z = 0; z < k; z++) {
			data[v+z] = data[v+z] ^ key[z];
		}
	}

	return data;
}

char *xor_decode(const char *data, int len)
{
	return xor_encode(data, len);
}

int encode(void)
{
	char data[1024];
	char *encode = NULL;
	int len = 0;
	int i = 0;

	printf("input string to encode：\n");
	scanf("%1023s", data);
	len = strlen(data);

	encode = xor_encode(data, len);	
	if (encode == NULL) {
		printf("error: encode fail\n");
		return -1;
	}

	printf("encode value:\n");
	for (i = 0; i < len; i++)
		printf("%c", encode[i]);
	printf("\n");
	free(encode);

	return 0;
}

int decode(void)
{
	char data[1024];
	char *decode = NULL;
	int len = 0;
	int i = 0;

	printf("input string to encode：\n");
	scanf("%1023s", data);
	len = strlen(data);

	decode = xor_decode(data, len);	
	if (decode == NULL) {
		printf("error: decode fail\n");
		return -1;
	}

	printf("decode value:\n");
	for (i = 0; i < len; i++)
		printf("%c", decode[i]);
	printf("\n");
	free(decode);

	return 0;
}

void usage(char *self)
{
	printf("Usage:\n");
	printf("\t%s --encode            # encode strings which you input\n", self);
	printf("\t%s --decode            # decode strings which you input\n", self);
	printf("\t%s --help or -h        # show this help infomation\n", self);
}

int main(int argc, char **argv)
{
	if (argc == 2) {
		if (strcmp(argv[1], "--encode") == 0) {
			encode();
		} else if (strcmp(argv[1], "--decode") == 0) {
			decode();
		} else {
			usage(argv[0]);
		}
	} else {
		usage(argv[0]);
	}

	return 0;
}
