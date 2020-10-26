/**
 * @author georgbuechner
 */

#include "user_manager.h"
#include "func.h"
namespace fs = std::filesystem;

UserManager::UserManager() {
  for (auto& p : fs::directory_iterator("../data/users")) {
    //Load user json from disc and try getting username and password.
    std::ifstream read(p.path());
    std::string username, password;
    try {
      nlohmann::json user;
      read >> user;
      username = user["username"];
      password = user["password"];
    }
    catch(std::exception& e) {
      std::cout << "Problem reading data from user: " << p.path() << std::endl;
      continue;
    }

    //Create user and add to map of users.
    users_[username] = std::shared_ptr<User>(new User(username, password));
  }

  std::cout << "All users:" << std::endl;
  for (auto it : users_)
    std::cout << it.first << std::endl;
};

bool UserManager::DoLogin(std::string username, std::string password) const {
  //Check whether user exists
  if (users_.count(username) == 0)
    return false;

  //Check whether passwords match (has password).
  password = func::hash_sha3_512(password);
  if (password != users_.at(username).get()->password())
    return false;
  return true;
}

nlohmann::json UserManager::AddUser(std::string username, std::string pw1, 
    std::string pw2) {
  nlohmann::json response; 

  //Check if user-input matches requirements.
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

  //Add new user (hash password) to map and return success code.
  std::unique_lock ul(shared_mutex_users_);
  users_[username] = std::shared_ptr<User>(new User(username, 
        func::hash_sha3_512(pw1)));
  try {
    std::cout << "Saving user: " << username << std::endl;
    users_[username].get()->SafeUser();
  }
  catch (std::exception& e) {
    std::cout << "Saving user failed: " << e.what() << std::endl;
  }
  ul.unlock();
  return nlohmann::json{{"success", true}};
}

std::shared_ptr<User> UserManager::GetUserByUsername(std::string username) 
    const {
  //Check if user exists, if so, return shared pointer to user.
  if (users_.count(username) == 0)
    return nullptr;
  return users_.at(username);
}


std::string UserManager::GetUsernameFromCookie(const char* ptr) const {
  //check if cookie exists.
  if (!ptr)
    return "";

  //Parse user-cookie from cookie and check if this user exists
  std::string cookie = ptr;
  cookie = cookie.substr(cookie.find("SESSID=")+7);
  std::shared_lock sl(shared_mutex_cookies_);
  if (cookies_.count(cookie) == 0)
    return "";
  return cookies_.at(cookie);
}
                                                                                            
std::string UserManager::GenerateCookie(std::string username) {
  //Collect 32 random bytes in Linux provided by /dev/urandom                                     
  std::ifstream ifs("/dev/urandom", std::ios::in|std::ios::binary);
  if (!ifs)                                                                                       
    std::cout << "Could not generate session id!" << std::endl;                                   
  char buffer[33];                                                                                
  ifs.read(buffer,32);                                                                            
  ifs.close();                                                                                    
                                                                                                  
  //Assign each character in the buffer a random char based on the byte                           
  //read from the random device                
  static const char alphanum[] =                                    
    "0123456789""ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz""_";   
  std::string sessid = "";
  for (int i = 0; i< 32; ++i)                           
    sessid += alphanum[buffer[i] % (sizeof(alphanum)-1)];
           
  std::unique_lock ul(shared_mutex_cookies_);
  cookies_[sessid] = username;                                     
  return sessid;
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
