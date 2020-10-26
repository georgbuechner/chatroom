/**
 * @author georgbuechner
 */

#include "user_manager.h"

UserManager::UserManager() {

};

nlohmann::json UserManager::AddUser(std::string username, std::string pw1, 
    std::string pw2) {
  
  nlohmann::json response;
  std::shared_lock sl(shared_mutex_users_);
  if (users_.count(username) > 0)
    response = nlohmann::json{{"error", "Username already exists."}};
  else if (pw1 != pw2)
    response = nlohmann::json{{"error", "Passwords don't match."}};
  else if (!CheckPasswordStrength(pw1))
    response = nlohmann::json{{"error", "Strength insufficient."}};
  sl.unlock();
  if (response.count("error") > 0)
    return response;

  std::unique_lock ul(shared_mutex_users_);
  users_[username] = std::shared_ptr<User>(new User(username, pw1));
  std::cout << "Added user to users: " << username << std::endl;
  std::cout << "Users: " << users_.size() << std::endl;
  ul.unlock();
  return nlohmann::json{{"success", true}};
};

std::shared_ptr<User> UserManager::GetUserByUsername(std::string username) {
  if (users_.count(username) == 0)
    return nullptr;
  return users_[username];
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
