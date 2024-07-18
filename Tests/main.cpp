#include "AssemblyMapTests.h"
#include "ParserTests.h"
#include "Tester.h"
int main () {
    Tester tester;
    tester (TestAssemblyMapInitailization, "Testing Assembly Map Initialzation");
    tester (TestParserReader, "Testing Parser on Test.vm");
    return 0;
}
