//
//  StyledTree.h
//  my-tiny-browser
//
//  Created by marco.liao on 2019/4/18.
//  Copyright © 2019年 marco.liao. All rights reserved.
//

#ifndef STYLEDTREE_H
#define STYLEDTREE_H
#include <vector>
#include <string>
#include "HtmlTagNode.h"
#include "StyledHtmlTagNode.h"
#include "CssRuleNode.h"

class StyledTree
{
private:

    std::vector<CssRuleNode> cssRuleNodeList;
    HtmlTagNode* htmlAST;
    StyledHtmlTagNode* styledRoot;
public:
    StyledTree(const char *cssFile, const char *htmlFile);

    void setStyle(StyledHtmlTagNode* n);
    std::vector<std::string> splitBySharpOrDot(std::string s);
    std::vector<std::string> splitByComma(std::string s);

    void buildTreeFromHtmlAST(StyledHtmlTagNode* styleNode, HtmlTagNode* htmlNode);
    void visitByLayer();
    void applyStyleRule(StyledHtmlTagNode* styleNode, CssASTNode* E);
    void applyStyleRules();
    void findMatchedNodes(StyledHtmlTagNode* entry, std::vector<StyledHtmlTagNode*> &container, std::string selector);
};

#endif
