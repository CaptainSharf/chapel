use BlockDist;

proc test(d1, d2) {
  var a1: [d1] int;
  var a2: [d2] int;

  a1 = 10;
  a2 = 20;

  a1 <=> a2;

  writeln(a1);
  writeln(a2);
}


{
  writeln("simple case: everything should be optimized");
  var d1 = {1..10} dmapped Block({1..10});
  var d2 = {1..10} dmapped Block({1..10});

  test(d1, d2);
  
  writeln();
}


{
  writeln("one array is unevenly distributed. block shouldn't optimize");
  var d1 = {0..9} dmapped Block({1..10});
  var d2 = {1..10} dmapped Block({1..10});

  test(d1, d2);

  writeln();
}

{
  writeln("both are unevenly distributed, but they align with each other");
  var d1 = {0..9} dmapped Block({1..10});
  var d2 = {0..9} dmapped Block({1..10});

  test(d1, d2);

  writeln();
}

{
  // this case can technically be optimized but it isn't today, mostly because
  // abundance of caution
  writeln("One of the domains are strided");
  var d1 = {0..9 by 2} dmapped Block({1..10});
  var d2 = {0..4} dmapped Block({1..10});

  test(d1, d2);

  writeln();
}

{
  writeln("both are strided and aligned");
  var d1 = {0..9 by 2} dmapped Block({1..10});
  var d2 = {0..9 by 2} dmapped Block({1..10});

  test(d1, d2);

  writeln();
}

{
  writeln("both are strided, have same number of elements but not aligned, block shouldn't optimize");
  var d1 = {0..9 by 2} dmapped Block({1..10});
  var d2 = {1..10 by 2} dmapped Block({1..10});

  test(d1, d2);

  writeln();
}

{
  // this case can technically be optimized but it isn't today, mostly because
  // abundance of caution
  writeln("both are strided and misaligned");
  var d1 = {0..9 by 2 align 0} dmapped Block({1..10});
  var d2 = {0..9 by 2 align 1} dmapped Block({1..10});

  test(d1, d2);

  writeln();
}
