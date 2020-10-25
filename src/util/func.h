/**
 * @author georgbuechner
 */

#ifndef SRC_SERVER_SRC_FUNC_H
#define SRC_SERVER_SRC_FUNC_H

#include <fstream>
#include <iostream>
#include <string>

namespace func
{
  /**
   * Load a page (html/ css/ javascript) from disc and return as string
   * @param[in] path to file
   * @return complete file as string
   * Load the login
   */
  std::string GetPage(std::string path);
}

#endif
