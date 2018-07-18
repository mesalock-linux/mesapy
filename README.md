# MesaPy: A Memory-Safe Python Implementation based on PyPy

MesaPy is a memory-safe Python implementation based on PyPy. In addition to
PyPy's distinct features -- speed, memory usage, compatibility and stackless,
MesaPy mainly focuses on improving its security and memory safety. On top of
the enhancements, we also bring MesaPy into Intel SGX to write memory-safe
applications running in the trusted execution environment.

We achieve the memory-safety promise through various methods: hardening
RPython's type system (RPython is the language for writing PyPy), modifying
PyPy/RPython's libraries, and verifying the RPython's libraries as well as its
interpreter/JIT backend. Overall, there are four most notable security
features of MesaPy:

- **Memory safety**: To provide a memory-safe runtime, MesaPy replaces external
  libraries written in C, which could introduce memory issues, with Rust, a
  memory-safe programming language. This guarantees the memory safety across
  all libraries including those written in Python, but also external libraries.

- **Security hardening**: PyPy is implemented with RPython, a statically-typed
  language with translation and support framework. We also enhanced
  memory-safety of RPython through hardening RPython's type system, i.e., the
  RPython Typer. For example, we improve RPython's list with runtime index check
  to avoid arbitrarily list read/write during PyPy's implementation.

- **Formal verification**: Some code in RPython's libraries and its
  interpreter/JIT backend are still written in C, which may contain potential
  memory bugs. To prove the memory safety of RPython, we aim to formally
  verify its libraries and backend written in C using state-of-the-art
  verification tools.

- **SGX support**: With the memory safety of MesaPy, we also port it to
  Intel SGX, which is a trusted execution environment to provide integrity and
  confidentiality guarantees to security-sensitive computation. Developers now
  can easily use MesaPy to implement SGX applications without worrying about
  memory issues.

More details about each features, roadmap, building process can be found here:
[https://docs.mesapy.org/](https://docs.mesapy.org/)

# Getting started

## Building MesaPy from source

Building MesaPy from source is very simple, you can simply use the docker provided
by MesaLock Linux and run `make pypy-c`. The detailed steps are explained in the
[documentation](https://docs.mesapy.org/building-from-source.html).

```
$ docker run --rm -it -v$(pwd):/mesapy -w /mesapy mesalocklinux/build-mesalock-linux make pypy-c
```

# Contributing

We still have some working-in-progress sub-projects. We are very happy if you
are interested to help out. Here are several topics you can get involved:
  - porting Rust libraries into MesaPy and replacing previous external C libraries
  - helping to verifying "unsafe" components using current the state-of-art
    verification tools
  - improving MesaPy in SGX (bringing in useful libraries in normal world into SGX)
For each topic, we provided detailed instructions to get started. Feel free to
pick an interesting one and improve MesaPy and send us pull requests on the GitHub.
If you find it a little difficult, you can also talk to our maintainers for help.

# Maintainers

  - **Memory-safety and security hardening**: Mingshen Sun
  - **Formal verification**: Qian Feng
  - **SGX support**: Huibo Wang and Yu Ding

# Steering Committee

  - Tao Wei
  - Yulong Zhang

# License

MesaPy is provided under the 3-Clause BSD license. MesaPy is built upon PyPy,
for a detailed license, see the LICENSE file.
