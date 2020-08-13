# MY-TINY-RENDERING-ENGINE

## HtmlParser
* using buttom-up, shift-reduce parsing method to build the AST

## CssParser
* parse the stylesheet by rules, using top-down, left-recursive parsing method.
* support nested style rules.

![image](https://github.com/ljxcript/my-tiny-rendering-engine/blob/master/nestedCss.png)

## StyledTree
* apply css rules to build a styled AST

## Layout
* implement the setBoundingClientRect() method and then traverse the styledTree to invoke it for each dom Element.

## Paint
* use opengl to paint rectangles, according to height, width, top and left provided by getBoundingClientRect().
