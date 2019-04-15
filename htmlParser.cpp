#include "HtmlParser.h"
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <regex>

HtmlParser::HtmlParser(const char *filename) : root(this->parse(filename))
{

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
HtmlTagNode* HtmlParser::parse(const char *filename)
{
  this->htmlText = get_file_contents(filename);
  std::string s = this->getHtmlText();
  std::smatch m;
  std::regex e("<[^<\\/]+\\/?>|<\\/\\w+>");

  std::vector<HtmlTagNode* > stack;
  HtmlTagNode* root;
  while(std::regex_search(s,m,e)) {
    for (auto x:m) {

      // 匹配opening tag
      std::regex matchOpeningTagRgx("<[^<\\/]+>");
      if (std::regex_match(x.str(), matchOpeningTagRgx)) {
        if (stack.empty()) {
          root = new HtmlTagNode(NULL, x.str());
          stack.push_back(root);
        } else {
          HtmlTagNode* n = new HtmlTagNode(stack[stack.size()-1], x.str());
          stack[stack.size()-1]->appendChildNode(n);
          stack.push_back(n);
        }
      }

      // 匹配closing tag
      std::regex matchClosingTagRgx("<\\/\\w+>");
      if (std::regex_match(x.str(), matchClosingTagRgx)) {
        if (stack.empty()) {
          std::cout << "parsing error: " << x.str() << " did not match." << std::endl;
          return NULL;
        }
        HtmlTagNode* lastN = stack.back();
        stack.pop_back();
        std::string transformedClosingTag = std::regex_replace(lastN->getText(), std::regex("<(\\w+)\\s?[\\w\\W]*>"), "</$1>");
        if (transformedClosingTag != x.str()) {
          std::cout << "parsing error: " << lastN->getText() << " , no matched closing tag." << std::endl;
          return NULL;
        }
      }

      // 匹配形如<div/>自关闭标签
      std::regex matchSelfClosingTagRgx("<[^<\\/]+\\/>");
      if (std::regex_match(x.str(), matchSelfClosingTagRgx)) {
        HtmlTagNode* n = new HtmlTagNode(stack[stack.size()-1], x.str());
        stack[stack.size()-1]->appendChildNode(n);
      }
    }
    s = m.suffix().str();
  }
  if (!stack.empty()) {
    std::cout << "parsing error: " << stack.back()->getText() << " did not match." << std::endl;
    return NULL;
  }
  return root;
}

// 按层遍历节点
void HtmlParser::visitByLayer()
{
  HtmlTagNode* node = this->root;
  if (node == NULL) return;
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
