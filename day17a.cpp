#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Helper function to calculate combo operand value
int combVal(int operand, int A, int B, int C) {
    switch (operand) {
        case 0: case 1: case 2: case 3:
            return operand;
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
    }
}

std::string instr() {
    // Initial registers
    int A = 64751475, B = 0, C = 0;

    // Program: list of opcodes and operands
    std::vector<int> program = {2,4,1,2,7,5,4,5,1,3,5,5,0,3,3,0};

    // Instruction pointer and output
    int IP = 0;
    std::vector<int> output;

    // Simulation loop
    while (IP < program.size()) {
        int opcode = program[IP];
        int operand = program[IP + 1];

        switch (opcode) {
            case 0: // adv
                A /= std::pow(2, combVal(operand, A, B, C));
                break;
            case 1: // bxl
                B ^= operand;
                break;
            case 2: // bst
                B = combVal(operand, A, B, C) % 8;
                break;
            case 3: // jnz
                if (A != 0) {
                    IP = operand;
                    continue;
                }
                break;
            case 4: // bxc
                B ^= C; // Operand ignored
                break;
            case 5: // out
                output.push_back(combVal(operand, A, B, C) % 8);
                break;
            case 6: // bdv
                B = A / std::pow(2, combVal(operand, A, B, C));
                break;
            case 7: // cdv
                C = A / std::pow(2, combVal(operand, A, B, C));
                break;
        }

        // Move to the next instruction
        IP += 2;
    }

    // Convert output to comma-separated string
    std::string result;
    for (size_t i = 0; i < output.size(); ++i) {
        if (i > 0) result += ",";
        result += std::to_string(output[i]);
    }

    return result;
}

int main() {
    std::string result = instr();
    std::cout << result << std::endl;
}
