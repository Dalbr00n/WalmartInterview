#include "main.hpp"

int main(int argc, char* argv[]){
    //We use a two dimensional array to store the values of the 
    //seated members. Although this is constained to the specifications
    //in the problem statement, we could use a larger matrix.
    uint8_t seat_open[10][20] = {0};
    uint8_t row_full = 0;

    //setup for the input and output datasreams
    //input filepath is the first command line arguement
    ifstream input;
    ofstream output;
    string input_s = argv[1];
    input.open(input_s.c_str());
    output.open("output.txt");

    //create variables to data from the input file to be used in the
    //seating algorithm
    string line;
    string seats;
    int nseats;
    bool reserved = false;
    string reservation;
    uint8_t logic = 0;

    //check if input file is opened correctly
    if(input.is_open()){
        output << "INPUT: " << input_s << endl << endl;
        //while there is data, apply the algorithm
        while(getline(input, line)){
            reserved = false;

            //seperate reservation name and number of seats
            reservation = line.substr(0, line.find(' '));
            seats = line.substr(line.find(' '));
            nseats = stoi(seats);

            for(int k = row_full; k < 10; k++){   
                int firstRow = (k == 0) ? 1 : 0;
                int lastRow  = ((k - 19) == 0) ? 1 : 0;             
                for(int i = 0; i < 20; i++){
                    logic = 0;
                    //if there are not enough available seats continue to next row
                    if(i > (20 - nseats)) break;
                    //if seat is occupied, continue to next seat
                    else if(seat_open[k][i] == 1) continue;
                    //if the end of a party section is reached, leave space for
                    //social distancing
                    else if(seat_open[k][i-1] == 1 & seat_open[k][i] == 0){
                        i += 2;
                        continue;
                    }
                    else{
                        //check if the current seat, the seat in previous row, and the seat in next row is open for length of party
                        if(firstRow) for(int j = 0; j < nseats; j ++) logic |= (seat_open[k][i + j] | seat_open[k + 1][i + j]);
                        else if(lastRow) for(int j = 0; j < nseats; j ++) logic |= (seat_open[k][i + j] | seat_open[k - 1][i + j]);
                        else for(int j = 0; j < nseats; j ++) logic |= (seat_open[k][i + j] | seat_open[k + 1][i + j] | seat_open[k - 1][i + j]);
                        
                        if(logic == 0){
                            //output name of reservation
                            output << reservation << " ";
                            for(int j = 0; j < nseats; j++) {
                                seat_open[k][i + j] = 1;
                                //write to output as ASCII character code, A = 65
                                uint8_t row = 65 + k;
                                output << row << (i + j  + 1);
                                if(j < nseats - 1) output << ",";
                            }
                            output << endl;
                            //mark the party as reserved
                            reserved = true;
                            break;
                        }
                    }
                }
                //if the party was reserved, continue to next reservation
                if(reserved == true) break;

                if(k == 9 && reserved == false){
                    cout << "Party not seated" << endl;
                    output << reservation << "  PARTY NOT SEATED, NO SEATING AVAILABLE" << endl;
                }
            }
        }
    }
    //close output files
    input.close();
    output.close();

    //Visual representation of seating chart
    cout << setw(4) << " " << "[[" 
    << setw(14) << " " << "SCREEN" << setw(15) << " " << "]]" << endl;
    cout << setw(4) << " " << "---------------------------------------" << endl;
    for (int i = 0; i < 10; i++){
        uint8_t row = 65 + i;
        cout << row << "   ";
        for(int j = 0; j < 20; j++){
            cout << unsigned(seat_open[i][j]) << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}