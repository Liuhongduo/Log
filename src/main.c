#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recorder.h"
#include "compressor.h"
#include "decompressor.h"
#include "visualization.h"

#define maxn 1024*100
unsigned char addr_in[maxn + 5];
unsigned char addr_out[maxn + 5];
unsigned char de_addr_in[maxn + 5];
unsigned char de_addr_out[maxn + 5];
char s[200] = "A0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz";
char n[200] = "I am from School of Information and Communication Engineering,UESTC";
char l[200] = "C0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz";
void Print(record_node *p)
{
	for (int i = 0; i<4; ++i)
	{
		printf("%d ", p[i].next_offset);
		printf("%d ", p[i].block_offset);
		printf("%d ", p[i].in_use);
		printf("%d\n", p[i].how_many_blocks);
	}
	printf("\n");
}

int main()
{
	FILE *fp = fopen("out.txt", "w");
	record_section(1, 52, addr_in, maxn);
	record(1, 2, 2, 2, 1, s, 18);
	record(1, 2, 2, 2, 2, s, 30, s, 30);
	record(1, 2, 2, 2, 1, s, 70);
	record(1, 2, 2, 2, 3, s, 38, l, 39, n, 40);
	for (int i = 0; i < 198; ++i) {
		record(1, 2, 3, 4, 3, s, 50, n, 50, l, 50);
		record(1, 3, 2, 1, 3, l, 50, n, 50, s, 50);
	}
	record(1, 4, 4, 4, 1, n, 50);
	record(1, 5, 5, 5, 1, s, 100);
	record(1, 3, 3, 3, 1, l, 70);
	record(1, 1, 1, 1, 1, l, 10);
	int len_out;
	compress(addr_in,maxn,addr_out,&len_out);
	printf("length after compress: %d\n",len_out);
	for(int i=0;i<len_out;++i)
		fprintf(fp,"%d\n",addr_out[i]);
	fclose(fp);

	FILE *readfp=fopen("out.txt", "r");
	unsigned char *p = de_addr_in;
	int de_len_out;
	int x;
	int de_len_in = 0;
	while (fscanf(readfp, "%d", &x) != EOF)
	{
		//printf("%d\n",x);
		*p = x;
		p++;
		de_len_in++;
	}
	if (memcmp(addr_out, de_addr_in, de_len_in) == 0)
	{
		printf("YES\n");
	}
	decompress(de_addr_in, de_len_in, de_addr_out, &de_len_out);
	printf("length after decompress:  %d\n", de_len_out);
	if(memcmp(addr_in,de_addr_out,maxn)==0) printf("SUCCESS\n");
	fclose(readfp);
	int tmp=visualization(de_addr_out,maxn);
	return 0;
}
