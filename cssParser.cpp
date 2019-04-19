//
//  CssParser.cpp
//  cp
//
//  Created by marco.liao on 2019/4/14.
//  Copyright © 2019年 marco.liao. All rights reserved.
//  Naturally support nested grammar like
//
#include "CssParser.h"
#include <iostream>
#include <fstream>
#include <regex>
#define TYPE_SELECTOR "TYPE_SELECTOR"
#define TYPE_LEFTBRACKET "TYPE_LEFTBRACKET"
#define TYPE_RIGHTBRACKET "TYPE_RIGHTBRACKET"
#define TYPE_STYLENAME "TYPE_STYLENAME"
#define TYPE_STYLEVALUE "TYPE_STYLEVALUE"

bool CssParser::match_TYPE_SELECTOR(const std::vector<CssGrammarToken*> &tokenStream, int &i, CssASTNode* parentNode) {
    if (tokenStream[i]->getType() == TYPE_SELECTOR) {

        CssASTNode* tmpNode = new CssASTNode(parentNode);
        tmpNode->setType(TYPE_SELECTOR);
        tmpNode->setText(tokenStream[i]->getText());

        i++;
        if (parentNode != NULL) {
            parentNode->appendChildNode(tmpNode);
        }
        return true;
    }
    return false;
}

bool CssParser::match_TYPE_LEFTBRACKET(const std::vector<CssGrammarToken*> &tokenStream, int &i, CssASTNode* parentNode) {
    if (tokenStream[i]->getType() == TYPE_LEFTBRACKET) {

        CssASTNode* tmpNode = new CssASTNode(parentNode);
        tmpNode->setType(TYPE_LEFTBRACKET);
        tmpNode->setText(tokenStream[i]->getText());

        i++;
        if (parentNode != NULL) {
            parentNode->appendChildNode(tmpNode);
        }
        return true;
    }
    return false;
}

bool CssParser::match_TYPE_RIGHTBRACKET(const std::vector<CssGrammarToken*> &tokenStream, int &i, CssASTNode* parentNode) {
    if (tokenStream[i]->getType() == TYPE_RIGHTBRACKET) {

        CssASTNode* tmpNode = new CssASTNode(parentNode);
        tmpNode->setType(TYPE_RIGHTBRACKET);
        tmpNode->setText(tokenStream[i]->getText());

        i++;
        if (parentNode != NULL) {
            parentNode->appendChildNode(tmpNode);
        }
        return true;
    }
    return false;
}

