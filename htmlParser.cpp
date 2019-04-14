#include "HtmlParser.h"

#include <iostream>
#include <fstream>
#include <regex>

HtmlParser::HtmlParser(const char *filename) : root(parse())
{
  this->htmlText = get_file_contents(filename);
}

std::string HtmlParser::get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    in.seekg(0, in.end);
    htmlText.resize(in.tellg());
    in.seekg(0, in.beg);
    in.read(&htmlText[0], htmlText.size());
    in.close();
    return htmlText;
  }
  return "read file error";
}

std::string HtmlParser::getHtmlText()
{
  return this->htmlText;
}

// 解析文本，构造树
HtmlTagNode HtmlParser::parse()
{
  std::string s = this->getHtmlText();
  std::smatch m;
  std::regex e("(<[^<]+\\/?>)|(<\\/\\w+>)");
  while(std::regex_search(s,m,e)) {
    for (auto x:m) std::cout << x << " ";
    std::cout << std::endl;
    s = m.suffix().str();
  }
  HtmlTagNode n(NULL, "<div>");
  return n;
}

// 按层遍历节点
void HtmlParser::visitByLayer()
{
  HtmlTagNode* node = &this->root;
  std::vector<HtmlTagNode*> container;
  container.push_back(node);
  while (!container.empty()) {

    HtmlTagNode* firstOne = container.front();
    std::cout << firstOne->getText() << std::endl;
    container.erase(container.begin());

    std::vector<HtmlTagNode*> children = firstOne->getChildNodes();
    int childrenNums = children.size();
    for (int i = 0; i < childrenNums; i++) {
      container.push_back(children[i]);
    }

  }

}
