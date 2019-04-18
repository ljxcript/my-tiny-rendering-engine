//
//  CssGrammarToken.cpp
//  cpp
//
//  Created by marco.liao on 2019/4/17.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
#include <iostream>
#include "CssGrammarToken.h"

CssGrammarToken::CssGrammarToken(std::string type, std::string text)
{
  this->type = type;
  this->text = text;
}

std::string CssGrammarToken::getText()
{
  return this->text;
}

std::string CssGrammarToken::getType()
{
  return this->type;
}
