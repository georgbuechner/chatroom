/**
 * @author georgbuechner
 */

#include <iostream>

#include <httplib.h>

#include "func.h"

/**
 * Class holding complete server structure.
 */
class ServerFrame {
  public:
    ServerFrame(int port);
    ~ServerFrame();

  private:
    httplib::Server server_;
};
