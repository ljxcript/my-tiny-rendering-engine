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
#include "CssASTNode.h"

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

  bool match_TYPE_SELECTOR(const std::vector<CssGrammarToken*> &tokenStream, int &i);
  bool match_TYPE_LEFTBRACKET(const std::vector<CssGrammarToken*> &tokenStream, int &i);
  bool match_TYPE_RIGHTBRACKET(const std::vector<CssGrammarToken*> &tokenStream, int &i);
  bool match_STYLE(const std::vector<CssGrammarToken*> &tokenStream, int &i);

  CssASTNode* E (const std::vector<CssGrammarToken*> &tokenStream, int &i, CssASTNode* parentNode);
};

#endif
