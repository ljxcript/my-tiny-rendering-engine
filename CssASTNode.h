#ifndef CSSASTNODE_H
#define CSSASTNODE_H
#include <vector>
#include <string>

class CssASTNode
{
private:
  std::vector<CssASTNode*> childNodes;
  std::string text;
  CssASTNode* parentNode;
public:
  CssASTNode(CssASTNode *parentNode);

  void appendChildNode(CssASTNode *childNode);
  void setText(std::string tagText);

  std::vector<CssASTNode*> getChildNodes();
  std::string getText();
};

#endif
