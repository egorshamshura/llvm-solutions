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

## Memory management
Every variable that is declared with the "var" keyword is allocated on the stack. Before being used in an expression or anywhere else, it is loaded from the stack. It is somewhat similar to the initial LLVM IR, before the scalar replacement pass for aggregates.

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
	while (step < endStep) {
		var y = 0;
		var endY = 256;
		while (y < endY) {
			var x = 0;
			var endX = 512;
			while (x < endX) {
				var colour = x * y * step;
				put_pixel(x y colour);
				x = x + 1;
			}
			y = y + 1;
		}
		flush();
		step = step + 1;
		dump(step);
	}
	var res = 0;
	return res;
}
```

## Examples
![](https://github.com/egorshamshura/llvm-solutions/blob/main/assets/llvm-example-2.gif)