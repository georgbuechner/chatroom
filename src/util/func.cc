/**
 * @author georgbuechner
 */

#include "func.h"

namespace func
{
  std::string GetPage(std::string path) {
    //Read loginpage and send
    std::ifstream read(path);
    if (!read) {
      std::cout << "Wrong file passed: " << path << std::endl;
      return "";
    }
    std::string page( (std::istreambuf_iterator<char>(read) ),
                      std::istreambuf_iterator<char>()     );
    //Delete file-end marker
    page.pop_back();
    return page;
  }
}
