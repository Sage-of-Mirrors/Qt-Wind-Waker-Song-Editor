#include "songmanager.h"

SongManager::SongManager() {
    mCurrentSongIndex = 0;
}

int SongManager::CheckGameVersion(bStream::CFileStream * reader) {
    reader->seek(0x1C);

    uint32_t version_test = reader->readUInt32();

    int data_offset;

    switch (version_test) {
        case 0x3355C0:
            data_offset = NTSC_U_OFFSET;
            break;
        case 0x332FC0:
            data_offset = NTSC_J_OFFSET;
            break;
        case 0x0:
            data_offset = PAL_OFFSET;
            break;
        default: // If execution gets here, no valid version was discovered. Error!
            return 1;
    }

    return data_offset;
}

void SongManager::LoadSongData(QString file_path) {
    mOpenPath = file_path;

    bStream::CFileStream * reader = new bStream::CFileStream(file_path.toStdString(), bStream::Big);

    mSongDataOffset = CheckGameVersion(reader);

    // There was an error!
    if (mSongDataOffset == 1)
    {
        return;
    }

    reader->seek(mSongDataOffset);

    for (int i = 0; i < 8; i++) {
        mSongs[i] = Song(reader);
    }

    delete reader;
}

void SongManager::SaveSongData() {
    bStream::CFileStream * writer = new bStream::CFileStream(mOpenPath.toStdString(), bStream::Big, bStream::Out);
    writer->seek(mSongDataOffset);

    for (int i = 0; i < 8; i++) {
        mSongs[i].SaveSong(writer);
    }

    delete writer;
}

void SongManager::OpenFile() {
    QString file_name = QFileDialog::getOpenFileName(nullptr, "Open .dol file", "", "GameCube executable files (*.dol)");
    LoadSongData(file_name);
}

void SongManager::SaveFile() {
    SaveSongData();
}

void SongManager::SaveFileAs() {
    QString new_file_name = QFileDialog::getSaveFileName(nullptr, "Save .dol file", "", "GameCube executable file (*.dol)");
    if (mOpenPath != new_file_name) {
        if (QFile::exists(new_file_name)) {
            QFile::remove(new_file_name);
        }

        QFile::copy(mOpenPath, new_file_name);
        mOpenPath = new_file_name;
    }

    SaveSongData();
}

void SongManager::SetCurrentSong(int index) {
    mCurrentSongIndex = index;
}

Song * SongManager::GetCurrentSong() {
    return &mSongs[mCurrentSongIndex];
}
