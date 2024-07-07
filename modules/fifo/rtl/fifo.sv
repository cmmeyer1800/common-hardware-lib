
module fifo #(
    parameter WIDTH = 32,
    parameter DEPTH = 16,
    parameter ADDR_WIDTH = $clog2(DEPTH)
) (
    input logic clk,
    input logic rst_n,
    input logic enqueue,
    input logic dequeue,
    input logic [WIDTH-1:0] data_in,
    output logic [WIDTH-1:0] data_out,
    output logic full,
    output logic empty
);

logic [WIDTH-1:0] mem [DEPTH-1:0];

// 1 bit larger addr than necessary for circular functionality
logic [ADDR_WIDTH:0] wr_ptr;
logic [ADDR_WIDTH:0] rd_ptr;

assign full = (wr_ptr[ADDR_WIDTH-1:0] == rd_ptr[ADDR_WIDTH-1:0]) && (wr_ptr[ADDR_WIDTH] != rd_ptr[ADDR_WIDTH]);
assign empty = (wr_ptr[ADDR_WIDTH-1:0] == rd_ptr[ADDR_WIDTH-1:0]) && (wr_ptr[ADDR_WIDTH] == rd_ptr[ADDR_WIDTH]);

always @(posedge clk) begin
    if (!rst_n) begin
        wr_ptr <= 0;
        rd_ptr <= 0;
    end else begin
        if (enqueue && ~full) begin
            mem[wr_ptr[ADDR_WIDTH-1:0]] <= data_in;
            wr_ptr <= wr_ptr + 1;
        end
        if (dequeue && ~empty) begin
            data_out <= mem[rd_ptr[ADDR_WIDTH-1:0]];
            rd_ptr <= rd_ptr + 1;
        end
    end
end

endmodule
