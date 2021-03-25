# WalmartInterview


# This program was written by Daniel Albrecht, March 25, 2021

# The following assumptions were made:

# -The user will use the command line to submit a valid file for analysis
# -This file must adhere to the specifications listed in the "Input Description" section of the "Movie Theater Seating Challenge - 2020" document
# -Reservation priority is given as a fisrt come, first serve basis
# -The optimal seating is closest to the screen, this is given to parties who register sooner, if a party can fit in additional seating they are seated as close to the screen as possible
# -Party sizes do not exceed a 20 person capacity

# This program is to be run on the Command Line utillity and will output to the Command Line as well

# To compile: g++ -std=c++11 main.cpp -o main\
# To run: ./main [Path-to-Input-file]
# NOTE: if your filepath includes whitespace, you may need to use the '' characters to compile correctly