#ifndef CSSTOKEN_H
#define CSSTOKEN_H
#include <vector>
#include <string>

class CssToken
{
private:

  std::string type;
  std::string text;
public:
  CssToken(std::string type, std::string text);
  
  std::string getType();
  std::string getText();
};

#endif
