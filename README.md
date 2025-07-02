
# Pipex

> A 42 School project that simulates shell-like piping and redirection in C.

---

## ✅ Project Overview

`pipex` replicates the behavior of shell commands connected by pipes (`|`), including input/output redirection.  
It executes two commands in sequence, piping the output of the first into the second.

Example shell behavior:

```bash
< infile cmd1 | cmd2 > outfile
````

is executed by:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

---

## ⚙️ How It Works

1. Open `infile` for reading and `outfile` for writing (create or overwrite).
2. Create a pipe, then fork a child process for `cmd1`:

   * Redirect `stdin` to `infile`, `stdout` to pipe's write end.
3. Parent forks another child for `cmd2`:

   * Redirect `stdin` to pipe’s read end, `stdout` to `outfile`.
4. Execute both commands via `execve()`, handling paths via `PATH`.
5. Parent closes unused descriptors and waits for both children.

---

## 🛠️ Build & Usage

```bash
git clone https://github.com/mouchtach/pipex.git
cd pipex
make
./pipex infile "grep foo" "wc -l" outfile
```

Creates `outfile` containing the number of lines in `infile` that include "foo".

---

## 📂 File Structure

* `pipex.c` – main program, `fork_pipes` logic
* `child.c` / `child_utils.c` – setup and exec functions for each child process
* `utils.c` – path search, error handling, helpers
* `Makefile` – compilation rules
* `README.md` – documentation

---

## 🧪 Testing Suggestions

Try edge cases like:

* Invalid `infile` or `outfile`
* Failed commands (e.g., `cmd1` not found)
* Commands requiring absolute paths
* Using `""` to simulate commands like `cat`

---

## 🧠 Learning Goals

* Mastering `fork()`, `pipe()`, `dup2()`, and `execve()`
* Handling file descriptors and I/O redirection
* Robust error handling and process control


