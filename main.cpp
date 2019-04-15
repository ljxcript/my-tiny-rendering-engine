#include <iostream>
#include "HtmlParser.h"
#include <regex>

int main(int argc, char const *argv[]) {

  HtmlParser parser(argv[1]);
  std::string html = parser.getHtmlText();
  parser.visitByLayer();
  return 0;
}
