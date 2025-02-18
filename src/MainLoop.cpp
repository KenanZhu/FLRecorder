///=====================================================///
/// 
/// \file   MainLoop.cpp
/// \brief 'FastLogRecorder' Main Source File
/// \author KenanZhu
/// \date   2025-02-09
///-----------------------------------------------------///
/// \note
///
/// Software usage:
///     This is a Command Line Interface (CLI) program.
///     the command are all be lowercase, any different
///     is reject. here are commands:
///     
///     commands are like:
///       FLRecord/base> fast [-cmd] [arg]
/// 
///       $[-cmd] $[arg]    $command
/// 
///        [-help]           Get help.
///        [-quit]           Exit the program.
///        [-ver]            Get program version.
///        [-init]           Init the workfolder.
///        [-new]            Add a new log file.
///           |____[str]     log type.
///           |____[str]     log file name.
///        [-rm]             Remove a log file.
///           |____[str]     log file name.
///        [-add]            Add a log record.
///           |____[str]     log file name.
///           |____[str]     new log record.
///        [-del]            Delete a log record.
///           |____[str]     log file name.
///           |____[str]     deleted log record.
///        [-show]           Show all logs list.
///           |____[str]     <optional> log file name
///        [-find]           Find log file.
///           |____[str]     log file name.
/// 
/// Copyright (c) 2025 by KenanZhu. All rights reserved.
///
/// ----------------------------------------------------///
/// \hsitory $-Date      $-Version  $-Update
///          2025-02-09  0.0.1      First Created.
///          2025-02-12  0.0.3      See Update Note.
///          2025-02-18  0.0.5      See Update Note.
/// 
///=====================================================///

#include "FLRecorder.h"
#include "./CLI/CmdLI.h"
#include "./LogTypes/LogTypes.h"
#include "./FileHandle/FileHandle.h"

using namespace std;

/// COMMAND LINE INTERFACE
static Cli::CliBase *CLI;
/// Control Class

int main(int argc,char *argv[])
{
    int LnhMod;
    string CMD;

    /// System level init:
    ///   set system info level by command line argument.
    if      (argc==1) LnhMod=0;
    else if (argc==2) {
        try { LnhMod=stoi(argv[1]);}
        catch (invalid_argument) {
            cout<<"exit (code=-1): Invalid argument '"+string(argv[1])+"' !"; 
            return -1;
        }
    }
    else    {
        cout<<"exit (code=-1): Too many arguments !";
        return -1;
    }
    CLI=new Cli::CliBase();

    while (true) {
        
        /// Get user input
        cout<<"[FLRecorder ~ v0.0.5-alpha] >> : ";
        getline(cin,CMD,'\n');
        
        /// Distribute command
        CLI->DistributeCmd(CMD);
    }
    return 0;
}