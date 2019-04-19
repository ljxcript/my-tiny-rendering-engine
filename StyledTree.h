#ifndef STYLEDTREE_H
#define STYLEDTREE_H
#include <vector>
#include <string>
#include "HtmlTagNode.h"
#include "StyledHtmlTagNode.h"
class StyledTree
{
private:

  std::vector<CssRuleNode>* cssRuleNodeList;
  HtmlTagNode* htmlAST;
  StyledHtmlTagNode* styledRoot;
public:
  StyledTree(std::string cssFile, std::string htmlFile);
  void applyStyleRules();
  void visitByLayer();
};

#endif
