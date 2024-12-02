# Open the input and output files
input_file_path = "inputsday2.txt"  # Replace with the path to your input file
output_file_path = "inputsday2new.txt"  # Replace with the desired path for your output file

# Read the input file, process each line, and write to the output file
with open(input_file_path, "r") as input_file:
    with open(output_file_path, "w") as output_file:
        for line in input_file:
            # Add a comma to the end of each line and write to the output file
            output_file.write(line.strip() + ",\n")

print(f"Processed file saved to {output_file_path}")
