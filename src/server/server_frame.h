/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_SERVER_H
#define CHATROOM_SRC_SERVER_H

#include <iostream>

#include <httplib.h>
#include <nlohmann/json.hpp>

/**
 * Class holding complete server structure.
 */
class ServerFrame {
  public:
    ServerFrame();

    void Start(int port);
  
    /**
     * @brief Registers the user, if all data is supplied.
     * TODO (georgbuechner): check matching passwords and password strength.
     * @param req
     * @param resp
     */
    void DoRegistration(const httplib::Request& req, httplib::Response& resp);

    bool IsRunning();
    void Stop();
    ~ServerFrame();

  private:
    httplib::Server server_;
};

#endif
