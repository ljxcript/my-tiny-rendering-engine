#ifndef CSSRULENODE_H
#define CSSRULENODE_H
#include <vector>
#include <string>

class CssRuleNode
{
private:
  std::vector<CssRuleNode*> childNodes;
  std::string ruleText;
  int id;
public:
  CssRuleNode(int id, std::string ruleText);

  std::vector<CssRuleNode*> getChildNodes();
  std::string getRuleText();
  int getId();
};

#endif
