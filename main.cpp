//
//  main.cpp
//  cpp
//
//  Created by marco.liao on 2019/4/14.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
#include <iostream>
#include "HtmlParser.h"
#include <regex>

int main(int argc, char const *argv[]) {

  HtmlParser parser(argv[1]);
  std::string html = parser.getHtmlText();
  parser.visitByLayer();
  return 0;
}
