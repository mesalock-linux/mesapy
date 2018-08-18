<p align="center"><img src="img/logo.png" height="86" /></p>

# MesaPy: 一个安全且快速的 Python

[![Build Status](https://ci.mesalock-linux.org/api/badges/mesalock-linux/mesapy/status.svg)](https://ci.mesalock-linux.org/mesalock-linux/mesapy)

[English](README.md) | 中文

Python 是现代大数据/机器学习的重要基础，但是 Python 包含超过 30 万行 C 代码，含
有很多安全漏洞和隐患，在高安全高可靠性场景下面临着严重的安全威胁。MesaPy 是一个
**内存安全**的 Python 实现，基于 PyPy 并继承了 PyPy 显著的特点：卓越的运行速度
（得益于 JIT 编译器）、高效的内存使用率、良好的兼容性、以及强大的并发处理（支持
stackless 协程）。除此之外，MesaPy 专注于安全，通过 **1. 使用内存安全语言重写外
部库**、**2. 加强 RPython 类型系统保障内存安全**、**3. 形式化验证保障内部 C 代码
的内存安全**等方法，全面提升 Python 解释器的安全性，避免内存问题引发的高危安全漏
洞。基于这些安全特性，MesaPy 也支持**运行在 Intel SGX 中**，开发者可以使用
Python 轻松地开发 SGX 应用，运行于可信运行环境中。

## MesaPy 四大安全特性

MesaPy 拥有**内存安全**、**安全增强**、**形式化验证**、**SGX 支持**四大安全特性，
以下是详细介绍：

- **内存安全**： 因为 MesaPy 基于由 RPython 实现的 PyPy，相比 CPython，多数内置
  的 Python 库都具有相对安全的运行时。但是 PyPy 仍然依赖由非内存安全的 C 编写的
  外部库，这些外部库会引入潜在的内存安全问题。为了解决这些外部依赖中隐藏的内存安
  全问题，我们使用内存安全语言 Rust 重写了外部依赖库。同时，我们努力兼容原有的
  API，确保开发者无需修改或少量修改，就可以无缝的享受 Rust 带来的内存安全保证。
- **安全增强**：MesaPy 解释器由 RPython 语言实现，RPython 与 Python 语法类似，但
  是为强类型语言（通过 RPython 翻译器翻译为后端中间代码后编译执行）。其中
  RPython 的 list 类型没有运行时数组越界的检查，这会导致使用中出现内存问题。我们
  通过修改 RPython 的 list 类型，使其可以运行时动态检查数组访问越界，保证数组访
  问的内存安全。
- **形式化验证**：MesaPy 项目中的 Python 解释器不可避免的使用了 C 代码，为了保证
  这些代码的安全性，我们使用多款形式化验证工具对其进行内存安全属性的验证。其中包
  括缓冲区溢出（buffer overflow, buffer over-read），空指针解引用（null pointer
  dereference）以及内存泄漏（memory leakage) 问题。现阶段，我们通过使用形式化验
  证的方法，验证 RPython 的翻译器本身，JIT 编译器后端，以及 RPython library 中部
  分的 C 代码。现在验证还在进行中，感兴趣的朋友可以根据文档尝试验证相关函数，帮
  助我们完善 MesaPy 的形式化验证。验证所需的 mock 函数，验证脚本，以及验证初步结
  果都已在开源代码中。
- **SGX 支持**：在以上三点安全保证的基础之上，MesaPy 也同样支持 Intel SGX（一个
  可信的执行环境）。我们通过对 MesaPy 的精简和对 Python 内置库的改造，使开发者能
  够使用 Python 写出运行在 SGX 里的应用。MesaPy 对于 SGX 的支持不仅加速了 SGX 应
  用的开发效率，同时也能保证运行在可信执行环境中应用的内存安全。针对 SGX 的支持
  还在开发当中，我们已经拥有一个可在 SGX 里执行的 Python 解释器，对于常用库的移
  植工作仍在进行，敬请期待后续更新。

MesaPy 项目仍在进行中，以上安全特性正在不断优化，代码都已开源在 GiHub，我们希望
与开源社区共同构建 MesaPy 的未来。对于 MesaPy 更多的介绍，包括功能、路线图、安全
特性的详细介绍等相见：

- GitHub 开源项目地址：https://github.com/mesalock-linux/mesapy
- 官方文档：https://docs.mesapy.org

## 系统架构

MesaPy 增强了 PyPy 的安全性，相比 CPython（也就是我们经常提到的 Python），整体安
全性有了本质的提升，MesaPy 的系统架构可以通过下面这张图概括。图中描述了如何构建
一个面向内存安全的 Python 实现，红色部分表示非内存安全模块，蓝色部分表示内存安全
模块。MesaPy 通过多种方式完善 Python 中非内存安全的部分。

<p align="center">
<img src="img/design.png" width="600"/>
</p>

首先，CPython 的主要模块 Python 解释器和 Python Modules 都是由非内存安全代码 C
编写（大约有 30 万行代码），如此庞大的代码量非常容易引入内存安全漏洞。可以查看
CPython 相关的安全漏洞，大部分都是由缓冲区溢出这类内存安全问题造成的（参考链接：
https://www.cvedetails.com/vulnerability-list/vendor_id-10210/product_id-18230/Python-Python.html
）。

其次，PyPy 使用 RPython 重写了 Python 解释器和库，这大大缓解了 CPython 带来的内
存安全问题。但是，PyPy 仍存在三个存在内存安全问题的薄弱点：1. 部分的 RPython 翻
译器，JIT 编译器库是由 C 编写（大约一千行）；2. RPython 的 list 类型没有运行时数
组越界检查（参考链接：
https://rpython.readthedocs.io/en/latest/rpython.html#exception-rules）；3. 部分
RPython 提供给 PyPy 使用的第三方库是有 C 编写的。

MesaPy 通过形式化验证、RPython 类型安全增强、使用内存安全语言重写非安全库等方式
弥补了 PyPy 潜在的安全问题，努力提供完整的内存安全保证。

## 性能测试

我们选取了 19 个 Python 的性能测试点针对 MesaPy、PyPy 和 Python 2.7 分别进行测试，
其性能测试结果如图。横轴表示 19 个性能测试点的测试脚本名称，纵轴表示测试点运行时
间相比 baseline (Python 2.7.12) 性能的 speedup（取运行 10 次的平均值，对数坐标系，
测试机器为 Intel Core i7-8086K CPU, 32G RAM），蓝色为 MesaPy 的测试结果，黑色为
PyPy 的测试结果。

<p align="center">
<img src="img/benchmarks.png" width="600"/>
</p>

如上图展示，MesaPy 与 PyPy 的性能相当，相比 Python 2.7 有大幅度的提升。**多数测
试结果都有 10x 左右的性能提升**，在某些测试点中（比如 `gcbench.py` 和
`spectral_norm`）会有 30x 的性能提升。如此显著的性能提升得益于 JIT 编译器以及高
效的内存垃圾回收机制。

用于性能测试的测试脚本已经开源在 GitHub:
https://github.com/mesalock-linux/mesapy-benchmarks，更多更详细的性能对比数据也
可以参考 PyPy Speed Center: http://speed.pypy.org/

## 如何使用 MesaPy

MesaPy 可以在多种场景下使用，如运行大数据计算、训练机器学习模型等。我们提供多种渠道下载使用 MesaPy：

1. 下载[预编译的 MesaPy 包](https://github.com/mesalock-linux/mesapy/releases)使用 MesaPy
2. 使用 Docker 体验 MesaPy：`docker run --rm -it mesalocklinux/mesalock-linux:latest mesapy`
3. 从源代码编译 MesaPy

MesaPy 在 GitHub 的 README 上提供了详细编译步骤，详见：https://github.com/mesalock-linux/mesapy

## 加入 MesaPy 项目

MesaPy 项目及其子项目选择使用 BSD 开源协议下开源。BSD 开源协议是一个给于使用者很
大自由的协议，我们希望有更多的人来使用 MesaPy，提升 Python 语言生态的安全。同时，
安全生态的可持续发展也离不开开源社区、工业界、学术界的共同参与，我们非常欢迎大家
的贡献和支持。支持 MesaPy 的途径有很多，例如：

- 尝试使用 MesaPy，给我们反馈使用感受和改进的建议等
- 参与贡献 MesaPy 的开发流程、完善文档、帮助解答常见问题等
- MesaPy 对于第三方库的支持的工作还在进行中，我们希望社区的支持，尝试把内存安全
  语言编写的第三方库移植到 MesaPy 中
- MesaPy 的形式化验证工作仍在进行中，我们开源了验证手段和现阶段结果，希望社区可
  以参与进来，与我们一起使用形式化验证方法和工具验证 MesaPy 中的“非安全”组件
- 帮助提高 MesaPy 对于 SGX 的支持，比如把 normal world 中常用库移植到 SGX 中

如果你对于 MesaPy 感兴趣，我们提供了详细的文档帮助你了解 MesaPy 的设计和代码结构。
同时也可以参与社区讨论，通过提交 issue，pull request 等方式和我们交流。

**参考链接：**

- MesaPy: https://github.com/mesalock-linux/mesapy
- PyPy Speed Center: http://speed.pypy.org/
- RPython Language (Exception rules): https://rpython.readthedocs.io/en/latest/rpython.html#exception-rules
