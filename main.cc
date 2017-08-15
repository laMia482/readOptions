#include "read_options.h"

int main(int argc, char **argv)
{
  char *fileName = const_cast<char*>("test.cfg");
  ReadOptions *rp = new ReadOptions(fileName);
  if(!rp->readPermitted())
    delete rp;



  return 0;

}
