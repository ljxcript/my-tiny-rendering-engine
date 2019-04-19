//
//  StyledHtmlTagNode.h
//  my-tiny-browser
//
//  Created by marco.liao on 2019/4/18.
//  Copyright © 2019年 marco.liao. All rights reserved.
//

#ifndef STYLEDHTMLTAGNODE_H
#define STYLEDHTMLTAGNODE_H
#include <vector>
#include <string>
#include "HtmlTagNode.h"

class StyledHtmlTagNode
{
private:
    HtmlTagNode* htmlNode;
    std::vector<std::string> style;
    std::vector<StyledHtmlTagNode*> childNodes;
    StyledHtmlTagNode* parentNode;
public:
    StyledHtmlTagNode(StyledHtmlTagNode* parentNode, HtmlTagNode* h);
    void appendChildNode(StyledHtmlTagNode *childNode);
    void visitByLayer(std::vector<StyledHtmlTagNode*> &matchedNodes, std::vector<std::string> &andRules);
    void setStyle(std::string);

    std::vector<StyledHtmlTagNode*> getChildNodes();
    std::string getStyleText();
    std::string getText();
};

#endif
