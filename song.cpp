#include "song.h"

Song::Song() {
    mNoteCount = 3;

    Notes[0] = CENTER;
    Notes[1] = CENTER;
    Notes[2] = CENTER;
    Notes[3] = EMPTY;
    Notes[4] = EMPTY;
    Notes[5] = EMPTY;
}

Song::Song(bStream::CFileStream * reader) {
    mNoteCount = reader->readInt8();

    for (int i = 0; i < 6; i++) {
        Notes[i] = static_cast<Note>(reader->readInt8());
    }
}

void Song::SaveSong(bStream::CFileStream * writer) {
    writer->writeInt8(mNoteCount);

    for (int i = 0; i < 6; i++) {
         writer->writeInt8(static_cast<int8_t>(Notes[i]));
    }
}
