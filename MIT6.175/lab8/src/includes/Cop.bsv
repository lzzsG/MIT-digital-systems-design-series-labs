/*

Copyright (C) 2012 Muralidaran Vijayaraghavan <vmurali@csail.mit.edu>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/


import Types::*;
import ProcTypes::*;
import Ehr::*;
import ConfigReg::*;
import Fifo::*;

interface Cop;
    method Action start;
    method Bool started;
    method Data rd(RIndx idx);
    method Action wr(Maybe#(FullIndx) idx, Data val);
    method ActionValue#(Tuple2#(RIndx, Data)) cpuToHost;

    // external interface to status, cause, and epc registers
    method Action causeException(Addr current_pc, Bit#(5) cause);
    method Action returnFromException;
    method Addr getEPC;
    method Bool isUserMode;
endinterface

(* synthesize *)
module mkCop(Cop);
    Reg#(Bool) startReg <- mkReg(False);

    // FIFO for writing to co-processor registers that send messages to the host
    Fifo#(2, Tuple2#(RIndx, Data)) copFifo <- mkCFFifo;

    // Co-processor registers:
    // 10 - Number of clock cycles elapsed
    Reg#(Data) cycles   <- mkReg(0);
    // 11 - Number of instructions executed
    Reg#(Data) numInsts <- mkReg(0);
    // 18 - Write an integer to stderr
    //      implemented by enqueuing to copFifo
    // 19 - Write a char to stderr
    //      implemented by enqueuing to copFifo
    // 21 - Finish code
    //      implemented by enqueuing to copFifo

    rule count (startReg);
        cycles <= cycles + 1;
        $display("\nCycle %d ----------------------------------------------------", cycles);
    endrule

    method Action start;
        startReg <= True;
        cycles <= 0;
    endmethod

    method Bool started;
        return startReg;
    endmethod

    // method for reading co-processor registers
    method Data rd(RIndx idx);
        return (case(idx)
                    10: cycles;
                    11: numInsts;
                endcase);
    endmethod

    // method for writing co-processor registers
    method Action wr(Maybe#(FullIndx) idx, Data val);
        if(isValid(idx) && validValue(idx).regType == CopReg) begin
            case (validRegValue(idx))
                18: copFifo.enq(tuple2(18, val));
                19: copFifo.enq(tuple2(19, val));
                21: copFifo.enq(tuple2(21, val));
            endcase
        end
        numInsts <= numInsts + 1;
    endmethod

    method ActionValue#(Tuple2#(RIndx, Data)) cpuToHost;
        copFifo.deq;
        return copFifo.first;
    endmethod
endmodule
