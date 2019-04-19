#ifndef CSSGRAMMARTOKEN_H
#define CSSGRAMMARTOKEN_H
#include <vector>
#include <string>

class CssGrammarToken
{
private:

    std::string type;
    std::string text;
public:
    CssGrammarToken(std::string type, std::string text);

    std::string getType();
    std::string getText();
};

#endif
