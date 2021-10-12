#include <iostream>
#include <fstream>
#include "header/compiler.hpp"

#define MEM_CAPACITY 640000

CComplier::CComplier(std::string fileName, std::queue<Token> tokens) {
    // Set m_strFileName to fileName without .corth extension
    this->m_strFileName = fileName.substr(0, fileName.size() - 6);
    this->m_qTokens = tokens;
}

void CComplier::GenerateNasm() {
    std::cout << "[LOG] Generating " << this->m_strFileName << ".asm" << std::endl;

    // Open .asm file and clear contents
    std::ofstream out(this->m_strFileName + ".asm",
        std::ofstream::out | std::ofstream::trunc);

    // Define a print function to make printing easier
    // Source: https://github.com/tsoding/porth/blob/master/porth.py#L1043
    out << "BITS 64\n";
    out << "segment .text\n";
    out << "print:\n";
    out << "\tmov\tr9, -3689348814741910323\n";
    out << "\tsub\trsp, 40\n";
    out << "\tmov\tBYTE [rsp+31], 10\n";
    out << "\tlea\trcx, [rsp+30]\n";
    out << ".L2:\n";
    out << "\tmov\trax, rdi\n";
    out << "\tlea\tr8, [rsp+32]\n";
    out << "\tmul\tr9\n";
    out << "\tmov\trax, rdi\n";
    out << "\tsub\tr8, rcx\n";
    out << "\tshr\trdx, 3\n";
    out << "\tlea\trsi, [rdx+rdx*4]\n";
    out << "\tadd\trsi, rsi\n";
    out << "\tsub\trax, rsi\n";
    out << "\tadd\teax, 48\n";
    out << "\tmov\tBYTE [rcx], al\n";
    out << "\tmov\trax, rdi\n";
    out << "\tmov\trdi, rdx\n";
    out << "\tmov\trdx, rcx\n";
    out << "\tsub\trcx, 1\n";
    out << "\tcmp\trax, 9\n";
    out << "\tja \t.L2\n";
    out << "\tlea\trax, [rsp+32]\n";
    out << "\tmov\tedi, 1\n";
    out << "\tsub\trdx, rax\n";
    out << "\txor\teax, eax\n";
    out << "\tlea\trsi, [rsp+32+rdx]\n";
    out << "\tmov\trdx, r8\n";
    out << "\tmov\trax, 1\n";
    out << "\tsyscall\n";
    out << "\tadd\trsp, 40\n";
    out << "\tret\n";
    out << "global _start\n";
    out << "_start:\n";
    out << "\tmov [args_ptr], rsp\n";

    // Grab the size before looping through so we can reuse it later
    int tokensSize = this->m_qTokens.size();
    int addrNum = 0;

    while (!this->m_qTokens.empty()) {
        out << "addr_" << addrNum << ":\n";
        switch (this->m_qTokens.front().m_Type) {
        case TokenType::INT:
            out << "\t;; -- push int " << this->m_qTokens.front().m_strValue << " --\n";
            out << "\tmov rax, " << this->m_qTokens.front().m_strValue << "\n";
            out << "\tpush rax\n";
            break;
        case TokenType::PLUS:
            out << "\t;; -- plus --\n";
            out << "\tpop rax\n";
            out << "\tpop rbx\n";
            out << "\tadd rax, rbx\n";
            out << "\tpush rax\n";
            break;
        case TokenType::INTRINSIC:
            switch (this->m_qTokens.front().m_Intrinsic) {
            case Intrinsics::PRINT:
                out << "\t;; -- print --\n";
                out << "\tpop rdi\n";
                out << "\tcall print\n";
                break;
            default:
                //std::cout << "unreachable\n";
                break;
            }
        default:
            //std::cout << "unreachable\n";
            break;
        }

        addrNum++;
        this->m_qTokens.pop();
    }

    out << "addr_" << tokensSize << ":\n";
    out << "\tmov rax, 60\n";
    out << "\tmov rdi, 0\n";
    out << "\tsyscall\n";
    out << "segment .data\n";
    out << "segment .bss\n";
    out << "args_ptr: resq 1\n";
    out << "mem: resb " << MEM_CAPACITY << "\n";
}

void CComplier::CompileNasm() {
    std::string cmd = "";
    cmd = "nasm -felf64 " + this->m_strFileName + ".asm";
    system(cmd.c_str());
    cmd = "ld -o " + this->m_strFileName + " " + this->m_strFileName + ".asm";
    system(cmd.c_str());
}
