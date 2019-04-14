#include <iostream>
#include <string>
#include <fstream>


class HtmlParser
{
  public:
    std::string get_file_contents(const char *filename)
    {
      std::ifstream in(filename, std::ios::in | std::ios::binary);
      if (in) {
        in.seekg(0, in.end);
        htmlText.resize(in.tellg());
        in.seekg(0, in.beg);
        in.read(&htmlText[0], htmlText.size());
        in.close();
        return htmlText;
      }
      return "read file error";
    }
    std::string getHtmlText()
    {
      return htmlText;
    }
  private:
    std::string htmlText;
};



int main(int argc, char const *argv[]) {

  HtmlParser parser;
  std::string html = parser.get_file_contents(argv[1]);
  for (int i = 0; i < html.size(); i++) {
    if (html[i] == ' ') continue;
    std::cout << html[i];
  }
  return 0;
}
