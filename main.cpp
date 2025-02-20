#include <iostream>
#include <string>
#include "simplelog.h"
#include "lecture.h"
#include "Stats.h"

using namespace std;

int main(int argv, char * argc[] )
{

    Lecture lecture("ex.txt");
    vector <string> filecontent = lecture.getLogContent();
    Stats analog;

    for (const auto& line: filecontent){
      Log test_log(line);
      SimpleLog simple_test_log(test_log);
      cout << "Ajout de " << endl << simple_test_log;
      analog.Append(simple_test_log);


    }
    cout << analog;
    analog.Execute_without_options();



    return 0;
}

// TEST CLASS LOG //
// // Lines from exemple-mini-non-exhaustif.txt that have to be given as str by class Lecture
// string test2 = "192.168.0.1 - - [08/Sep/2012:11:15:00 +0200] \"GET /page2.html HTTP/1.1\" 200 2000 \"http://intranet-if.insa-lyon.fr/page1.html\" \"Mozilla/5.0\"";
// string test3 = "192.168.0.1 - - [08/Sep/2012:11:37:00 +0200] \"GET /page1.html HTTP/1.1\" 200 1000 \"http://intranet-if.insa-lyon.fr/page2.html\" \"Mozilla/5.0\"";
// string test4 = "192.168.0.1 - - [08/Sep/2012:12:12:00 +0200] \"GET /page2.html HTTP/1.1\" 200 2000 \"http://intranet-if.insa-lyon.fr/page3.html\" \"Mozilla/5.0\"";
// string test5 = "192.168.0.1 - - [08/Sep/2012:12:16:00 +0200] \"GET /page3.html HTTP/1.1\" 200 3000 \"http://intranet-if.insa-lyon.fr/page2.html\" \"Mozilla/5.0\"";
// string test6 = "192.168.0.1 - - [08/Sep/2012:12:16:01 +0200] \"GET /image.jpg HTTP/1.1\" 200 50000 \"http://intranet-if.insa-lyon.fr/page3.html\" \"Mozilla/5.0\"";
// string test7 = "192.168.0.1 - - [08/Sep/2012:12:59:00 +0200] \"GET /page2.html HTTP/1.1\" 200 2000 \"http://intranet-if.insa-lyon.fr/page1.html\" \"Mozilla/5.0\"";
//
// // Create log objects
// Log test_log2(test2);
// Log test_log3(test3);
// Log test_log4(test4);
// Log test_log5(test5);
// Log test_log6(test6);
// Log test_log7(test7);
// SimpleLog test_simple_log(test_log7);
//
// // Print log infos
// cout << test_log2;
// cout << test_log3;
// cout << test_log4;
// cout << test_log5;
// cout << test_log6;
// cout << test_simple_log;
//
// // Test default constructor
// Log test_log_default;
// cout << test_log_default;
//
// SimpleLog test_simple_log_default;
// cout << test_simple_log_default;


// TEST TXT TO LOG
// Lecture lecture("ex.txt");
// vector <string> filecontent = lecture.getLogContent();
//
// for (const auto& line: filecontent){
//   Log test_log(line);
//   SimpleLog simple_test_log(test_log);
//
//   cout << simple_test_log;
// }
