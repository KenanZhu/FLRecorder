# FLRecorder

[English](README.md) | [中文](READMECN.md)

> [!NOTE]
> 该项目还处于试验阶段.

![FLRecorder_Logo](./doc/FLRecorder_CODE.png#pic_center)

![STARS](https://img.shields.io/github/stars/KenanZHu/FLRecorder.svg#pic_center) 
![ISSUES](https://img.shields.io/github/issues/KenanZHu/FLRecorder.svg#pic_center) 
![LICENSE](https://img.shields.io/github/license/KenanZHu/FLRecorder.svg#pic_center)

一款快速构建日志，管理日志的命令行软件

## 简介

这是一款开源软件。您可以自由使用、修改和分发它。\
但是，您必须包括原始作者的信息和原始源代码。

这是一款快速构建日志的软件。它可以：

1. 支持使用BLog记录简单消息。
2. 支持使用PLog记录项目消息。
3. 支持使用FLog快速构建日志。
4. 支持管理日志文件。

## 使用

这是一个命令行界面（CLI）程序。所有的命令都是小写的，\
任何不同的命令格式都将被拒绝。以下是所有的命令列表：

     命令如下：
       FLRecord/base> fast [-cmd] [arg]

       $[-cmd] $[arg]    $command

        [-help]           获取帮助。
        [-quit]           退出程序。
        [-ver]            获取程序版本。
        [-init]           初始化工作文件夹。
        [-new]            添加新的日志文件。
           |____[str]     <可选> 日志类型
           |____[str]     日志文件名
        [-rm]             删除日志文件。
           |____[str]     日志文件名
        [-add]            添加日志记录。
           |____[str]     日志文件名
           |____[str]     新的日志记录
        [-del]            删除日志记录。
           |____[str]     日志文件名
           |____[str]     删除的日志记录
        [-show]           显示所有日志列表。
           |____[str]     <可选> 日志文件名
        [-find]           查找日志文件。
           |____[str]     日志文件名

### 命令介绍

#### fast -help

此命令将显示所有命令。

#### fast -quit

此命令将退出程序。

#### fast -ver

此命令将显示程序版本。

#### fast -init

此命令将初始化工作文件夹。
如果工作文件夹已经存在，程序将搜索工作文件夹中的所有存在文件。
将有效日志文件添加到日志索引列表中。

#### fast -new [str] [str]

此命令将在工作文件夹中创建一个新的日志文件。与此同时，它接受两个参数。
第一个参数是日志类型，这里是一些例子：

``fast -new -b example.log``
``fast -new -p example.plog``
``fast -new -f example.flog``

第二个参数是日志文件名。当存在第一个参数时，日志格式必须与扩展名匹配，
否则程序将不做处理。省略第一个参数时，日志格式将默认为BLog。

#### fast -rm [str]

此命令将从工作文件夹中删除一个文件。与此同时，它接受一个参数。
这个参数是工作文件夹中的任何文件名。

#### fast -add [str] [str]

NOT COMPLETE

#### fast -del [str] [str]

NOT COMPLETE

#### fast -show [str]

此命令将显示所有日志列表。
如果您想显示特定的日志文件，您可以将日志文件名作为参数。
如果您想显示所有日志列表，您可以留空参数。

#### fast -find [str]

此命令将在工作文件夹中查找日志文件。与此同时，它接受一个参数。
这个参数是日志文件名。

## 构建

### Windows

这是一款用C/C++20编写的软件。我们建议您\
使用Visual Studio 2022来构建它。

如果出现警告，您可以尝试在解决方案配置中添加以下\
预处理器定义

``_CRT_SECURE_NO_WARNINGS``
``_CRT_NONSTDC_NO_DEPRECATE``

### Linux

我们使用CMake来构建Linux版本的FLRecorder。准确来说\
是Ubuntu 24.10。通过{src}文件夹下的文件{CMakeLists.txt}\
使用以下命令来构建：

``mkdir build``
``cd build``
``cmake ..``
``cmake --build .``

### MacOS

通常来说，MacOS的构建和Linux的构建是一样的。不过我们还\
未进行测试。如果您在MacOS上遇到问题，请提交issue告知我们。

## 联系

作者 : KenanZhu (Nanoki)\
Email  : <nanoki_zh@163.com>