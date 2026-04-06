# Yash - Yet Another Shell

Yash is a lightweight, Unix-like shell implemented in C. 

> **WARNING:** This project was created primarily for **learning purposes**. It is not intended for production use and should be used with caution. 

I am very happy to receive **contributions**! If you find a bug or have an idea for a feature, feel free to open an issue or submit a pull request.

## Current Features

Yash already supports several core shell functionalities:

- **Command Execution:** Run any standard Unix command (e.g., `ls`, `grep`, `mkdir`).
- **Pipes (`|`):** Support for multi-stage command piping.
- **Redirection:**
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Output append (`>>`)
- **Logical Operators:** Conditional execution using `&&` and `||`.
- **Built-in Commands:** 
  - `cd`: Change directory.
  - `exit`: Terminate the shell.
- **Environment Variables:** Basic expansion of variables (e.g., `$HOME`, `$PATH`).
- **Interactive Interface:** 
  - Custom prompt (`Yash> `).
  - Command history and line editing via `readline`.
- **Signal Handling:** Gracefully handles `SIGINT` (Ctrl+C).

## Roadmap

The project is still under active development. Planned future improvements include:

- **Lua Configuration:** Integration of a configuration file written in **Lua** for flexible customization.
- **POSIX Compliance:** Moving towards stricter adherence to POSIX standards for better compatibility.
- **Job Control:** Implementation of background and foreground process management.

## Getting Started

### Prerequisites

You will need a C compiler (like `gcc`) and the `readline` library.

### Building

You can build the project using the provided `Makefile`:

```bash
make
```

### Running

Once built, you can start the shell by running:

```bash
./yash
```

## License

This project is licensed under the **GNU General Public License v3.0**. See the [LICENSE](LICENSE) file for details.
