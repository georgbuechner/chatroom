/**
 * @author georgbuechner
 */

#include "user_manager.h"

UserManager::UserManager() {

};

nlohmann::json UserManager::AddUser(std::string username, std::string pw1, 
    std::string pw2) {
  
  if (users_.count(username) > 0)
    return nlohmann::json{{"error", "Username already exists."}};
  if (pw1 != pw2)
    return nlohmann::json{{"error", "Passwords don't match."}};
  if (!CheckPasswordStrength(pw1))
    return nlohmann::json{{"error", "Strength insufficient."}};

  users_[username] = "";
  return nlohmann::json{{"success", true}};
};

/**    
 * @brief checking password strength    
 * Either 15 characters long, or 8 characters + 1 lowercase + 1 digit.    
 * @param password (given password to check)    
 * @return whether strength is sufficient.    
 */    
bool UserManager::CheckPasswordStrength(std::string password) const {    
  if (password.length() >= 15) return true;    
  if (password.length() < 8) return false;    
  bool digit = false, letter = false;    
  for (size_t i=0; i<password.length(); i++) {    
    if (std::isdigit(password[i]) != 0)     
      digit = true;    
    else if (std::islower(password[i]) != 0)     
      letter = true;    
    if (letter == true && digit == true)     
      return true;    
  }    
  return false;    
}
