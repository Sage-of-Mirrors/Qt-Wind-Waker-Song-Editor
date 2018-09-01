#ifndef SONG_H
#define SONG_H

#include "bstream.h"

enum Note {
  EMPTY  = -1,
  CENTER = 0,
  UP     = 1,
  RIGHT  = 2,
  DOWN   = 3,
  LEFT   = 4,
  MAX_NOTE = 6
};

class Song {
private:
    int8_t mNoteCount;
public:
    Note Notes[6];

    Song();
    Song(bStream::CFileStream * reader);

    void SaveSong(bStream::CFileStream * writer);
};

#endif // SONG_H
