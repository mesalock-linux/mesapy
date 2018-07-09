# MesaPy: A Memory-safe Python Implementation based on PyPy 

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
  verified its libraries and backend written in C using state-of-the-art
  verification tools.

- **SGX support**: With the memory safety of MesaPy, we also port it to
  Intel SGX, which is a trusted execution environment to provide integrity and
  confidentiality guarantees to security-sensitive computation. Developers now
  can easily use MesaPy to implement SGX applications without worrying about
  memory issues.

# Maintainers

  - **Memory-safety and security hardening**: Mingshen Sun `<mssun@mesalock-linux.org>`
  - **Formal verification**: Qian Feng
  - **SGX support**: Huibo Wang and Yu Ding

# Steering Committee

  - Tao Wei
  - Yulong Zhang

# License

MesaPy is provided under the 3-Clause BSD license. For a copy, see the LICENSE file.
