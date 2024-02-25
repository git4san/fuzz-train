<details markdown='1'>

<summary>Contents</summary>

1. [Drill Test on buggy- A simple example](#buggy)

</details>

<a name="buggy"></a>
## 1. Drill Test on Buggy (driller/buggy.c)

```sh
$ gcc -o buggy buggy.c
```
### In QEMU mode, we use regular gcc instead of afl-gcc for compiling the target program because QEMU instrumentation is applied at runtime, rather than at compile time like with AFL's native instrumentation.

### The purpose of using gcc is to compile the program with the necessary source code instrumentation for QEMU to perform dynamic analysis during runtime. This instrumentation is different from AFL's native instrumentation, which is applied by afl-gcc during compilation for AFL's fuzzing process.

### Once the program is compiled with gcc, AFL's QEMU mode (afl-qemu-trace) can then instrument the binary at runtime to track code coverage and guide the fuzzing process. This allows AFL to fuzz binaries that were compiled without AFL instrumentation, making it useful for fuzzing closed-source or third-party applications

## Check the compiled
```sh
$ echo 123456 | ./buggy
# No problem
$ echo 7/42a8 | ./buggy
# Segmentation fault (core dumped)
```

## Fuzz with AFL
```sh
$ mkdir -p workdir/input
$ echo 'init' > workdir/input/seed1
$ echo core | sudo tee /proc/sys/kernel/core_pattern
$ afl-fuzz -M fuzzer-master -i workdir/input/ -o workdir/output/ -Q ./buggy
# if qemu-trace path issue then set the path
$ export AFL_PATH="/home/fuzz/AFL/afl-2.52b"
```

###    -M fuzzer-master: This option specifies that AFL should operate in parallel fuzzing mode with the identifier "fuzzer-master." In parallel fuzzing mode, multiple instances of AFL can run simultaneously, each with its own identifier. This mode enables AFL to monitor directories for interesting inputs, which is important for integration with tools like Driller.

###    -i workdir/input/: Here, we specify the input directory for AFL, which is set to "workdir/input/." AFL will read the files in this directory once and add them to its queue of inputs to be tested and mutated during the fuzzing process.

###    -o workdir/output/: This option sets the output directory for AFL to "workdir/output/." The output directory stores all of AFL's state and results, including generated test cases, coverage data, and any crash reports.

###    -Q: This flag instructs AFL to use QEMU mode for fuzzing. QEMU mode involves running the target program within an instrumented QEMU emulator rather than directly on the host system's hardware. This allows AFL to fuzz programs for which the source code is not available, making it useful for testing closed-source or third-party applications.

## Unleash Driller along with AFL run

```sh
$ python run_driller.py ./buggy workdir/output/fuzzer-master
```




