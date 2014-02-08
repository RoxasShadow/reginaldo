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