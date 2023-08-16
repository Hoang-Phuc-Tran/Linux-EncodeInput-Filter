# encodeInput Utility

The `encodeInput` utility is a versatile Linux filter designed to convert assembled program data into S19 download file format. This tool enables seamless transfer of compiled code to embedded devices, enhancing your understanding of binary arithmetic, hexadecimal numbering, and file input/output in a UNIX/Linux environment. With support for various command-line switches, `encodeInput` offers flexible customization for transforming binary input into human-readable ASCII output, suitable for both S-Record and assembly file formats.

**Project Highlights:**
- Transform assembled program data into S19 download file format.
- Reinforce knowledge of binary arithmetic, hexadecimal numbering, and UNIX/Linux application programming.
- Support for command-line switches for customized data transformation.
- Generate human-readable ASCII output files for S-Record and assembly formats.

Explore the capabilities of `encodeInput` and unlock a powerful tool for your embedded software development workflow.

# encodeInput Utility

The `encodeInput` utility is a powerful Linux filter designed to convert assembled program data into S19 download file format. This utility is analogous to the ARM development environment, where code is compiled on a host computer and then transferred to the target ARM board.

## Project Overview

This project serves as a practical exercise to reinforce knowledge of binary arithmetic, hexadecimal numbering, file input/output (both ASCII and binary), and command-line processing. The utility enables the transformation of any binary input file into two human-readable ASCII output formats: S-Record files or assembly files for embedded software development.

## Getting Started

To use the `encodeInput` utility, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the project directory in the terminal.
3. Compile the program using your preferred C compiler.
4. Run the utility with optional command-line switches to customize its behavior.

## Command-Line Switches

The `encodeInput` utility supports the following command-line switches:

- `-iINPUTFILENAME`: Specifies the input file name. If not provided, data is read from standard input (stdin).
- `-oOUTPUTFILENAME`: Specifies the output file name. If not provided:
  - If the `-srec` switch is absent, output is written to an assembly file (input filename + ".asm").
  - If the `-srec` switch is present, output is written to an S-Record file (input filename + ".srec").
  - If no input or output file is specified, output is directed to standard output (stdout).
- `-srec`: Instructs the program to output in S-Record format. Without this switch, an assembly file output is generated.
- `-h`: Displays the program's usage statement and exits.

Invalid switches prompt the display of the usage statement and program termination. Input stream ends upon reaching the end-of-file marker (simulated using Ctrl-D).

## Examples

Here are some examples of valid command lines:

- `encodeInput -imyData.dat -omyData.srec -srec`: Converts 'dat' to 'myData.srec' as an S-Record file.
- `encodeInput -h`: Outputs the usage statement and exits.
- `encodeInput -omyData.asm`: Converts standard input into 'asm' as an assembly file.
- `encodeInput –srec -imyData.dat`: Converts 'dat' into 'myData.dat.srec' as an S-Record file.
- `encodeInput`: Converts standard input into Assembly-formatted standard output.
- `ls -l | encodeInput -odirectory.srec -srec`: Converts the piped standard input from `ls -l` into an S-Record file output in 'srec' format.

Note: The runtime switches can appear in any order on the command line.

## Project Structure

The solution for this utility follows recommended Linux development practices:

- The solution is modularized into separate source modules for clean code organization.
- The source code adheres to SET Coding Standards, featuring appropriate comments.
- The repository includes a makefile for easy compilation and building.
- The project directory structure adheres to the recommended Linux development directory structure.

## Getting Help

If you need assistance or have questions about using the `encodeInput` utility, please don't hesitate to reach out via GitHub issues.

## License

This project is licensed under the [MIT License](LICENSE).
