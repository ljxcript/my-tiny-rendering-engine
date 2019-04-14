
#include "HtmlTagNode.h"

HtmlTagNode::HtmlTagNode(HtmlTagNode *parentNode, std::string tagText)
{
  this->parentNode = parentNode;
  this->tagText = tagText;
  this->height = parentNode == NULL ? 0 : parentNode->height + 1;
}

void HtmlTagNode::appendChildNode(HtmlTagNode *childNode)
{
  this->childNodes.push_back(childNode);
}

std::string HtmlTagNode::getText()
{
  return this->tagText;
}

std::vector<HtmlTagNode*> HtmlTagNode::getChildNodes()
{
  return this->childNodes;
}
