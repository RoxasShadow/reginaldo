/**
 * Copyright (C) 2014 Giovanni Capuano <webmaster@giovannicapuano.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <reginaldo.h>
#include <reginaldo/config.h>
#include <reginaldo/paste.h>
#include <reginaldo/windows.h>

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

  signal(SIGINT, watchdog);

  history = (char**) malloc(1 * sizeof(char**));
  history[id++] = "";

  printf("Currently listening...\n");
  clearClipboard();

  while(raised == 0) {
    t_paste paste = getPasteOnShortcut(id, history);
    if(!&paste) {
      if(paste.content == NULL)
        printf("Paste #%d has been copied in the clipboard!\n", paste.id);
      else
        printf("Paste #%d doesn't exist.\n",                    paste.id);
    }

    sleep(INTERVAL);
    string = getInTheClipboard();
    if(presentInTheClipboard(history, id, string))
      continue;

    /*
      printf("%d > ", id + 1);
      scanf("%s", string);

      if(putInTheClipboard(string))
        printf("'%s' copied. ", string);
    */

    history = (char**) realloc(history, (id + 1) * sizeof(char*));
    if(history == NULL) {
      fprintf(stderr, "Memory allocation error.\n");
      exit(EXIT_FAILURE);
    }
    
    history[id] = (char*) malloc( (strlen(string) + 1) * sizeof(char));
    if(history[id] == NULL) {
      fprintf(stderr, "Memory allocation error.\n");
      exit(EXIT_FAILURE);
    }

    strcpy(history[id++], string);

    printf("History (#%d): ", id - 1);
    for(int i = 1; i < id; i++)
      printf(i + 1 == id ? "'%s'.\n" : "'%s', ",  history[i]);
  }

  printf("Graceful shutdown...\n");
  for(int i = 0; i < id; ++i)
    free(history[i]);
  free(history);

  return EXIT_SUCCESS;
}