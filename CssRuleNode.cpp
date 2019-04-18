//
//  CssRuleNode.cpp
//  cpp
//
//  Created by marco.liao on 2019/4/14.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
#include "CssRuleNode.h"
#include <iostream>

CssRuleNode::CssRuleNode(std::string ruleText, CssASTNode* root)
{
    this->AST = root;
    this->ruleText = ruleText;
}

std::string CssRuleNode::getRuleText()
{
    return ruleText;
}

CssASTNode* CssRuleNode::getAST()
{
    return this->AST;
}
