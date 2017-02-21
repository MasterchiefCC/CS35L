#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, int**argv){
  if(argc!=3){
    fprintf(stderr,"Error\n");
    exit(1);
  }
  char *from =argv[1];
  char *to=argv[2];
  if(strlen(from)!=strlen(to)){
    fprintf(stderr, "Error!\n");
    exit(1);
  }
  for(int a=0; a<strlen(from)-1; a++){
    for(int b=a+1; b<strlen(from); b++)
      if(from[a]==from[b]){
	fprintf(stderr, "Error\n");
	exit(1);
      }
  }
  char cur=getchar();
  while(cur!=EOF){
    for(int a=0; a<strlen(from); a++){
      if(cur==from[a])cur=to[a];
      break;
    }
    putchar(cur);
    cur=getchar();
  }
  return 0;
}
