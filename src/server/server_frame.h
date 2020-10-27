/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_SERVER_H
#define CHATROOM_SRC_SERVER_H

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <vector>

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
     * @brief Logs in user, if all data is supplied.
     * @param req
     * @param resp
     */
    void DoLogin(const httplib::Request& req, httplib::Response& resp);

    /**
     * @brief Registers the user, if all data is supplied.
     * @param req
     * @param resp
     */
    void DoRegistration(const httplib::Request& req, httplib::Response& resp);

    /**
     * @brief Handles a sent message from user.
     * @param req
     * @param resp
     */
    void Send(const httplib::Request& req, httplib::Response& resp);

    /**
     * @brief Sends all messages to client.
     * @param req
     * @param resp
     */
    void Get(const httplib::Request& req, httplib::Response& resp);



    /**
     * @brief Logout user.
     * @param req
     * @param resp
     */
    void DoLogout(const httplib::Request& req, httplib::Response& resp);

    /**
     * @brief Check whether user is currently logged in.
     * @param resp
     * @return username or empty string (if not logged in)
     */
    std::string CheckLoggedIn(const httplib::Request& resp);

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
    typedef std::pair<std::string, std::string> message;
    std::map<std::string, std::vector<message>> chatrooms_;
    mutable std::shared_mutex shared_mutex_chatroom_;
};

#endif
