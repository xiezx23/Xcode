`timescale 1ns / 1ps

module SingleCycleCPU(
        input CLK,
        input Reset,
        output [31:0] curPC,      //当前地址
        output [31:0] nextPC,     //下条地址
        output [4:0] rs1,         //rs1地址
        output [31:0] ReadData1,  //rs1内数据
        output [4:0] rs2,         //rs2地址
        output [31:0] ReadData2,  //rs2内数据
        output [31:0] AluOutput,  //alu计算结果
        output [31:0] DB,         //DB总线数据

        output [31:0] instr,      //指令
        output [7:0] op,          //操作码
        output [4:0] rd          //rd地址
    );

    wire[24:0] imm;        //指令分割imm段
    wire [31:0] extend;    //立即数
    wire [2:0] funct3;
    wire [6:0] funct7;
    wire [31:0] DataOut;   //存储器读数据
    wire PCSrc;
    wire [2:0] AluOp;
    wire AluSrc1;
    wire AluSrc2;
    wire RegWr;
    wire RegDst;
    wire [2:0] ExtSel;
    wire Sign;
    wire [1:0] Digit;
    wire DataWr;
    wire [1:0] cmp;
    wire immres;

    PC pc(
        .CLK(CLK),       //时钟
        .Reset(Reset),   //是否重置地址。0-初始化PC
        .PCSrc(PCSrc),   //数据选择器输入
        .AluOutput(AluOutput), //ALU计算结果
        .curPC(curPC),    //当前指令的地址
        .nextPC(nextPC)   //新地址
    );

    ControlUnit control(
        .cmp(cmp),        //比较器结果
        .op(op),          //操作码
        .funct3(funct3),  //3位功能码
        .funct7(funct7),  //7位功能码
        .PCSrc(PCSrc),    //PC下一步取值方式
        .AluOp(AluOp),    //ALU操作
        .Alu1Src(AluSrc1),   //ALU1口
        .Alu2Src(AluSrc2),   //ALU2口
        .RegDst(RegDst),  //Rd位选
        .RegWr(RegWr),    //Rd写使能
        .ExtSel(ExtSel),  //立即数扩展式
        .Sign(Sign),      //立即数符号扩展
        .Digit(Digit),    //读写位数
        .DataWr(DataWr),  //存储器写使能
        .immres(immres)   //rd是否选择imm直接作为数据
    );

    ALU alu(
        .ALUSrc1(AluSrc1),
        .ALUSrc2(AluSrc2),
        .ReadData1(ReadData1),
        .ReadData2(ReadData2),
        .extend(extend),
        .PC(curPC),
        .AluOp(AluOp),
        .AluOutput(AluOutput)
    );

    InsMEM imsmem(
        .curPC(curPC),
        .op(op),
        .funct3(funct3),
        .funct7(funct7),
        .rs1(rs1),
        .rs2(rs2),
        .imm(imm)
    );

    Extend ext(
        .imm(imm),   //立即数
        .Sign(Sign),         //扩展符号
        .ExtSel(ExtSel),       //扩展方式
        .extend(extend)
    );

    RegisterFile regfile(
        .CLK(CLK),            //时钟
        .immres(extend),         //立即数直接写入信号
        .rs1(rs1),      //rs1寄存器地址输入端口
        .rs2(rs2),      //rs2寄存器地址输入端口
        .WriteReg(rd),
        .AluOutput(AluOutput),  //ALU输出
        .imm(imm),      //imm扩展器输出
        .Datain(DataOut),   //存储器输出
        .PC(curPC),       //当前PC值
        .cmp(cmp),      //比较器输出
        .RegDst(RegDst),    //输入具体数据位选
        .RegWr(RegWr),               //写使能信号，为1时在时钟边沿触发写入
        .DB(DB),     //输入总线数据
        .ReadData1(ReadData1),  //rs1寄存器数据输出端口
        .ReadData2(ReadData2)   //rs2寄存器数据输出端口
    );

    DataMEM datamem(
        .DataWr(DataWr), //存储器写使能
        .Digit(Digit), //读写位数，00为8位，01为16位，10为32位
        .CLK(CLK),     //时钟下降沿写入数据
        .DAddr(AluOutput),  //写入地址
        .DataIn(ReadData2), //写入数据
        .DataOut(DataOut) //输出数据
    );

endmodule
