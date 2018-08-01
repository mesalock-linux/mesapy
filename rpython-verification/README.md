# Formal Verification of MesaPy: Towards Verifying RPython Translator/JIT and Libraries

Since there are still several unavoidable C code in the MesaPy's codebase, we
seek to formally verify these code to guarantee their memory safety. These C
code are located in RPython's translator/JIT backends and its libraries.
To cross validate our verification results, We utilize three state-of-the-art
verification tools --
[Seahorn](http://seahorn.github.io/blog/),
[Smack](https://github.com/smackers/smack), and
[TIS](https://trust-in-soft.com/) to
prove conclusively that the memory safety issues can never occur.

The memory safety issues in our current checks include

* Buffer overflow
* Buffer over-read
* Null pointer dereference
* Memory leak 

Here are three verification tools:

  - **Seahorn**: leverages the SMT solver and Abstract Interpretation techniques to
    check memory safte issues. http://seahorn.github.io/blog/

  - **SMACK**: translates the LLVM compiler's popular intermediate representation
    (IR) into the Boogie intermediate verification language (IVL), and leverages
    the Boogie and Corral verifiers for memory safety checks.
    https://github.com/smackers/smack

  - **TrustInSoft Analyzer**: uses formal methods to deliver mathematical
    guarantees. With an extensible framework that enables collaboration between
    different formal methods, TrustInSoft Analyzer can mathematically guarantee
    that a given flaw is not present in your source code.
    https://trust-in-soft.com/
