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

  users_[username] = username;
  return nlohmann::json{{"success", true}};
};

std::string Username::GetUserByUsername(std::string username) {
  if (users_.count(username) == 0)
    return users_[username];
  return "";
}
    
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
