#ifndef CSSRULENODE_H
#define CSSRULENODE_H
#include <vector>
#include <string>
#include "CssASTNode.h"

class CssRuleNode
{
private:
    CssASTNode* AST;
    std::string ruleText;
public:
    CssRuleNode( std::string ruleText, CssASTNode* AST);

    CssASTNode* getAST();
    std::string getRuleText();

};

#endif
