/**
 * @author georgbuechner
 */

#ifndef CHATROOM_SRC_USERS_USERMANAGER_H
#define CHATROOM_SRC_USERS_USERMANAGER_H

#include <fstream>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <nlohmann/json.hpp>

#include "user.h"

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
    std::shared_ptr<User> GetUserByUsername(std::string username) const;

    /**                                                                                       
     * @brief returns username from cookie.
     * @param[in] ptr (pointer to cookie)                                                
     * @return username or empty string 
     */
    std::string GetUsernameFromCookie(const char* ptr) const;

     /**                                                                                       
      * @brief Generates cookie and maps user to cookie.
      * Creates random 32 characters to generates cookie.
      * @param[in] username (username which is mapped on cookie)                               
      * @return returns cookie as string.                                                      
      */                                                                                       
    std::string GenerateCookie(std::string username);                                         

    /**    
     * @brief checks password strength    
     * Either 15 characters long, or 8 characters + 1 lowercase + 1 digit.    
     * (Github uses a similar approach) 
     * @param password (given password to check)    
     * @return whether strength is sufficient.    
     */    
    bool CheckPasswordStrength(std::string password) const;

  private:
    std::map<std::string, std::shared_ptr<User>> users_;  //Map of users by username.
    mutable std::shared_mutex shared_mutex_users_;  
    std::map<std::string, std::string> cookies_;  //Map of users by cookie.
    mutable std::shared_mutex shared_mutex_cookies_;  
};

#endif

