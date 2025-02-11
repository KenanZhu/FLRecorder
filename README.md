# FLRecorder

> [!NOTE]
> This project is still in experimental phase.

![FLRecorder_Logo](./doc/FLRecorder_CODE.png#pic_center)

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
           |____[int]     log type.
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

## Contact

Author : KenanZhu (Nanoki)\
Email  : <nanoki_zh@163.com>
