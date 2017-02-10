#include<stdio.h>
#include<stdlib.h>
#include <errno.h>
int frobcmp(char const *a, char const *b)
{
  for (;; a++, b++) {
    if (*a == ' ' && *b == ' ') { return 0; }
    else if (*a == ' ' || ((*a ^ 42) < (*b ^ 42))) { return -1; }
    else if (*b == ' ' || ((*a ^ 42) > (*b ^ 42))) { return 1; }
  }
}
int cmp(const void* in1, const void* in2){
  const char* a = *(const char**)in1;
  const char* b = *(const char**)in2;
  return frobcmp(a, b);
}

inline void err() {
  if (ferror(stdin)) {
    fprintf(stderr, "Error: %d\n", errno);
    exit(1);
  }
}
int main(void) {
  char*word;
  char**words;
  int Lcounter = 0;
  int Wcounter = 0;
  word = (char*)malloc(sizeof(char));
  words = (char**)malloc(sizeof(char *));
  char pos = getchar();
  err();
  char next = getchar();
  err();
  while (pos != EOF && !ferror(stdin)) {
    word[Lcounter] = pos;
    char*moreLetters = (char*)realloc(word, (Lcounter + 2) * sizeof(int));
    if (moreLetters != NULL)word = moreLetters;
    else {
      free(word);
      int a1;
      for (a1 = 0; a1 < Wcounter; a1++)
	free (words + a1);
    }
    if (pos == ' ') {
      words[Wcounter] = word;
      char **moreWord = realloc(words, (Wcounter + 2) * sizeof(char*));
      if (moreWord != NULL) {
	words = moreWord;
	Wcounter++;
	word = NULL;
	word = (char*)malloc(sizeof(char));
	Lcounter = -1;
      }
      else {
	int a2;
	for (a2 = 0; a2 < Wcounter; a2++)
	  free(words + a2);
	free(word);
	fprintf(stderr, "Error: %d\n", errno);
	exit(1);
      }
    }
    if (next == EOF&&pos == ' ')break;
    else if (pos == ' '&&next == ' ') {
      while (pos == ' ') {
	pos = getchar();
	err();
      }
      next = getchar();
      err();
      Lcounter++;
      continue;
    }
    else if (next == EOF) {
      pos = ' ';
      Lcounter++;
      continue;
    }
    pos = next;
    next = getchar();
    err();
    Lcounter++;
  }

  qsort(words, Wcounter, sizeof(char*), cmp);

  int a3;
  for (a3 = 0; a3 < Wcounter; a3++) {
    int b1;
    for (b1 = 0; ; b1++) {
      if (putchar(words[a3][b1]) == EOF) {
	fprintf(stderr, "Error: %d", errno);
	exit(1);
      }
      if (words[a3][b1] == ' ')break;
    }
  }
  for (a3 = 0; a3 < Wcounter; a3++)
    free(words[a3]);
  free(words);
  exit(0);
}
