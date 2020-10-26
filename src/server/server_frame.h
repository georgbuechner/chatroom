/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_SERVER_H
#define CHATROOM_SRC_SERVER_H

#include <iostream>

#include <httplib.h>

/**
 * Class holding complete server structure.
 */
class ServerFrame {
  public:
    ServerFrame();
    ~ServerFrame();

    void Start(int port);
    void Stop();
    bool IsRunning();

  private:
    httplib::Server server_;
};

#endif
