//
//  StyledHtmlTagNode.cpp
//  my-tiny-browser
//
//  Created by marco.liao on 2019/4/18.
//  Copyright © 2019年 marco.liao. All rights reserved.
//

#include <string>
#include <regex>
#include "StyledHtmlTagNode.h"

StyledHtmlTagNode::StyledHtmlTagNode(StyledHtmlTagNode* p, HtmlTagNode* h)
{
    this->parentNode = p;
    this->htmlNode = h;
}

void StyledHtmlTagNode::appendChildNode(StyledHtmlTagNode *childNode)
{
    childNodes.push_back(childNode);
}

std::string StyledHtmlTagNode::getText()
{
    return this->htmlNode->getText();
}

std::vector <StyledHtmlTagNode*> StyledHtmlTagNode::getChildNodes()
{
    return childNodes;
}

void StyledHtmlTagNode::setStyle(std::string k, std::string v)
{
    this->style[k] = v;
}

std::string StyledHtmlTagNode::getStyleText()
{
    std::string res = "";
    for (std::map<std::string,std::string>::iterator it=this->style.begin(); it!=this->style.end(); ++it) {
        res += it->first;
        res += it->second;
    }
    return res;
}

void StyledHtmlTagNode::visitByLayer(std::vector<StyledHtmlTagNode*> &matchedNodes, std::vector<std::string> &andRules)
{
    StyledHtmlTagNode* node = this;
    std::vector<StyledHtmlTagNode*> container;
    container.push_back(node);

    while (!container.empty()) {

        StyledHtmlTagNode* firstOne = container.front();
        bool isMatched = true;
        for (int i = 0; i < andRules.size(); i++) {
            std::string nodeText = firstOne->getText();
            std::regex classSelect("^\\.\\w[\\w-]*$");
            std::regex idSelect("^\\#\\w[\\w-]*$");
            if (std::regex_match(andRules[i], classSelect)) {
                std::size_t found = nodeText.find("class=\""+andRules[i].substr(1)+"\"");
                if (found == std::string::npos) {
                    isMatched = false;
                }
            } else {
                if (std::regex_match(andRules[i], idSelect)) {
                    std::size_t found = nodeText.find("id=\""+andRules[i].substr(1)+"\"");
                    if (found == std::string::npos) {
                        isMatched = false;
                    }
                } else {
                    if(nodeText.substr(1, andRules[i].length()) != andRules[i]){
                        isMatched = false;
                    }
                }
            }
        }
        if (isMatched) {
            matchedNodes.push_back(firstOne);
        }
        container.erase(container.begin());

        std::vector<StyledHtmlTagNode*> children = firstOne->getChildNodes();
        int childrenNums = (int)children.size();
        for (int i = 0; i < childrenNums; i++) {
            container.push_back(children[i]);
        }

    }
}
