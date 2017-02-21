#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include <ctype.h>
int frobcmp(char const *a, char const *b){
  for(;; a++, b++) {
      if(*a == 0 && *b == 0) { return 0; }
      else if (*a == 0 || ((*a^42) < (*b^42))) { return -1; }
      else if (*b == 0 || ((*a^42) > (*b^42))) { return 1; }
    }
}

int cmp(const void* in1, const void* in2){
  const char* a = *(const char**)in1;
  const char* b = *(const char**)in2;
  return frobcmp(a,b);
}
int Ufrobcmp(char const *a, char const *b){
  for(;; a++, b++) {
      if(*a == 0 && *b == 0) { return 0; }
      else if (*a == 0 || ((toupper(*a)^42) < (toupper(*b)^42))) { return -1; }
      else if (*b == 0 || ((toupper(*a)^42) > (toupper(*b)^42))) { return 1; }
    }
}

int Ucmp(const void* in1, const void* in2){
  const char* a = *(const char**)in1;
  const char* b = *(const char**)in2;
  return Ufrobcmp(a,b);
}
void err(int a){
  if(a<0){
    fprintf(stderr, "error\n");
    exit(1);
  }}
int main(int argc, int **argv) {
  int fmode=0;
  if (argc > 2) {
    fprintf(stderr, "Argument Error!\n");
    exit(1);
  }
  if (argc == 2 && strlen(argv[1])!=2) {
    fprintf(stderr, "Argument Error!\n");
    exit(1);
  }
  if (argc == 2 && strlen(argv[1])==2) fmode = 1;
  struct stat fileStat;
  if (fstat(0, &fileStat) < 0) {
    fprintf(stderr, "File Error\n");
    exit(1);
  }
  char **wordArray;
  int nOfw = 0;
  char * temp;
  if (S_ISREG(fileStat.st_mode)) {
    int fsize = fileStat.st_size;
    temp = (char*)malloc(fileStat.st_size * sizeof(char));
    int tempWords = 0;
    ssize_t state = read(0, temp, fileStat.st_size);
    if (state > 0) {
      for (int a = 0; a < fsize; a++) {
	if (a == fsize - 1)temp[a] = ' ';
	if (temp[a] == ' ') {
	  tempWords++;
	  int b=a;
	  while (temp[b] == ' '&&b<fsize)b++;
	  a = b - 1;
	}
      }
    }
    wordArray = (char**)malloc(tempWords * sizeof(char*));
    for (int a = 0; a < fsize; a++) {
      if (temp[a] != ' ') {
	int b = a;
	while (temp[b] != ' '){b++;}
	wordArray[nOfw] = (char*)malloc((b - a+1) * sizeof(char));
	for (int c = 0; c < b - a; c++)wordArray[nOfw][c] = temp[c + a];
	wordArray[nOfw++][b - a] = 0;
	a = b;
      }
    }
  }
  else {
  wordArray = (char**)malloc(sizeof(char**));
  }
  char *word=(char*)malloc(sizeof(char));
  char curr[1], next[1];
  int stateC = read(0, curr, 1);
  err(stateC);
  int stateN = read(0, next, 1);
  err(stateN);
  int nLetter = 0;
  while (stateC>0) {
    word[nLetter] = curr[0];
    char *temp =(char*) realloc(word, (nLetter + 2) * sizeof(char));
    if (temp != NULL)word = temp;
    else {
      fprintf(stderr, "Error!\n");
      for (int a = 0; a < nOfw; a++)free(wordArray[a]);
      free(wordArray);
      free(word);
      exit(1);
    }

    if (curr[0] == ' ') {
      word[nLetter] = 0;
      wordArray[nOfw] = word;
      char **tempA = realloc(wordArray, (nOfw + 2) * sizeof(char*));
      if (tempA != NULL) {
	wordArray = tempA;
	nOfw++;
	word = NULL;
	word = (char*)malloc(sizeof(char));
	nLetter = -1;
      }
      else {
	printf(stderr, "Error!\n");
	for (int a = 0; a < nOfw; a++)free(wordArray[a]);
	free(wordArray);
	free(word);
	exit(1);
      }
    }
    if (stateN == 0 && curr[0] == ' '){free(word); break;}
      else if (curr[0] == ' '&&next[0] == ' ') {
	while (curr[0] == ' ') {
	  stateC = read(0, curr, 1);
	  err(stateC);
	}
	stateN = read(0, next, 1);
	err(stateN);
	nLetter++;
	continue;
      }
      else if (stateN == 0) {
	curr[0] = ' ';
	nLetter++;
	continue;
      }
      curr[0] = next[0];
      stateN = read(0, next, 1);
      nLetter++;

  }
  if (fmode)qsort(wordArray, nOfw, sizeof(char*), Ucmp);
  else{ qsort(wordArray, nOfw, sizeof(char*), cmp);}
  for (int a = 0; a < nOfw; a++) {
    if (write(1, wordArray[a], strlen(wordArray[a])) == 0) {
      fprintf(stderr, "Error!\n");
      for (int a = 0; a < nOfw; a++)free(wordArray[a]);
      free(wordArray);
      exit(1);
    }
    write(1, " ", 1);
  }
  for (int a = 0; a < nOfw; a++)free(wordArray[a]);
  free(wordArray);
  free(temp);
  exit(1);
}
