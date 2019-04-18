//
//  CssASTNode.cpp
//  cpp
//
//  Created by marco.liao on 2019/4/18.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
#include "CssASTNode.h"
#include <iostream>

CssASTNode::CssASTNode(CssASTNode *parentNode)
{
  this->parentNode = parentNode;
}

void CssASTNode::appendChildNode(CssASTNode *childNode)
{
  childNodes.push_back(childNode);
}

std::string CssASTNode::getText()
{
  return this->text;
}

std::vector <CssASTNode*> CssASTNode::getChildNodes()
{
  return childNodes;
}

void CssASTNode::setText(std::string text)
{
  this->text = text;
}
