#include "dlist.h"
#include <iostream>
using namespace std;

/**
 * @brief This function helps to determine whether the input command is valid.
 * @param command
 * @return true if the command is valid, else false.
 */
bool isValid(char command){
    switch (command){
        case '+':case '-':case '*':case '/':case 'n':case 'd':case 'r':case 'p':case 'c':case 'a':case 'q': return true;
        default: return false;
    }
}

int main(){
    Dlist<int> list;
    while (true) {
        try {
            string input;
            char command;
            int number = 0;
            cin >> input;
            if (input.size() == 1) {
                if (isValid(input[0])) {
                    command = input[0];
                    Dlist<int> new_list;
                    new_list = list;
                    switch (command) {
                            int *number1, *number2, *answer;
                        case '+':
                            number1 = list.removeFront();
                            if (list.isEmpty()){
                                list.insertFront(new int(*number1));
                                delete number1;
                                throw (emptyList());
                            }
                            else {
                                number2 = list.removeFront();
                                list.insertFront(new int(*number1 + *number2));
                                delete number1;
                                delete number2;
                            }
                            break;
                        case '-':
                            number1 = list.removeFront();
                            if (list.isEmpty()){
                                list.insertFront(new int(*number1));
                                delete number1;
                                throw (emptyList());
                            }
                            else {
                                number2 = list.removeFront();
                                list.insertFront(new int(*number2 - *number1));
                                delete number1;
                                delete number2;
                            }
                            break;
                        case '*':
                            number1 = list.removeFront();
                            if (list.isEmpty()){
                                list.insertFront(new int(*number1));
                                delete number1;
                                throw (emptyList());
                            }
                            else {
                                number2 = list.removeFront();
                                list.insertFront(new int(*number1 * *number2));
                                delete number1;
                                delete number2;
                            }
                            break;
                        case '/':
                            number1 = list.removeFront();
                            if (list.isEmpty()){
                                list.insertFront(new int(*number1));
                                delete number1;
                                throw (emptyList());
                            }
                            else {
                                number2 = list.removeFront();
                                if (*number1 == 0) {
                                    list.insertFront(new int(*number2));
                                    list.insertFront(new int(*number1));
                                    delete number1;
                                    delete number2;
                                    throw(0);
                                } else {
                                    list.insertFront(new int(*number2 / *number1));
                                    delete number1;
                                    delete number2;
                                }
                            }
                            break;
                        case 'n':
                            answer = list.removeFront();
                            *answer *= -1;
                            list.insertFront(new int(*answer));
                            delete answer;
                            break;
                        case 'd':
                            number1 = list.removeFront();
                            list.insertFront(new int(*number1));
                            list.insertFront(new int(*number1));
                            delete number1;
                            break;
                        case 'r':
                            number1 = list.removeFront();
                            if (list.isEmpty()){
                                list.insertFront(new int(*number1));
                                delete number1;
                                throw (emptyList());
                            }
                            else {
                                number2 = list.removeFront();
                                list.insertFront(new int(*number1));
                                list.insertFront(new int(*number2));
                                delete number1;
                                delete number2;
                            }
                            break;
                        case 'p':
                            number1 = list.removeFront();
                            cout << *number1 << endl;
                            list.insertFront(new int(*number1));
                            delete number1;
                            break;
                        case 'c':
                            while (!list.isEmpty()) {
                                int *remove = list.removeFront();
                                delete remove;
                            }
                            break;
                        case 'a':
                            if (!new_list.isEmpty()) while (!new_list.isEmpty()) cout << *new_list.removeFront() << " ";
                            cout << endl;
                            break;
                        case 'q': {
                            while (!list.isEmpty()) {
                                int *remove = list.removeFront();
                                delete remove;
                            }
                            break;
                        }
                    }
                    if (command == 'q') break;
                }
                // Handle the command cases.
                else if (input[0] >= '0' && input[0] <= '9') {
                    number = stoi(input);
                    list.insertFront(new int(number));
                }
                // Handle the number cases.
                else throw(0.1);
                // Else throw error messages.
            } else {
                int sign = 1;
                for (unsigned int i = 0; i < input.size(); i++) {
                    if ((i == 0) && (input[i] == '-')) sign = -1;
                    else {
                        if (isdigit(input[i])) number = number * 10 + input[i] - '0';
                        else throw(0.1);
                    }
                }
                number *= sign;
                list.insertFront(new int(number));
            }
            // If the number of input characters is larger than 1, check whether it is valid and simultaneously derive the number.
        }
        catch (double) {cout << "Bad input\n";}
        catch (emptyList) {cout << "Not enough operands\n";}
        catch (int) {cout << "Divide by zero\n";}
        // Handle errors and output error messages.
    }
    return 0;
}