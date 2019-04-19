//
//  main.cpp
//  cpp
//
//  Created by marco.liao on 2019/4/14.
//  Copyright © 2019年 marco.liao. All rights reserved.
//
#include <iostream>
#include "StyledTree.h"
#include <regex>

#include <unistd.h>


int main(int argc, char const *argv[]) {
    const int MAXPATH=250;
    char buffer[MAXPATH];
    getcwd(buffer, MAXPATH);
    printf("The current directory is: %s", buffer);

    std::cout << std::endl << argv[1] << argv[2] << std::endl;
    StyledTree styledTree(argv[1], argv[2]);
    styledTree.applyStyleRules();
    styledTree.visitByLayer();
    return 0;
}
