#include <stdio.h>
#include <stdlib.h>
#include <reginaldo.h>
#include <reginaldo/windows.h>
#define  INTERVAL 500

sig_atomic_t raised = 0;

void watchdog(int signum) {
  raised = 1;
}

bool presentInTheClipboard(char** history, int id, const char* string) {
  return string == NULL || strcmp(string, history[id-1]) == 0;
}

int main(void) {
  char** history;
  char*  string;
  int    id = 0;
  int    i;

  signal(SIGINT, watchdog);

  history = (char**) malloc(1 * sizeof(char**));
  history[id++] = "";

  printf("Currently listening...\n");
  clearClipboard();

  while(raised == 0) {
    sleep(INTERVAL);
    string = getClipboard();
    if(presentInTheClipboard(history, id, string))
      continue;

    /*
      printf("%d > ", id + 1);
      scanf("%s", string);

      if(putClipboard(string))
        printf("'%s' copied. ", string);
    */

    history = (char**) realloc(history, (id + 1) * sizeof(char*));
    if(history == NULL) {
      fprintf(stderr, "Memory allocation error.\n");
      exit(EXIT_FAILURE);
    }
    
    history[id] = (char*) malloc( (strlen(string) + 1) * sizeof(char));
    if(history[id] == NULL) {
      fprintf(stderr, "Memory allocation error (2).\n");
      exit(EXIT_FAILURE);
    }

    strcpy(history[id++], string);

    printf("History (#%d): ", id - 1);
    for(i = 1; i < id; i++)
      printf(i + 1 == id ? "'%s'.\n" : "'%s', ",  history[i]);
  }

  printf("Graceful shutdown...\n");
  for(i = 0; i < id; ++i)
    free(history[i]);
  free(history);

  return EXIT_SUCCESS;
}