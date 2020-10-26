/**
 * @author georgbuechner
 */

#ifndef SRC_SERVER_SRC_FUNC_H
#define SRC_SERVER_SRC_FUNC_H

#include <codecvt>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <string.h>
#include <time.h>

namespace func
{
  /**
   * Load a page (html/ css/ javascript) from disc and return as string
   * @param[in] path to file
   * @return complete file as string
   * Load the login
   */
  std::string GetPage(std::string path);

  /**
   * @brief Implements a cryptographic hash function, uses the slower but better
   * SHA3 algorithm also named Keccak
   * @param input The string to hash, for example password email whatever.
   * @return The hashed string is returned, the input remains unchanged
   */
  std::string hash_sha3_512(const std::string& input);
}

#endif
