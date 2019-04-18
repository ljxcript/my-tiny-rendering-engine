//
//  CssParser.cpp
//  cp
//
//  Created by marco.liao on 2019/4/14.
//  Copyright © 2019年 marco.liao. All rights reserved.
//  Naturally support nested grammar like
//
#include "CssParser.h"
#include <iostream>
#include <fstream>
#include <regex>
#define TYPE_SELECTOR "TYPE_SELECTOR"
#define TYPE_LEFTBRACKET "TYPE_LEFTBRACKET"
#define TYPE_RIGHTBRACKET "TYPE_RIGHTBRACKET"
#define TYPE_STYLENAME "TYPE_STYLENAME"
#define TYPE_STYLEVALUE "TYPE_STYLEVALUE"

bool CssParser::TYPE_SELECTOR(std::vector<CssGrammarToken> tokenStream, int &i) {
  if (tokenStream[i]->getType() == TYPE_SELECTOR) {
    i++;
    return true;
  }
  return false
}

bool CssParser::TYPE_LEFTBRACKET(std::vector<CssGrammarToken> tokenStream, int &i) {
  if (tokenStream[i]->getType() == TYPE_LEFTBRACKET) {
    i++;
    return true;
  }
  return false
}

bool CssParser::TYPE_RIGHTBRACKET(std::vector<CssGrammarToken> tokenStream, int &i) {
  if (tokenStream[i]->getType() == TYPE_RIGHTBRACKET) {
    i++;
    return true;
  }
  return false
}

bool CssParser::STYLE(std::vector<CssGrammarToken> tokenStream, int &i) {
  if (tokenStream[i]->getType() == TYPE_STYLENAME){
    i++;
    if (tokenStream[i]->getType() == TYPE_STYLEVALUE) {
      i++;
      return true;
    }
    i--;
  }
  return false;
}


ASTNode* CssParser::E (std::vector<CssGrammarToken> tokenStream, int &i, ASTNode* parentNode) {
  int start = i;
  ASTNode* tmpNode = new ASTNode(parentNode);

  bool isMatched = TYPE_SELECTOR(tokenStream, i)
                && TYPE_LEFTBRACKET(tokenStream, i)
                && (E(tokenStream, i) != NULL || STYLE(tokenStream, i))
                && TYPE_RIGHTBRACKET(tokenStream, i);

  if (isMatched) {
    tmpNode->value = tokenStream[start, i];
    if (parentNode != NULL) {
      parentNode->appendChild(tmpNode);
    }
    return tmpNode;
  } else {
    delete tmpNode;
    i = start;
    return NULL;
  }
}

void CssParser::parse () {
    std::vector<CssGrammarToken*> tokenStream = this->tokenize();
    int pointer = 0;
    ASTNode* root = E(tokenStream, pointer, NULL);
    if (ASTNode == NULL) {
      std::cout << "error while parsing, please check the grammar validity" << std::endl;
    }
}

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

std::vector<CssGrammarToken*> CssParser::tokenize()
{
  std::string s = this->getCssText();
  std::vector<CssGrammarToken*> res;
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
      CssGrammarToken* token;
      if (std::regex_match(trimedStr, SELECTOR)) {
        token = new CssGrammarToken(TYPE_SELECTOR, trimedStr);
      }
      if (std::regex_match(trimedStr, LEFTBRACKET)) {
        token = new CssGrammarToken(TYPE_LEFTBRACKET, trimedStr);
      }
      if (std::regex_match(trimedStr, RIGHTBRACKET)) {
        token = new CssGrammarToken(TYPE_RIGHTBRACKET, trimedStr);
      }
      if (std::regex_match(trimedStr, STYLENAME)) {
        token = new CssGrammarToken(TYPE_STYLENAME, trimedStr);
      }
      if (std::regex_match(trimedStr, STYLEVALUE)) {
        token = new CssGrammarToken(TYPE_STYLEVALUE, trimedStr);
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
  std::vector<CssGrammarToken*> tokenStream = this->tokenize();
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
