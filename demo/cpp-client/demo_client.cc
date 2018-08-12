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
    bool logout_on = false;
    bool username_on = false;
    bool password_on = false;
    bool platform_on = false;

    char *user_name;
    char *password;
    char *device;

    for (int i = 1; i < argc; ++i) {
        char *pchar = argv[i];
        switch (pchar[0]) {
        case '-': {
            switch (pchar[1]) {
            case 'i':
                signin_on = true;
                break;
            case 'l':
                logout_on = true;
                break;
            case 'r':
                cout << "3" << endl;
                signup_on = true;
            case 'u':
                username_on = true;
                break;
            case 'p':
                password_on = true;
                break;
            case 'd':
                platform_on = true;
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
            } else if (platform_on) {
                device = pchar;
                platform_on = false;
            }
            break;
        }
    }

    GreeterClientImpl greeter("10.0.0.23:50051");

    string user(user_name);
    string pwd(password);
    string dc(device);
    if (signin_on) {
        string reply = greeter.SignIn(dc, user, pwd);
        cout << "Sign In: " << reply << endl;
    } else if (signup_on) {
        string reply = greeter.SignUp(user, pwd);
        cout << "Sign Up: " << reply << endl;
    }else if (logout_on) {
        string reply = greeter.LogOut(dc, user, pwd);
        cout << "Logout: " << reply << endl;
    }
    return 0;
}
