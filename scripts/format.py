# gemini goat
# opcode, addressing mode, instruction, cycles, pagecross

with open("input.txt", "r") as input_file, open("output.txt", "w") as out:
    for line in input_file:
        line = line.strip()
        if not line or line.startswith("#"):
            continue  # Skip empty lines or header comments

        # Clean each token automatically
        tokens = [token.strip() for token in line.split(",")]

        if len(tokens) < 4:
            continue  # Skip malformed lines

        op = tokens[0].upper()
        am = tokens[1].upper()
        ins = tokens[2].upper()
        cycles = tokens[3]

        # Check if 5th element exists and is "true"
        has_page_cross = len(tokens) >= 5 and tokens[4].lower() == "true"

        if has_page_cross:
            out.write(f"arr[0x{op}] = {{AM::{am}, INS::{ins}, {cycles}, true}};\n")
        else:
            out.write(f"arr[0x{op}] = {{AM::{am}, INS::{ins}, {cycles}}};\n")
