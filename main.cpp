#include <iostream>
#include "HtmlParser.h"
#include <regex>

int main(int argc, char const *argv[]) {

  HtmlParser parser(argv[1]);
  std::string html = parser.getHtmlText();
  // for (int i = 0; i < html.size(); i++) {
  //   if (html[i] == ' ') continue;
  //   std::cout << html[i];
  // }
  std::string s = html;
  std::smatch m;
  std::regex e("(<[^<]+\\/?>)|(<\\/\\w+>)");
  while(std::regex_search(s,m,e)) {
    for (auto x:m) std::cout << x << "+";
    std::cout << std::endl;
    s = m.suffix().str();
  }
  return 0;
}
