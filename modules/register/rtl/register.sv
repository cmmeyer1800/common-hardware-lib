module register #(
    parameter WIDTH = 32
) (
    input logic clk,
    input logic rst_n,
    input logic load_i,
    input logic [WIDTH-1:0] d_i,
    output logic [WIDTH-1:0] q_o
);

logic [WIDTH-1:0] data, new_data;

assign q_o = data;

always_ff @(posedge clk) begin
    if(rst_n) begin
        data <= 0;
    end else begin
        data <= new_data;
    end
end

always_comb begin : choose_data_next
    if(load_i) begin
        new_data = d_i;
    end else begin
        new_data = data;
    end
end

endmodule
