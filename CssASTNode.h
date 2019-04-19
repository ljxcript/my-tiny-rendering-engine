#ifndef CSSASTNODE_H
#define CSSASTNODE_H
#include <vector>
#include <string>

class CssASTNode
{
private:
    std::vector<CssASTNode*> childNodes;
    std::string text;
    std::string type;
    std::string key;
    std::string value;
    CssASTNode* parentNode;
public:
    CssASTNode(CssASTNode *parentNode);

    void visitByLayer();
    void appendChildNode(CssASTNode *childNode);
    void setText(std::string text);
    void setType(std::string type);
    void setKey(std::string key);
    void setValue(std::string value);


    std::vector<CssASTNode*> getChildNodes();
    std::string getText();
    std::string getType();
    std::string getKey();
    std::string getValue();
};

#endif
