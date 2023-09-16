module register #(
    parameter WIDTH = 32
) (
    input logic clk,
    input logic rst_n,
    input logic load_i,
    input logic [WIDTH-1:0] d_i,
    output logic [WIDTH-1:0] q_o
);

logic [WIDTH-1:0] data;

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
