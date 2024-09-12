#include <iostream>
#include "dlist.h"
using namespace std;

enum priority{regular, silver, gold, platinum};
// Define four kinds of status

string priority_name[4] ={"regular", "silver", "gold", "platinum"};
// Also define four kinds of status, but used for output.

struct member{
    int timestamp;
    string name;
    priority status;
    int duration;
};
// Define a struct for members, with four elements included.

/**
 * @brief This function helps to check whether the reservation agent has finished all the calls that have arrived.
 * @param queue
 * @return true if all the four queues are empty, else false
 */
bool check_empty(Dlist<member> queue[4]){
    bool status = true;
    for (int i = 0; i < 4; i++) if (!queue[i].isEmpty()) status = false;
    return status;
}

/**
 * @brief This function helps to insert all the statistics from the structs "member" into the queue.
 * @param call
 * @param queue
 * @param tick
 * @param total_line
 */
void insert_queue(member* call, Dlist<member> queue[4], int tick, int total_line){
    for (int i = 0; i < total_line; i++){
        if (call[i].timestamp == tick){
            cout << "Call from " << call[i].name << " a " << priority_name[call[i].status] << " member" << endl;
            queue[call[i].status].insertBack(new member(call[i]));
        }
    }
}

/**
 * @brief If the agent is not busy now, there are possibly new calls from the future. Therefore, the agent has to
 * at least wait until the the largest timestamp from the calls.
 * @param call
 * @param total_line
 * @return the largest timestamp from the calls
 */
int find_largest(member* call, int total_line) {
    int largest = -1;
    for (int i = 0; i < total_line; i++)
        if (call[i].timestamp > largest) largest = call[i].timestamp;
    return largest;
}

/**
 * @brief If the agent is busy, he will continue handling the call. Else, he will look for a new call from
 * the highest priority and handle it. Whether he is busy depends on the variant "same", showing whether he is handling the same call as last tick.
 * @param queue
 * @param same
 * @param responding
 */
void find_respond(Dlist<member> queue[4], bool &same, int &responding){
    if (same) {
        member *removed = queue[responding].removeFront();
        removed->duration--;
        if (removed->duration > 0) {
            queue[responding].insertFront(new member(*removed));
            same = true;
        } else same = false;
        delete removed;
    }
    else {
        for (int i = 3; i >= 0; i--) {
            if (!queue[i].isEmpty()) {
                member *removed = queue[i].removeFront();
                removed->duration--;
                cout << "Answering call from " << removed->name << endl;
                if (removed->duration > 0) {
                    queue[i].insertFront(new member(*removed));
                    responding = i;
                    same = true;
                } else same = false;
                delete removed;
                break;
            }
        }
    }
}

int main(){
    int total_line;
    string line;
    cin >> line;
    total_line = stoi(line);
    auto *call = new member[total_line];
    auto *queue = new Dlist<member>[4];
    // Initialize the calls and the waiting queue.
    int responding;
    for (int i = 0; i < total_line; i++){
        cin >> line;
        call[i].timestamp = stoi(line);
        cin >> line;
        call[i].name = line;
        cin >> line;
        for (int count = 0; count < 4; count++){
            if (line == priority_name[count]) {
                call[i].status = priority(count);
                break;
            }
        }
        cin >> line;
        call[i].duration = stoi(line);
    }
    // Storing the input data into the structs.
    int tick = 0;
    bool same = false;
    while ((find_largest(call, total_line) >= tick) || (!check_empty(queue))){
        cout << "Starting tick #" << tick << endl;
        insert_queue(call, queue, tick, total_line);
        find_respond(queue, same, responding);
        tick++;
    }
    // Continue taking calls and make responds.
    cout << "Starting tick #" << tick << endl;
    // Announce the final tick at last.
    delete []call;
    delete []queue;
    return 0;
}