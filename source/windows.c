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
 
#include <stdbool.h>
#include <reginaldo/paste.h>
#include <reginaldo/windows.h>

/*
  Virtual-Key Codes - MSDN
    http://msdn.microsoft.com/en-us/library/ms927178.aspx
*/
#define  BASE_KEY VK_LSHIFT
#define  SHIFTED  0x8000
#define  F1       112
#define  F12      123
#define  F_DIFF   111

char* getInTheClipboard(void) {
  if(!OpenClipboard(0))
      return NULL;

  char* clipboard = GetClipboardData(CF_TEXT);
  CloseClipboard();

  return clipboard;
}

bool clearClipboard(void) {
  if(!OpenClipboard(0))
      return false;

  bool cleared = EmptyClipboard();
  CloseClipboard();

  return cleared;
}

bool putInTheClipboard(const char* string) {
  const size_t  len  = strlen(string) + 1;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);

  if(hMem == NULL)
    return false;

  memcpy(GlobalLock(hMem), string, len);

  if(!OpenClipboard(0))
      return false;

  EmptyClipboard();
  bool copied = SetClipboardData(CF_TEXT, hMem);
  CloseClipboard();
  
  return copied;
}

t_paste getPasteOnShortcut(int id, char** history) {
  short baseKey = GetKeyState(BASE_KEY);
  short key;
  t_paste paste;

  for(int i = F1; i <= F12; ++i) {
    key = GetKeyState(i);

    if((baseKey & SHIFTED) && (key & SHIFTED)) {
      int fKey       = i  - F_DIFF;
      int selectedId = ((id - 1) - 13);

      if(selectedId < 0)
        selectedId = 0;
      selectedId += fKey;

      if(id - 1 >= selectedId) {
        putInTheClipboard(history[selectedId]);
        paste.id         = selectedId;
        paste.content    = history[selectedId];
      }
      else {
        paste.id         = selectedId;
        paste.content    = NULL;
      }
      break;
    }
  }

  return paste;
}

void sleep(unsigned int interval) {
  Sleep(interval);
}