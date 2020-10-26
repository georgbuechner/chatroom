/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_USERS_USER_H
#define CHATROOM_SRC_USERS_USER_H

#include <fstream>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>

#include <nlohmann/json.hpp>

class User {
  public:
    /**
     * @brief Constructs a user
     * @param username
     * @param std::string
     * @param password
     */
    User(std::string username, std::string password);

    std::string username();

    /**
     * @brief Saves user to disc.
     */
    void SafeUser();

  private:
    const std::string username_;
    std::string password_;
    mutable std::shared_mutex shared_mutex_password_;

    /**
     * @brief Constructs user-json
     * @param[in] user (reference to an empty json)
     */
    void ConstructJson(nlohmann::json& user) const;
};

#endif

