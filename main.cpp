#include <iostream>
#include "parser.hpp"
int main(int argc, char * argv[])
{
  Driver driver(argc, argv); //
  driver.Parse();
  return 0;
}
