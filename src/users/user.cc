/**
 * @author georgbuechner
 */

#include "user.h"

User::User(std::string username, std::string password) : username_(username) {
  password_ = password;
}

std::string User::username() {
  return username_;
}

void User::SafeUser() {
  //Construct json with user data.
  nlohmann::json user;
  ConstructJson(user);

  //Write json to disc.
  std::ofstream write("../../data/users/" + username_ + ".json");
  try {
    write << user;
  }
  catch (std::exception& e) {
    std::cout << "Writing user data failed." << std::endl;
  }
  write.close();
}

void User::ConstructJson(nlohmann::json& user) const {
  user["username"] = username_;
  std::shared_lock sl(shared_mutex_password_);
  user["password"] = password_;
}
