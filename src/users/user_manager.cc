/**
 * @author georgbuechner
 */

#include "user_manager.h"

UserManager::UserManager() {

};

nlohmann::json AddUser(std::string user_name, std::string pw1, 
    std::string pw2) {
  
  if (users_.count(user_name) > 0)
    return nlohmann::json{{"error", "Username already exists."}};
  if (pw1 != pw2)
    return nlohmann::json{{"error", "Passwords's don't match."}};
  if (!CheckpasswodStrength(pw1, pw2))
    return nlohmann::json{{"error", "Strength insufficient."}};

  users_[username] = "";
  return nlohmann::json{{"success", true}};
};
