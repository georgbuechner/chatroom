/**
 * @author georgbuechner
 */

#include "user.h"

User::User(std::string username, std::string password) : username_(username) {
  password_ = password;
}
