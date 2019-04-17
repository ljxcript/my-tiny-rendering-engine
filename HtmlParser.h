#ifndef HTMLPARSER_H
#define HTMLPARSER_H
#include <string>
#include "HtmlTagNode.h"
class HtmlParser
{
private:
  std::string htmlText;
  HtmlTagNode* root;
public:
  HtmlParser(const char *filename);

  HtmlTagNode* parse(const char *filename);

  std::string get_file_contents(const char *filename);
  std::string getHtmlText();
  
  void visitByLayer();
};

#endif
