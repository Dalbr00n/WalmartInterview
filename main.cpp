#include "main.hpp"

int main(int argc, char* argv[]){
    uint8_t seat_open[10][20] = {0};
    uint8_t row_full = 0;

    ifstream input;
    ofstream output;
    string input_s = argv[1];

    input.open(input_s.c_str());
    output.open("output.txt");

    string line;
    string seats;
    int nseats;
    bool reserved = false;
    string reservation;
    uint8_t logic = 0;
    vector<int> seat;

    if(input.is_open()){
        output << "INPUT: " << input_s << endl << endl;
        while(getline(input, line)){
            reserved = false;
            reservation = line.substr(0, line.find(' '));
            seats = line.substr(line.find(' '));
            nseats = stoi(seats);

            for(int k = row_full; k < 10; k++){                
                for(int i = 0; i < 20; i++){
                    logic = 0;
                    if(i > (20 - nseats)) break;
                    else if(seat_open[k][i] == 1) continue;
                    else if(seat_open[k][i-1] == 1 & seat_open[k][i] == 0){
                        i += 2;
                        continue;
                    }
                    else{
                        if(k == 0){
                            for(int j = 0; j < nseats; j++) logic |= (seat_open[k][i + j] | seat_open[k + 1][i + j]);
                            if(logic == 0) {
                                output << reservation << " ";
                                for(int j = 0; j < nseats; j++) {
                                    seat_open[k][i + j] = 1;
                                    uint8_t row = 65 + k;
                                    output << row << (i + j  + 1);
                                    if(j < nseats - 1) output << ",";
                                }
                                output << endl;
                                reserved = true;
                                break;
                            }
                        }
                        else if(k == 19){
                            for(int j = 0; j < nseats; j ++) logic |= (seat_open[k][i + j] | seat_open[k - 1][i + j]);
                            if(logic == 0) {
                                output << reservation << " ";
                                for(int j = 0; j < nseats; j++) {
                                    seat_open[k][i + j] = 1;
                                    uint8_t row = 65 + k;
                                    output << row << (i + j  + 1);
                                    if(j < nseats - 1) output << ",";
                                }
                                output << endl;
                                reserved = true;
                                break;
                            }
                        }
                        else{
                            for(int j = 0; j < nseats; j ++) logic |= (seat_open[k][i + j] | seat_open[k + 1][i + j] | seat_open[k - 1][i + j]);
                            if(logic == 0){
                                output << reservation << " ";
                                for(int j = 0; j < nseats; j++) {
                                    seat_open[k][i + j] = 1;
                                    uint8_t row = 65 + k;
                                    output << row << (i + j  + 1);
                                    if(j < nseats - 1) output << ",";
                                }
                                output << endl;
                                reserved = true;
                                break;
                            }
                        }
                    }
                }
                if(reserved == true) break;
            }
            seat.push_back(stoi(seats));
        }
    }
    input.close();
    output.close();

    // int total = 0;
    // for(auto i = seat.begin(); i < seat.end(); i++){
    //     cout << *i << ",";
    //     total += *i;
    // }
    // cout << endl;
    // cout << "Total seats: " << total << endl;

    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            cout << unsigned(seat_open[i][j]) << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}