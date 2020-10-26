/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_USERS_USER_H
#define CHATROOM_SRC_USERS_USER_H

#include <iostream>
#include <string>

class User {
  public:
    /**
     * @brief Constructs a user
     * @param username
     * @param std::string
     * @param password
     */
    User(std::string username, std::string password) : username_(username) {
      password_ = password;
    }

    std::string username() {
      return username_;
    }

  private:
    const std::string username_;
    std::string password_;
};

#endif

