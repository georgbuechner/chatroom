/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_USERS_USERMANAGER_H
#define CHATROOM_SRC_USERS_USERMANAGER_H

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <nlohmann/json.hpp>

class UserManager {
  public:
    UserManager();
    
    /**
     * @brief Adds a new user, if passwords and username is sufficient.
     * @param usernname
     * @param pw1
     * @param pw2
     * @return json with error-/ success-code
     */
    nlohmann::json AddUser(std::string username, std::string pw1, 
        std::string pw2);

    /**
     * @brief finds and returns user with given username. 
     * Returns nullptr if user does not exist.
     * @param username
     * @return user or nullptr
     */
    std::string GetUserByUsername(std::string username);

    /**    
     * @brief checks password strength    
     * Either 15 characters long, or 8 characters + 1 lowercase + 1 digit.    
     * @param password (given password to check)    
     * @return whether strength is sufficient.    
     */    
    bool CheckPasswordStrength(std::string password) const;

  private:
    std::map<std::string, std::string> users_;  //Map of users by username.
    mutable std::shared_mutex shared_mutex_users_;  
};

#endif