bool CssParser::match_STYLE(const std::vector<CssGrammarToken*> &tokenStream, int &i, CssASTNode* parentNode) {
    while(tokenStream[i]->getType() == TYPE_STYLENAME || tokenStream[i]->getType() == TYPE_STYLEVALUE) {
        if (tokenStream[i]->getType() == TYPE_STYLENAME){

            CssASTNode* tmpNode = new CssASTNode(parentNode);
            tmpNode->setType("STYLE");
            tmpNode->setText(tokenStream[i]->getText());

            i++;
            if (tokenStream[i]->getType() == TYPE_STYLEVALUE) {

                tmpNode->setText(tmpNode->getText() + tokenStream[i]->getText());

                i++;
                if (parentNode != NULL) {
                    parentNode->appendChildNode(tmpNode);
                }
            } else {
                i--;
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

CssASTNode* CssParser::E (const std::vector<CssGrammarToken*> &tokenStream, int &i, CssASTNode* parentNode) {
    int start = i;
    CssASTNode* tmpNode = new CssASTNode(parentNode);

    bool isMatched = match_TYPE_SELECTOR(tokenStream, i, tmpNode)
    && match_TYPE_LEFTBRACKET(tokenStream, i, tmpNode)
    && (
        (E(tokenStream, i, tmpNode) != NULL && match_STYLE(tokenStream, i, tmpNode))
        ||
        (match_STYLE(tokenStream, i, tmpNode) && E(tokenStream, i, tmpNode) != NULL)
        ||
        (match_STYLE(tokenStream, i, tmpNode))
        )
    && match_TYPE_RIGHTBRACKET(tokenStream, i, tmpNode);

    if (isMatched) {
        std::string t = "";
        for (int j = start; j < i; j++) {
            t += tokenStream[j]->getText();
        }
        tmpNode->setType("E");
        tmpNode->setText(t);
        if (parentNode != NULL) {
            parentNode->appendChildNode(tmpNode);
        }
        return tmpNode;
    } else {
        delete tmpNode;
        i = start;
        return NULL;
    }
}

std::vector<CssRuleNode> CssParser::getNodeList()
{
    return this->nodeList;
}

std::vector<CssRuleNode> CssParser::parse(const char *filename)
{

    this->cssText = get_file_contents(filename);
    std::cout << this->cssText << std::endl;
    std::vector<CssGrammarToken*> tokenStream = this->tokenize();

    int pointer = 0;
    std::vector<CssRuleNode> nodeList;
    while(pointer < tokenStream.size()) {
        CssASTNode* root = E(tokenStream, pointer, NULL);
        if (root == NULL) {
            std::cout << "error while parsing, please check the grammar validity" << std::endl;
        }
//        root->visitByLayer();
        nodeList.push_back(CssRuleNode(root->getText(), root));
    }

    return nodeList;
}


CssParser::CssParser(const char *filename) : nodeList(this->parse(filename))
{
    this->nodeLength = (int)this->nodeList.size();
    std::cout << nodeLength << " rules found" << std::endl;
}

std::string CssParser::get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in) {
        in.seekg(0, in.end);
        cssText.resize(in.tellg());
        in.seekg(0, in.beg);
        in.read(&cssText[0], cssText.size());
        in.close();
        return cssText;
    }
    return "read file error";
}

std::string CssParser::getCssText()
{
    return this->cssText;
}

std::vector<CssGrammarToken*> CssParser::tokenize()
{
    std::string s = this->getCssText();
    std::vector<CssGrammarToken*> res;
    std::smatch m;
    std::regex e("[^\\s\\n\\t]+[\\s\\n\\t]+");
    while(std::regex_search(s,m,e)) {
        for (auto x:m) {
            std::string trimedStr = x.str().erase(x.str().find_last_not_of(" \n\r\t")+1);
            std::regex SELECTOR("^[^\\{\\}:;]+$");
            std::regex LEFTBRACKET("^\\{$");
            std::regex RIGHTBRACKET("^\\}$");
            std::regex STYLENAME("^[a-z][a-z-]+:$");
            std::regex STYLEVALUE("^[a-z-\\s0-9#]+;$"); // do not support calc, rgba() for now
            CssGrammarToken* token = NULL;
            if (std::regex_match(trimedStr, SELECTOR)) {
                token = new CssGrammarToken(TYPE_SELECTOR, trimedStr);
            }
            if (std::regex_match(trimedStr, LEFTBRACKET)) {
                token = new CssGrammarToken(TYPE_LEFTBRACKET, trimedStr);
            }
            if (std::regex_match(trimedStr, RIGHTBRACKET)) {
                token = new CssGrammarToken(TYPE_RIGHTBRACKET, trimedStr);
            }
            if (std::regex_match(trimedStr, STYLENAME)) {
                token = new CssGrammarToken(TYPE_STYLENAME, trimedStr);
            }
            if (std::regex_match(trimedStr, STYLEVALUE)) {
                token = new CssGrammarToken(TYPE_STYLEVALUE, trimedStr);
            }
            if (token == NULL) {
                std::cout << "error while tokenizing: " << trimedStr << ", missing ; or : " << std::endl;
                return res;
            }
            res.push_back(token);
        }
        s = m.suffix().str();
    }
    return res;
}


void CssParser::traverse()
{
    for (int i = 0; i < nodeLength; i++) {
        std::cout << nodeList[i].getRuleText() << std::endl;
    }
}
