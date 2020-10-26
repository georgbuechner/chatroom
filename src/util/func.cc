/**
 * @author georgbuechner
 */

#include "func.h"
#include "cleanup_dtor.h"
#include <openssl/evp.h>
#include <openssl/sha.h>

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

  std::string hash_sha3_512(const std::string& input) {
    unsigned int digest_length = SHA512_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha3_512();
    uint8_t* digest = static_cast<uint8_t*>(OPENSSL_malloc(digest_length));
    CleanupDtor dtor([digest](){OPENSSL_free(digest);});


    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, algorithm, nullptr);
    EVP_DigestUpdate(context, input.c_str(), input.size());
    EVP_DigestFinal_ex(context, digest, &digest_length);
    EVP_MD_CTX_destroy(context);

    std::stringstream stream;
    stream<<std::hex;

    for(auto b : std::vector<uint8_t>(digest,digest+digest_length))
      stream << std::setw(2) << std::setfill('0') << (int)b;

    return stream.str();
  }

}
