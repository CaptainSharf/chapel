class Foo {
  var x: int;
  var y: bool;

  proc init(xVal) {
    if (xVal < 5) {
      x = xVal;
      y = true;
    } else {
      x = xVal;
    }
  }
}

var x = new borrowed Foo(4);
var y = new borrowed Foo(6);
writeln(x);
writeln(y);
