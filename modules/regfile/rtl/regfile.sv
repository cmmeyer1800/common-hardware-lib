module regfile #(
    /* verilator lint_off UNUSEDPARAM */
    parameter NUM_REGS = 16,
    parameter REG_WIDTH = 32
) (
    input logic clk,
    input logic rst_n,
    input logic load_i,
    input logic [REG_WIDTH-1:0] d_i,
    output logic [REG_WIDTH-1:0] q_o
);

logic [REG_WIDTH-1:0] data;

assign q_o = data;

always_ff @(posedge clk) begin
    if(~rst_n) begin
        data <= 0;
    end else if(load_i) begin
        data <= d_i;
    end else begin
        data <= data;
    end
end

endmodule
