#ifndef _FILEHANDLE_H_
#define _FILEHANDLE_H_

#include "..\FLRecorder.h"

/// 
/// File/Folder Handle Classes
/// 
namespace Fhd {

/// File Handle Basic Class
/// 
class FileHandle
{
protected:
    int sef_FileFormat;
    bool sef_FileState;
    string sef_FilePath;
    string sef_FileName;
    fstream sef_FileHand;
private:

    // Init All Members
    void Init(void);

    

public:
    FileHandle(void);
    ~FileHandle(void);

    // ReWrite Base Class
    void PutMessage(string Msg);

    // Get File Path
    string Path(void);

    // Get File Name
    string Name(void);

    // Set/Get File Format
    int Format(string ExpName=" ");

    // Set File Path
    int SetPath(string FilePath);

    // Create File
    bool Create(void);

    // Remove File
    bool Remove(void);

    // Get File State: Exist
    bool IsExist(void);

    // Get File State: Open State
    bool IsOpen(void);

    // Get File State: Eof State
    bool IsEof(void);

    // Close File
    void Close(void);
};

}

#endif // !_FILEHANDLE_H_