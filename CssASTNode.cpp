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

std::string CssASTNode::getKey()
{
    return this->key;
}

std::string CssASTNode::getValue()
{
    return this->value;
}


std::string CssASTNode::getType()
{
    return this->type;
}

std::vector <CssASTNode*> CssASTNode::getChildNodes()
{
    return childNodes;
}

void CssASTNode::setText(std::string text)
{
    this->text = text;
}

void CssASTNode::setType(std::string type)
{
    this->type = type;
}

void CssASTNode::setKey(std::string key)
{
    this->key = key;
}

void CssASTNode::setValue(std::string value)
{
    this->value = value;
}


void CssASTNode::visitByLayer()
{

    std::vector<CssASTNode*> container = getChildNodes();
    std::cout << this->getType() <<  std::endl;
    while (!container.empty()) {

        CssASTNode* firstOne = container.front();
        std::cout << firstOne->getType() << " ";
        container.erase(container.begin());

        std::vector<CssASTNode*> children = firstOne->getChildNodes();
        int childrenNums = (int)children.size();
        for (int i = 0; i < childrenNums; i++) {
            container.push_back(children[i]);
        }
        std::cout << std::endl;
    }

}
