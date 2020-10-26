/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_SERVER_H
#define CHATROOM_SRC_SERVER_H

#include <iostream>
#include <mutex>
#include <shared_mutex>

#include <httplib.h>
#include <nlohmann/json.hpp>

#include "user_manager.h"

/**
 * Class holding complete server structure.
 */
class ServerFrame {
  public:
    ServerFrame();

    void Start(int port);

    UserManager& user_manager() { return user_manager_; }
  
    /**
     * @brief Registers the user, if all data is supplied.
     * TODO (georgbuechner): check matching passwords and password strength.
     * @param req
     * @param resp
     */
    void DoRegistration(const httplib::Request& req, httplib::Response& resp);

    /**
     * @brief Gives feedback on whether server is still running
     * @return boolean
     */
    bool IsRunning();

    /**
     * @brief Makes server stop running.
     */
    void Stop();

    /**
     * @brief Destructor, which stops server.
     */
    ~ServerFrame();

  private:
    httplib::Server server_;  //Server
    UserManager user_manager_; //Manages users.
    mutable std::shared_mutex shared_mutex_user_manager_;
};

#endif
