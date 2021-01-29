#include <iostream>
#include <map>
#include <regex>
using namespace std;

map <string, string> tagMap;



void createMap(int& n, string pretag) {
    if (!n) return;

    string line, tag, attr, value;
    getline(cin, line);

    int i = 1;
    if (line[i] == '/') {           // found closing tag
        while (line[i] != '>') i++;
        if (pretag.size() > (i - 2))        // update tag
            tag = pretag.substr(0, pretag.size() - i + 1);
        else
            tag = "";
    }
    else {                       // found opening tag
        while (line[i] != ' ' && line[i] != '>') i++;
        tag = line.substr(1, i - 1);    // update tag
        if (pretag != "") tag = pretag + "." + tag;

        int j;
        while (line[i] != '>') { // go through attributes
            j = ++i;
            while (line[i] != ' ') i++;
            attr = line.substr(j, i - j);    // attribute name

            while (line[i] != '\"') i++;
            j = ++i;
            while (line[i] != '\"') i++;
            value = line.substr(j, i - j);    // attribute value
            i += 1;

            tagMap[tag + "~" + attr] = value;
        }
    }
    createMap(--n, tag);
}

int main() {
    cout << "Example:\n"
        "HRML listing\n"
        "<tag1 value = \"value\" >\n"
        "<tag2 name = \"name\">\n"
        "<tag3 another = \"another\" final = \"final\">\n"
        "</tag3>\n"
        "</tag2>\n"
        "</tag1>\n"
        "Queries\n"
        "tag1~value\n"
        "tag1.tag2.tag3~name\n"
        "tag1.tag2~value\n\n\n";



    while (true) {
        cout << "Please add a first number: \n";
        int n, q;
        cin >> n;
        cout << "Please add a second number: \n";
        cin >> q;
        cin.ignore();
        createMap(n, "");

        string attr, value;
        while (q--) {
            cout << "add command: \n";
            getline(cin, attr);
            value = tagMap[attr];
            if (value == "") value = "Not Found!";
            cout << "Result: \n" << value << endl;
        }
    }
    return 0;
}
