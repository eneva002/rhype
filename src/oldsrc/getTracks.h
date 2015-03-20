#ifndef _gettracks_h_
#define _gettracks_h_

#include "Python.h"

int getTracks()
{
  char cName[] = "hyped.py";
  char flags[] = "r";

  Py_Initialize();

  FILE* file = fopen(cName, flags);
  if(file == NULL){
    perror("fopen");
    return 1;
  }

  if(0 != PyRun_SimpleFile(file, cName)) perror("PyRun_SimpleFile");

  Py_Finalize();

  if(0 != fclose(file)) perror("fclose");

  return 0;
}

#endif
