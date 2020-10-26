/**
 * @author georgbuechner
 */

#include <iostream>
#include <string>

#include "server/server_frame.h"


int main() {
   
  ServerFrame srv;
  srv.Start(4444);
  return 0;
}
