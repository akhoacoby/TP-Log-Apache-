#include <iostream>
#include <string>
#include "log.h"

using namespace std;

int main() {

    string test = "192.168.0.0 - - [08/Sep/2012 :11:16:02 +0200] \"GET /temps/4IF16.html HTTP/1.1\" 200 12106 \"https://intranet-if.insa-lyon.fr/temps/4IF15.html\" \"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1\"";
    Log test_log(test);

    cout << test_log;

    return 0;
}
