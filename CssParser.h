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
#include "CssRuleNode.h"
#include "CssToken.h"

class CssParser
{
private:
  std::string cssText;
  std::vector<CssRuleNode> nodeList;
  int nodeLength;
public:
  CssParser(const char *filename);
  std::string get_file_contents(const char *filename);
  std::string getCssText();
  std::vector<CssRuleNode> parse(const char *filename);
  std::vector<CssToken*> tokenize();
  void traverse();
};

#endif
