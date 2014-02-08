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
#include <reginaldo/windows.h>

char* getClipboard(void) {
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

bool putClipboard(const char* string) {
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

void sleep(unsigned int interval) {
  Sleep(interval);
}