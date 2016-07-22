#ifndef INCLUDE_MAPLOADER
#define INCLUDE_MAPLOADER

#include <windows.h>
#include <fileOperations.h>

class CMapLoader
{
 public:
  CMapLoader(void);
  ~CMapLoader(void);

  void loadMap(const char *file);
 private:
};
#endif
