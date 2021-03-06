#include "systemc.h"
#include "common/defines.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

using std::cout;
using namespace std;

struct operation{
    string cmd;
    string address;
    int data_size;
    vector<int> data;
    string rvu_instruction;
};

SC_MODULE(hmc_tb){
	 sc_out<sc_lv<34> > address_in_t;
 	 sc_out<sc_lv<7> > cmd_in_t;
 	 sc_out<sc_lv<128> > data_in_t[16];
 	 sc_out<sc_lv<3> > cub_in_t;
 	 sc_out<bool> reset;

	 sc_in<bool> clk;

	 sc_in<sc_lv<128> > packet_out_t;
        
        string trace_name;
	 SC_CTOR(hmc_tb){
 	 	 SC_THREAD (process);
 	 	 SC_METHOD(print);
 	 	 sensitive << packet_out_t;
 	 }


	 void print(){
		 cout << "Packet out @ " << sc_time_stamp() << " :\n";
		 cout << packet_out_t.read().range(127,64) << endl;
		 cout << packet_out_t.read().range(63,0) << endl;
		 cout << endl;
 	 }
 	 
 	 void open_trace(){
 	 	ifstream fin;
                 if(trace_name.empty()){
                    fin.open("trace.txt");
                 }
                 else{
                     fin.open(trace_name.c_str()); 
                 }
                string c;
                num_operations = 0;
                while(!fin.eof()){
                    operation op;
                    fin >> c;
                    op.cmd = c;
                    //cerr << op.cmd << endl;
                    fin >> c;
                    op.address = c;
                    fin >> c;
                    op.data_size = atoi(c.c_str());
                    op.data.resize(op.data_size);
                    if(op.cmd == "0000001"){
                    	fin >> c;
                    	op.rvu_instruction = c;

                    }
                    else{
                    	for(int i = 0; i < op.data_size; i++){
                    		fin >> c;
                    		op.data[i] = atoi(c.c_str());
                    	}
                    }
                    operations.push_back(op);
                    num_operations++;
                }

                fin.close();
                counter = 0;
         }

 	 void process(){
 	 	 for(int i =0; i < 16; i++) data_in_t[i].write(i);
 	 	 cub_in_t.write("000");
 	 	 reset.write(true);
 	 	 wait(TRANS_CLOCK_RATE,SC_NS);

 	 	 reset.write(false);
 	 	 wait(TRANS_CLOCK_RATE, SC_NS);


 	 	 for(int i = 0; i < num_operations; i++){
 	 		 if(operations[i].cmd == "0000001"){
 	 			data_in_t[0].write(operations[i].rvu_instruction.c_str());
 	 		 }
 	 		 else{
				 if(operations[i].data_size != 0){
					 if(operations[i].data_size == 1){
						 data_in_t[0].write("00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000001");
					 }
					 else{
						 for(int j = 0; j < operations[i].data_size; j++)
							 data_in_t[j].write(operations[i].data[j]);
					 }
				 }
 	 		 }
 	 		 address_in_t.write(operations[i].address.c_str());
 	 		 //cout << "input address: " << operations[i].address << endl;
 	 		 cmd_in_t.write(operations[i].cmd.c_str());

 	 	 	 wait(TRANS_CLOCK_RATE,SC_NS);
 	 	 }
 	 }

private:
 	 vector<operation> operations;
 	 int num_operations;
 	 int counter;
 };
