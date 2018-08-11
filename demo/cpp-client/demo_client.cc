#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "greeter_client_impl.hpp"

using namespace std;
using namespace grpcdemo;

int main(int argc, char** argv) {
    bool signin_on = false;
    bool signup_on = false;
    bool username_on = false;
    bool password_on = false;

    char *user_name;
    char *password;

    for (int i = 1; i < argc; ++i) {
        //cout << "argv[" << i << "]:" << argv[i] << endl;
        char *pchar = argv[i];
        switch (pchar[0]) {
        case '-': {
            //cout << "case \'-\' found" << endl;
            switch (pchar[1]) {
            case 'l':
                signin_on = true;
            case 'r':
                signup_on = true;
            case 'u':
                username_on = true;
                break;
            case 'p':
                password_on = true;
                break;
            default:
                cout << "Invalid param:  " << pchar[1] << endl;
            }
            break;
        }
        default:
            if (username_on) {
                //cout << "user name: " << pchar << endl;
                user_name = pchar;
                username_on = false;
            } else if (password_on) {
                //cout << "password: " << pchar << endl;
                password = pchar;
                password_on = false;
            }
            break;
        }
    }

    GreeterClientImpl greeter("10.0.0.23:50051");

    if (signin_on) {
        string user(user_name);
        string pwd(password);
        string reply = greeter.SignIn(user, pwd);
        cout << "Sign In: " << reply << endl;
    } else if (signup_on) {
        string user(user_name);
        string pwd(password);
        string reply = greeter.SignUp(user, pwd);
        cout << "Sign Up: " << reply << endl;
    }
    return 0;
}
