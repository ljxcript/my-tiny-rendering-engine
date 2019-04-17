#include "CssParser.h"
#include <iostream>
#include <fstream>
#include <regex>
#define TYPE_SELECTOR "TYPE_SELECTOR"
#define TYPE_LEFTBRACKET "TYPE_LEFTBRACKET"
#define TYPE_RIGHTBRACKET "TYPE_RIGHTBRACKET"
#define TYPE_STYLENAME "TYPE_STYLENAME"
#define TYPE_STYLEVALUE "TYPE_STYLEVALUE"
//
//  CssParser.cpp
//  cp
//
//  Created by marco.liao on 2019/4/14.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
CssParser::CssParser(const char *filename) : nodeList(this->parse(filename))
{
  nodeLength = 0;
}

std::string CssParser::get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    in.seekg(0, in.end);
    cssText.resize(in.tellg());
    in.seekg(0, in.beg);
    in.read(&cssText[0], cssText.size());
    in.close();
    return cssText;
  }
  return "read file error";
}

std::string CssParser::getCssText()
{
  return this->cssText;
}

std::vector<CssToken*> CssParser::tokenize()
{
  std::string s = this->getCssText();
  std::vector<CssToken*> res;
  std::smatch m;
  std::regex e("[^\\s\\n\\t]+[\\s\\n\\t]+");
  while(std::regex_search(s,m,e)) {
    for (auto x:m) {
      std::string trimedStr = x.str().erase(x.str().find_last_not_of(" \n\r\t")+1);
      std::regex SELECTOR("^[^\\{\\}:;]+$");
      std::regex LEFTBRACKET("^\\{$");
      std::regex RIGHTBRACKET("^\\}$");
      std::regex STYLENAME("^[a-z][a-z-]+:$");
      std::regex STYLEVALUE("^[a-z-\\s0-9#]+;$"); // do not support calc, rgba() for now
      CssToken* token;
      if (std::regex_match(trimedStr, SELECTOR)) {
        token = new CssToken(TYPE_SELECTOR, trimedStr);
      }
      if (std::regex_match(trimedStr, LEFTBRACKET)) {
        token = new CssToken(TYPE_LEFTBRACKET, trimedStr);
      }
      if (std::regex_match(trimedStr, RIGHTBRACKET)) {
        token = new CssToken(TYPE_RIGHTBRACKET, trimedStr);
      }
      if (std::regex_match(trimedStr, STYLENAME)) {
        token = new CssToken(TYPE_STYLENAME, trimedStr);
      }
      if (std::regex_match(trimedStr, STYLEVALUE)) {
        token = new CssToken(TYPE_STYLEVALUE, trimedStr);
      }
      res.push_back(token);
    }
    s = m.suffix().str();
  }
  return res;
}

std::vector<CssRuleNode> CssParser::parse(const char *filename)
{

  this->cssText = get_file_contents(filename);
  std::vector<CssToken*> tokenStream = this->tokenize();
  for (int i = 0; i < tokenStream.size(); i++) {
    std::cout << tokenStream[i]->getType() << " -> " << tokenStream[i]->getText() << std::endl;
  }
  std::vector<CssRuleNode> nodeList;
  return nodeList;
}

void CssParser::traverse()
{
  for (int i = 0; i < nodeLength; i++) {
    std::cout << nodeList[i].getRuleText() << std::endl;
  }
}
