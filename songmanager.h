#ifndef SONGMANAGER_H
#define SONGMANAGER_H

#include <QString>
#include <QFileDialog>
#include "bstream.h"
#include "song.h"

class SongManager {
private:
    const int NTSC_U_OFFSET = 0x3985F4;
    const int NTSC_J_OFFSET = 0x38BB1C;
    const int PAL_OFFSET = 0x0;

    int mSongDataOffset;
    QString mOpenPath;

    int mCurrentSongIndex;
    Song mSongs[8];

    int CheckGameVersion(bStream::CFileStream * reader);
    void LoadSongData(QString file_path);
    void SaveSongData();
public:
    SongManager();

    void SetCurrentSong(int index);
    void SetCurrentSongNote(Note value, int note);

    Song * GetCurrentSong();

    bool OpenFile();
    void SaveFile();
    void SaveFileAs();
};

#endif // SONGMANAGER_H
