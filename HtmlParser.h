//
//  HtmlParser.h
//  my-tiny-browser
//
//  Created by marco.liao on 2019/4/18.
//  Copyright © 2019年 marco.liao. All rights reserved.
//

#ifndef HTMLPARSER_H
#define HTMLPARSER_H
#include <string>
#include "HtmlTagNode.h"
class HtmlParser
{
private:
    std::string htmlText;
    HtmlTagNode* root;
public:
    HtmlParser(const char *filename);

    HtmlTagNode* parse(const char *filename);

    std::string get_file_contents(const char *filename);
    std::string getHtmlText();
    HtmlTagNode* getRoot();

    void visitByLayer();
};

#endif
