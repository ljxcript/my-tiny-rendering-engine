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
#include "CssGrammarToken.h"

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
  std::vector<CssGrammarToken*> tokenize();
  void traverse();

  bool TYPE_SELECTOR(std::vector<CssGrammarToken> tokenStream, int &i);
  bool TYPE_LEFTBRACKET(std::vector<CssGrammarToken> tokenStream, int &i);
  bool TYPE_RIGHTBRACKET(std::vector<CssGrammarToken> tokenStream, int &i);
  bool STYLE(std::vector<CssGrammarToken> tokenStream, int &i);

  ASTNODE* E (std::vector<CssGrammarToken> tokenStream, int &i, ASTNODE* parentNode);
};

#endif
