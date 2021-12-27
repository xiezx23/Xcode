`timescale 1ns / 1ps
//寄存器组
module RegisterFile(
        input CLK,              //时钟信号
        input Mwk,              //工作使能
        input immres,           //立即数直接写入信号
        input [4:0] rs1,        //rs1寄存器地址输入端口
        input [4:0] rs2,        //rs2寄存器地址输入端口
        input [4:0] WriteReg,   //rd输入地址
        input [31:0] AluOutput, //ALU输出
        input [31:0] extend,    //立即数扩展器输出
        input [31:0] Datain,    //存储器输出
        input [31:0] PC,        //当前PC值
        input [1:0] cmp,        //比较器输出
        input [1:0] RegDst,     //输入具体数据位选
        input RegWr,            //写使能信号，时钟下降沿触发写入
        output reg[31:0] DB,    //输入总线数据
        output [31:0] ReadData1, //rs1寄存器数据输出端口
        output [31:0] ReadData2  //rs2寄存器数据输出端口
    );

    reg [31:0] regFile[0:31]; //声明32个32位寄存器
    integer i;
    
    initial begin
        for (i = 0; i < 32; i = i+ 1) regFile[i] <= 0;//初始化  
    end

    assign ReadData1 = regFile[rs1];
    assign ReadData2 = regFile[rs2];

    always@(posedge CLK) //时钟上升沿写入
    begin
        if (Mwk) 
        begin
            if(immres & RegWr) begin
                regFile[WriteReg] = extend;
                DB = extend;
            end
            else begin
                if(RegWr)begin
                    case (RegDst)
                        2'b00: begin
                            regFile[WriteReg] = AluOutput;
                            DB = AluOutput;
                        end 
                        2'b01: begin
                            regFile[WriteReg] = Datain;
                            DB = Datain;
                        end 
                        2'b10: begin
                            regFile[WriteReg] = PC+4;
                            DB = PC+4;
                        end 
                        2'b11: begin
                            regFile[WriteReg][31:1] = 0;
                            regFile[WriteReg][0] = cmp[0];
                            DB[31:1] = 0;
                            DB[0] = cmp[0];
                            //$display("cmp:%d, db:%d",cmp,DB);
                        end
                    endcase
                end
            end
        end
        //$display("immres = %d ; in %d write %d",immres,WriteReg,regFile[WriteReg]);
    end
endmodule
