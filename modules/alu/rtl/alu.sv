/* verilator lint_off IMPORTSTAR */

`include "alu_com.sv"

import alu_com::*;

module alu #(
    parameter WIDTH = 32
) (
    input logic [WIDTH-1:0] a_i,
    input logic [WIDTH-1:0] b_i,
    input aluop op,

    output logic [WIDTH-1:0] data_o
);

always_comb begin
    unique case(op)
        aluopADD: data_o = a_i + b_i;
        aluopSUB: data_o = a_i - b_i;
        aluopAND: data_o = a_i & b_i;
        aluopOR: data_o = a_i | b_i;
        aluopXOR: data_o = a_i ^ b_i;
        aluopSHL: data_o = a_i << b_i;
        aluopSHR: data_o = a_i >> b_i;
        
        default: data_o = 0;
    endcase
end
    
endmodule