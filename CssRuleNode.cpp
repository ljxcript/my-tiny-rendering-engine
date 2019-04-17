//
//  CssRuleNode.cpp
//  cpp
//
//  Created by marco.liao on 2019/4/14.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
#include "CssRuleNode.h"
#include <iostream>

CssRuleNode::CssRuleNode(int id, std::string ruleText)
{
  this->id = id;
  this->ruleText = ruleText;
}

std::string CssRuleNode::getRuleText()
{
  return ruleText;
}

std::vector<CssRuleNode*> CssRuleNode::getChildNodes()
{
  return childNodes;
}

int CssRuleNode::getId()
{
  return id;
}
