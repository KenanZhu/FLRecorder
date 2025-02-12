# FLRecorder

[中文](READMECN.md) | [English](README.md)

> [!NOTE]
> This project is still in experimental phase.

![FLRecorder_Logo](./doc/FLRecorder_CODE.png#pic_center)

![STARS](https://img.shields.io/github/stars/KenanZHu/FLRecorder.svg#pic_center) 
![ISSUES](https://img.shields.io/github/issues/KenanZHu/FLRecorder.svg#pic_center) 
![LICENSE](https://img.shields.io/github/license/KenanZHu/FLRecorder.svg#pic_center)\

A CLI software which can fastly build log files and manage them.

## Brief

This is an open source software. You are free to use,\
modify, and redistribute it. However, you must include\
the original author's information and the original\
source code.

This program is a fast log recording constructor.It can :

1. Support record simple message by BLog.
2. Support record project message by PLog.
3. Support recorder fast construct by FLog.
4. Support manage log files.

## Usage

This is a Command Line Interface (CLI) program.\
the command are all be lowercase, any different\
is reject. here are commands:

     commands are like:
       FLRecord/base> fast [-cmd] [arg]
 
       $[-cmd] $[arg]    $command
 
        [-help]           Get help.
        [-quit]           Exit the program.
        [-ver]            Get program version.
        [-init]           Init the workfolder.
        [-new]            Add a new log file.
           |____[str]     <optional> log type.
           |____[str]     log file name.
        [-rm]             Remove a log file.
           |____[str]     log file name.
        [-add]            Add a log record.
           |____[str]     log file name.
           |____[str]     new log record.
        [-del]            Delete a log record.
           |____[str]     log file name.
           |____[str]     deleted log record.
        [-show]           Show all logs list.
           |____[str]     <optional> log file name
        [-find]           Find log file.
           |____[str]     log file name.

### Command Introduction

#### fast -help

This command will show all commands.

#### fast -quit

This command will exit the program.

#### fast -ver

This command will show the program version.

#### fast -init

This command will init the workfolder.
If the workfolder is already exist, program
will search all exist files in the workfolder.
Add vaild log file in the log index list.

#### fast -new [str] [str]

This command will create a new log file in the
workfolder. Meanwhile it accept two arguments.
The first argument is the log type, here are
the examples:

``fast -new b example.log``
``fast -new p example.plog``
``fast -new f example.flog``

The second argument is the log file name. When
exist the first argument, The log format must
match with the expansion name, or the program
will reject it. Omit the first argument, the
program will create BLog format as default.

#### fast -rm [str]

This command will remove a file in the
workfolder. Meanwhile it accept one argument.
This argument is the any file name in the
workfolder.

#### fast -add [str] [str]

NOT COMPLETE

#### fast -del [str] [str]

NOT COMPLETE

#### fast -show [str]

This command will show all logs list.
If you want to show a specific log file,
you can add the log file name as the argument.
If you want to show all logs list, you can
leave the argument empty.

#### fast -find [str]

This command will find a log file in the
workfolder. Meanwhile it accept one argument.
This argument is the log file name.

## Build

### Windows

This program is written in C/C++20. We suggest you\
use Visual Studio 2022 to build it.

if occur warning, you can try to add the following\
preprocessor define in the solution configure.

``_CRT_SECURE_NO_WARNINGS``
``_CRT_NONSTDC_NO_DEPRECATE``

### Linux

### MacOS

## Contact

Author : KenanZhu (Nanoki)\
Email  : <nanoki_zh@163.com>
