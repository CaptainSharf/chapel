record A {
  var i : integer;
}

var a1 : A;
var a2 : A;
a1.i = 1;
a2.i = 2;

writeln("1 = ", a1 != a2);

a2.i = 1;

writeln("0 = ", a1 != a2);
