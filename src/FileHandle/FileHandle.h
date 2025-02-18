#ifndef _FILEHANDLE_H_
#define _FILEHANDLE_H_

#include "../FLRecorder.h"

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

    // Init all members
    void Init(void);
    
public:
    FileHandle(void);
    ~FileHandle(void);

    // Put message on the console
    void PutMessage(string Msg);

    // Get file path
    string Path(void);

    // Get file name
    string Name(void);

    // Set/Get file format when argument is empty
    int Format(string ExpName=" ");

    // Set file path
    int SetPath(string FilePath);

    // Create file
    bool Create(void);

    // Remove file
    bool Remove(void);

    // Get file state: exist
    bool IsExist(void);

    // Get file state: open state
    bool IsOpen(void);

    // Get file state: eof state
    bool IsEof(void);

    // Close file
    void Close(void);
};

}

#endif // !_FILEHANDLE_H_