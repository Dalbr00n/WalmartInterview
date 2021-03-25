#include "main.hpp"

int main(){
    uint8_t seat_open[10][20];
    uint8_t row_full = 0;

    ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");

    string line;
    string seats;
    int nseats;
    string reservation;
    vector<int> seat;

    if(input.is_open()){
        while(getline(input, line)){
            reservation = line.substr(0, line.find(' '));
            seats = line.substr(line.find(' '));
            nseats = stoi(seats);

            for(row_full; row_full < 10; row_full++){
                for(int i = 0; i < 20; i++){
                    if(19 - nseats < i) break;
                    else if(seat_open[row_full][i] == 0) continue;
                    else{

                    }
                }
            }
            cout << reservation << endl;
            seat.push_back(stoi(seats));
        }
    }
    input.close();
    int total = 0;
    for(auto i = seat.begin(); i < seat.end(); i++){
        cout << *i << ",";
        total += *i;
    }
    cout << endl;
    cout << "Total seats: " << total << endl;
    return 0;
}