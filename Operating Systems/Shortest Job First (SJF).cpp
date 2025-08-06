#include <bits/stdc++.h>
using namespace std;

struct process {
    int 
    id,
    arrival_time, 
    burst_time, 
    completion_time  = -1, 
    waiting_time     = -1, 
    turn_around_time = -1;
};

bool sortbyID(process a, process b){
    return a.id < b.id;
}

bool sortbyAT(process a, process b){
    return a.arrival_time < b.arrival_time;
}

bool sortbyBTandAT(process a, process b){
    if(a.burst_time == b.burst_time){
        return a.arrival_time < b.arrival_time; // since burst time is same
    }
    return a.burst_time < b.burst_time;
}

bool processExists(vector<process> &Q, process P){
    return find_if(Q.begin(), Q.end(), [&P](process QP){
        return (QP.id == P.id);
    }) != Q.end();
}

int find_process_index(vector<process> &container, process &target){
    for (int i = 0; i < container.size(); ++i){
        if(container[i].id == target.id) return i;
    }
    return -1;
}

void AddProcess(vector<process> &Q, vector<process> &container, int currnt_time){
    for(process P : container){
        if(P.completion_time == -1 && P.arrival_time <= currnt_time && !processExists(Q, P)){
            Q.push_back(P);
        }
    }

    // Condition: If Q has more than 1 process, the priority will be based on burst time
    if(Q.size() > 1){
        sort(Q.begin(), Q.end(), sortbyBTandAT);
    }
}

void printProcess(process P){
    cout << "p" << P.id                 << " \t |";
    cout << " " << P.arrival_time       << " \t |";
    cout << " " << P.burst_time         << " \t |";
    cout << " " << P.completion_time    << " \t |";
    cout << " " << P.waiting_time       << " \t |";
    cout << " " << P.turn_around_time   << " \t |";
    cout << endl;
}

void printProcesses(vector<process>&container){
    cout << "ID \t |";
    cout << " AT \t |";
    cout << " BT \t |";
    cout << " CT \t |";
    cout << " WT \t |";
    cout << " TAT \t |";
    cout << endl << "----------------------------------------------" << endl;
    int sum_of_TAT = 0, sum_of_BT = 0;
    for(process P : container){
        sum_of_BT   += P.burst_time;
        sum_of_TAT  += P.turn_around_time;
        printProcess(P);
    }
    cout << endl << "----------------------------------------------" << endl << endl;

    cout << "Average Turn-Over-Time: " << ((float)sum_of_TAT / container.size()) << endl;
    cout << "Throughput: " << ((float) container.size() / sum_of_BT) << endl;
}

int main(){
    int n; cin >> n;
    vector<process> P;

    for(int i=0; i<n; i++){
        process input_P;
        input_P.id = i+1;
        cin >> input_P.arrival_time;
        cin >> input_P.burst_time;
        P.push_back(input_P);
    }

    
    // Initial Process will be start based on arrival_time
    sort(P.begin(), P.end(), sortbyAT);

    vector<process> Q; // Ready Queue
    int current_time = P.front().arrival_time; // Initial current_time
    AddProcess(Q, P, current_time);

    while(!Q.empty()){
        // Find the index in the vector by searching front process
        int i = find_process_index(P, Q.front());

        // -------------------------------------------------------------

        // Completion Time = (last_completion_time + burst_time)
        P[i].completion_time = current_time + P[i].burst_time;

        // Turn Around Time = (completion_time - arrival_time)
        P[i].turn_around_time = P[i].completion_time - P[i].arrival_time;
        
        // Waiting Time = (turn_around_time - burst_time)
        P[i].waiting_time = P[i].turn_around_time - P[i].burst_time;
        
        // -------------------------------------------------------------

        // Update Current Time
        current_time = P[i].completion_time;

        // Prepare Ready-Queue
        Q.erase(Q.begin()); // Remove completed process
        AddProcess(Q, P, current_time);
    }

    sort(P.begin(), P.end(), sortbyID);
    printProcesses(P);
}
