//
//  HtmlTagNode.h
//  my-tiny-browser
//
//  Created by marco.liao on 2019/4/18.
//  Copyright © 2019年 marco.liao. All rights reserved.
//

#ifndef HTMLTAGNODE_H
#define HTMLTAGNODE_H
#include <vector>
#include <string>

class HtmlTagNode
{
private:
    std::vector<HtmlTagNode*> childNodes;
    std::string tagText;
    int height;
    HtmlTagNode* parentNode;
public:
    HtmlTagNode(HtmlTagNode *parentNode, std::string tagText);
    void appendChildNode(HtmlTagNode *childNode);

    std::vector<HtmlTagNode*> getChildNodes();
    std::string getText();
    int getHeight();
};

#endif
