/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_USERS_USERMANAGER_H
#define CHATROOM_SRC_USERS_USERMANAGER_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

class UserManager {
  public:
    UserManager() {};
    
    nlohmann::json AddUser(std::string user_name, std::string pw1, 
        std::string pw2) {
      return nlohmann::json{};
    };
};

#endif;

