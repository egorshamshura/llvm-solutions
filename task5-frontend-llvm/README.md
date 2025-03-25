# llvm-course task 5 solution

## Grammar of SimpleLang
```
Keywords: [func, ->, int, return, {, }, (, ), var];

Function declaration:
---------------------
func name(args...) -> int {
  funcBody;
  return x;
}

While expression:
-----------------
while (id1 < id2) {
  funcBody;
}

Variable declaration (should be in the beginning of function):
------------------------------------------------------------
var id = expression;

Expression:
-----------
expr +-*/ expr
-expr
id
int
id(args...) // function call
```

## Test programm:
```
func square(x) -> int {
	var result = x * x;
	return result;
}

func id(x) -> int {
	return x;
}

func app() -> int {
	var step = 0;
	var endStep = 1000;
	var y = 0;
	var endY = 256;
	var x = 0;
	var endX = 512;
	var colour = x * y * step;
	while (step < endStep) {
		y = 0;
		while (y < endY) {
			x = 0;
			endX = 512;
			while (x < endX) {
				colour = x * y * step;
				put_pixel(x y colour);
				x = x + 1;
			}
			y = y + 1;
		}
		flush();
		step = step + 1;
	}
	var res = 0;
	return res;
}
```

## Examples
![](https://github.com/egorshamshura/llvm-solutions/blob/main/assets/llvm-example-2.gif)