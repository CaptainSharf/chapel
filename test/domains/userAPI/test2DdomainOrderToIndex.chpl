proc testDom(dom: domain) {
  for (idx, i) in zip(dom, 0..<dom.size) {
    if idx != dom.orderToIndex(i) {
      writeln('wrong index for ', dom, ':', idx, ' != dom.orderToIndex(', i,')');
      writeln('  got ', dom.orderToIndex(i), ' instead');
    }
  }
}

{
    var dom = {1..3,1..3,1..5};
    testDom(dom);
}
{
    var dom = {1..3,1..3,1..5 by -2};
    testDom(dom);
}
{
    var dom = {1..4 by 2,1..4 by 2,1..4 by -2};
    testDom(dom);
}
{
    var dom = {1..4 by 2,1..4 by 2 align 2,1..4 by -2};
    testDom(dom);
}
{
    var dom = {1..3,1..3};
    testDom(dom);
}
