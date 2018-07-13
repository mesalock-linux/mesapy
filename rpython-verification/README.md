# The Formal Verification on RPython Backend

Mesapy aims to formally verify the memory safety of Rpython C backend programs. It utilizes three of state-of-art verification tools, Seahorn, Smack and TIS to prove conclusively
that the memory safety issues can never occur. 

The memory safety issues in our current checks include

* Buffer overflow
* Buffer over-read
* Null pointer dereference
* Memory leak 

Seahorn leverages the SMT solver and Abstract Interpretation techniques to check memory safte issues:

	http://seahorn.github.io/blog/

SMACK translates the LLVM compiler's popular intermediate representation (IR) into the Boogie intermediate verification language (IVL), and leverages the Boogie and Corral verifiers for memory safety checks.

	https://github.com/smackers/smack

TrustInSoft Analyzer uses formal methods to deliver mathematical guarantees. With an extensible framework that enables collaboration between different formal methods, TrustInSoft Analyzer can mathematically guarantee that a given flaw is not present in your source code.

	https://trust-in-soft.com/

