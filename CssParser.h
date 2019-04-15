//
//  CssParser.h
//  cpp
//
//  Created by marco.liao on 2019/4/14.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
//
#ifndef CSSPARSER_H
#define CSSPARSER_H
#include <string>
#include "HtmlTagNode.h"
class HtmlParser
{
private:
  std::string htmlText;
  HtmlTagNode* root;
public:
  HtmlParser(const char *filename);
  std::string get_file_contents(const char *filename);
  std::string getHtmlText();
  HtmlTagNode* parse(const char *filename);
  void visitByLayer();
};

#endif
