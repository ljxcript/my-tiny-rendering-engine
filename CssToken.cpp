//
//  CssToken.cpp
//  cpp
//
//  Created by marco.liao on 2019/4/17.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
#include <iostream>
#include "CssToken.h"

CssToken::CssToken(std::string type, std::string text)
{
  this->type = type;
  this->text = text;
}

std::string CssToken::getText()
{
  return this->text;
}

std::string CssToken::getType()
{
  return this->type;
}
