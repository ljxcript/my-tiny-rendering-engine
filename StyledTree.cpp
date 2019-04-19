//
//  StyledTree.cpp
//  my-tiny-browser
//
//  Created by marco.liao on 2019/4/18.
//  Copyright © 2019年 marco.liao. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <regex>

#include "StyledTree.h"
#include "HtmlParser.h"
#include "CssParser.h"
#include "StyledHtmlTagNode.h"

void StyledTree::buildTreeFromHtmlAST(StyledHtmlTagNode* styleNode, HtmlTagNode* htmlNode) {
    std::vector<HtmlTagNode*> children = htmlNode->getChildNodes();
    if(!children.empty()) {
        for (int i = 0; i < children.size(); i++) {
            StyledHtmlTagNode* tmp = new StyledHtmlTagNode(styleNode, children[i]);
            styleNode->appendChildNode(tmp);
            buildTreeFromHtmlAST(tmp, children[i]);
        }
    }
}

std::vector<std::string> StyledTree::splitByComma(std::string s){
    std::vector<std::string> res;
    int lastCommaIndex = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ',') {
            int interval = i - lastCommaIndex;
            res.push_back(s.substr(lastCommaIndex, interval));
            lastCommaIndex = i + 1;
        }
    }
    res.push_back(s.substr(lastCommaIndex));
    return res;
}

std::vector<std::string> StyledTree::splitBySharpOrDot(std::string s)
{
    std::vector<std::string> res;
    int lastIndex = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.' || s[i] == '#') {
            int interval = i - lastIndex;
            std::string tmp = s.substr(lastIndex, interval);
            if (tmp.length() > 0) {
                res.push_back(tmp);
            }
            lastIndex = i;
        }
    }
    std::string tmps = s.substr(lastIndex);
    if (tmps.length() > 0) {
        res.push_back(tmps);
    }
    return res;
}

void StyledTree::setStyle(StyledHtmlTagNode* n)
{

}

void StyledTree::findMatchedNodes(StyledHtmlTagNode* entry, std::vector<StyledHtmlTagNode*> &container, std::string selector)
{
    std::vector<std::string> parallelSelectors = splitByComma(selector);
    for (int i = 0; i < parallelSelectors.size(); i++) {
        std::vector<std::string> andRules = splitBySharpOrDot(parallelSelectors[i]);
        entry->visitByLayer(container, andRules);
    }

}

void StyledTree::applyStyleRule(StyledHtmlTagNode* styleNode, CssASTNode* E) {
    std::vector<CssASTNode*> cssRuleASTNodes= E->getChildNodes();
    std::string selector = cssRuleASTNodes[0]->getText();
    std::vector<StyledHtmlTagNode*> nodesMatchedBySelector;
    findMatchedNodes(styleNode, nodesMatchedBySelector, selector);
    for (int j = 0; j < cssRuleASTNodes.size(); j++){
        if (cssRuleASTNodes[j]->getType() == "STYLE") {
            for (int k = 0; k < nodesMatchedBySelector.size(); k++) {
                nodesMatchedBySelector[k]->setStyle(cssRuleASTNodes[j]->getText());
            }
        }
        if (cssRuleASTNodes[j]->getType() == "E") {
            for (int k = 0; k < nodesMatchedBySelector.size(); k++) {
                applyStyleRule(nodesMatchedBySelector[k], cssRuleASTNodes[j]);
            }
        }
    }

}

void StyledTree::applyStyleRules()
{
    for (int i = 0; i < this->cssRuleNodeList.size(); i++) {
        applyStyleRule(this->styledRoot, this->cssRuleNodeList[i].getAST());
    }
}


StyledTree::StyledTree(const char *cssFile, const char *htmlFile)
{
    CssParser cssparser(cssFile);
    HtmlParser htmlparser(htmlFile);
    this->htmlAST = htmlparser.getRoot();
    this->cssRuleNodeList = cssparser.getNodeList();
    this->styledRoot = new StyledHtmlTagNode(NULL, this->htmlAST);
    buildTreeFromHtmlAST(this->styledRoot, this->htmlAST);
}


void StyledTree::visitByLayer()
{
    StyledHtmlTagNode* node = this->styledRoot;
    if (node == NULL) return;
    std::vector<StyledHtmlTagNode*> container;
    container.push_back(node);

    while (!container.empty()) {

        StyledHtmlTagNode* firstOne = container.front();
        std::cout << firstOne->getText() << " " << firstOne->getStyleText() << std::endl;
        container.erase(container.begin());

        std::vector<StyledHtmlTagNode*> children = firstOne->getChildNodes();
        int childrenNums = (int)children.size();
        for (int i = 0; i < childrenNums; i++) {
            container.push_back(children[i]);
        }

    }
}
