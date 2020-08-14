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

## Sample Input

```html
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8"/>
    <title></title>
  </head>
  <body>
    <div id="d1" class="layer-1">
      <div id="d1-1" class="layer-2"><h1></h1></div>
      <div id="d1-2" class="layer-2"><h2></h2></div>
    </div>
    <span id="s2" class="layer-1">
      <div id="d2-1" class="layer-2">
        <div id="d2-1-1" class="layer-3">
          <div id="d2" class="layer-4"><h3></h3></div>
        </div>
      </div>
    </span>
    <div id="d3" class="layer-1"></div>
  </body>
</html>
```

```css
div.layer-1 {
    .layer-2 {

        .layer-3 {
            .layer-4 {
                height: 100px;
            }
        }
        background-color: blue;
        padding: 20px;
    }
    background-color: red;
    margin-bottom: 20px;
    padding: 10px;
    width: 500px;
}
h1,h2,h3 {
  margin: auto;
  color: #cc0000;
}
span.layer-1 {
  .layer-2 {
    background-color: blue;
    padding: 20px;
    .layer-3 {
      background-color: yellow;
    }
  }
  background-color: green;
  margin-bottom: 88px;
  padding: 77px;
  width: 433px;
}
#d2 {
  display: none;
}
```

## result
![image](https://github.com/ljxcript/my-tiny-rendering-engine/blob/master/GTScreenshot_20200814_174239.png)
