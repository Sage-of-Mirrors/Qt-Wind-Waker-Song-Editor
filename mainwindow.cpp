#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtWidgets/QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    notes[0] = QPixmap(":/images/WWMiddleNew.png");
    notes[1] = QPixmap(":/images/WWup.png");
    notes[2] = QPixmap(":/images/WWright.png");
    notes[3] = QPixmap(":/images/WWdown.png");
    notes[4] = QPixmap(":/images/WWleft.png");
    notes[5] = QPixmap(":/images/WWempty.png");

    noteView[0] = new QGraphicsPixmapItem(notes[5]);
    noteView[1] = new QGraphicsPixmapItem(notes[5]);
    noteView[2] = new QGraphicsPixmapItem(notes[5]);
    noteView[3] = new QGraphicsPixmapItem(notes[5]);
    noteView[4] = new QGraphicsPixmapItem(notes[5]);
    noteView[5] = new QGraphicsPixmapItem(notes[5]);

    for(int i = 0; i < 6; i++){
        noteView[i]->setPos(QPoint(100*i, 0));
        this->scene.addItem(noteView[i]);
    }

    connect(ui->note1, SIGNAL(currentIndexChanged(int)), this, SLOT(updateNoteGraphics(int)));
    connect(ui->note2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateNoteGraphics(int)));
    connect(ui->note3, SIGNAL(currentIndexChanged(int)), this, SLOT(updateNoteGraphics(int)));
    connect(ui->note4, SIGNAL(currentIndexChanged(int)), this, SLOT(updateNoteGraphics(int)));
    connect(ui->note5, SIGNAL(currentIndexChanged(int)), this, SLOT(updateNoteGraphics(int)));
    connect(ui->note6, SIGNAL(currentIndexChanged(int)), this, SLOT(updateNoteGraphics(int)));

    connect(ui->note1, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSongNote(int)));
    connect(ui->note2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSongNote(int)));
    connect(ui->note3, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSongNote(int)));
    connect(ui->note4, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSongNote(int)));
    connect(ui->note5, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSongNote(int)));
    connect(ui->note6, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSongNote(int)));

    ui->graphicsView->setScene(&this->scene);
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < 6; i++){
        delete noteView[i];
    }

    delete ui;
}

void MainWindow::updateNoteGraphics(int noteType) {
    int noteIndex = sender()->property("noteIndex").value<int>();
    this->noteView[noteIndex]->setPixmap(notes[noteType]);
    ui->graphicsView->update();
}

void MainWindow::updateSongNote(int noteType) {
    int noteIndex = sender()->property("noteIndex").value<int>();
    Song * curSong = view_model.GetCurrentSong();

    curSong->Notes[noteIndex] = static_cast<Note>(noteType);
}

void MainWindow::on_actionOpen_triggered()
{
    if (view_model.OpenFile()) {
        ToggleCombos(true);
        UpdateView();
        ui->SongSelector->setCurrentIndex(0);

        switch(view_model.GetCurrentSong()->GetNoteCount())
        {
        case 3:
            on_note3Radio_toggled(true);
            break;
        case 4:
            on_note4Radio_toggled(true);
            break;
        case 6:
            on_note6Radio_toggled(true);
            break;
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    view_model.SaveFile();
}

void MainWindow::on_actionSave_As_triggered()
{
    view_model.SaveFileAs();
}

void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}

void MainWindow::on_SongSelector_currentIndexChanged(int index)
{
    view_model.SetCurrentSong(index);
    UpdateView();
}

void MainWindow::ToggleCombos(bool state) {
    ui->note1->setEnabled(state);
    ui->note2->setEnabled(state);
    ui->note3->setEnabled(state);
    ui->note4->setEnabled(state);
    ui->note5->setEnabled(state);
    ui->note6->setEnabled(state);

    ui->SongSelector->setEnabled(state);

    ui->actionSave->setEnabled(state);
    ui->actionSave_As->setEnabled(state);

    ui->noteCountLabel->setEnabled(state);
    ui->note3Radio->setEnabled(state);
    ui->note4Radio->setEnabled(state);
    ui->note6Radio->setEnabled(state);
}

void MainWindow::UpdateView() {
    Song * curSong = view_model.GetCurrentSong();

    switch (curSong->GetNoteCount()) {
    case 3:
        ui->note3Radio->setChecked(true);
        break;
    case 4:
        ui->note4Radio->setChecked(true);
        break;
    case 6:
        ui->note6Radio->setChecked(true);
        break;
    }

    ui->note1->setCurrentIndex(static_cast<int>(curSong->Notes[0]));
    ui->note2->setCurrentIndex(static_cast<int>(curSong->Notes[1]));
    ui->note3->setCurrentIndex(static_cast<int>(curSong->Notes[2]));

    if (curSong->Notes[3] == EMPTY) {

    }
    else {
            ui->note4->setCurrentIndex(static_cast<int>(curSong->Notes[3]));
    }
    if (curSong->Notes[4] == EMPTY) {

    }
    else {
            ui->note5->setCurrentIndex(static_cast<int>(curSong->Notes[4]));
    }
    if (curSong->Notes[5] == EMPTY) {

    }
    else {
            ui->note6->setCurrentIndex(static_cast<int>(curSong->Notes[5]));
    }
}

void MainWindow::on_note3Radio_toggled(bool checked)
{
    if (checked) {
        Song * curSong = view_model.GetCurrentSong();

        curSong->SetNoteCount(3);

        noteView[3]->setPixmap(notes[5]);
        noteView[4]->setPixmap(notes[5]);
        noteView[5]->setPixmap(notes[5]);

        ui->note4->setCurrentIndex(static_cast<int>(0));
        ui->note5->setCurrentIndex(static_cast<int>(0));
        ui->note6->setCurrentIndex(static_cast<int>(0));

        ui->note4->setEnabled(false);
        ui->note5->setEnabled(false);
        ui->note6->setEnabled(false);

        ui->note4->setVisible(false);
        ui->note5->setVisible(false);
        ui->note6->setVisible(false);
    }
}

void MainWindow::on_note4Radio_toggled(bool checked)
{
    if (checked) {
        Song * curSong = view_model.GetCurrentSong();

        curSong->SetNoteCount(4);

        ui->note4->setCurrentIndex(static_cast<int>(0));
        ui->note5->setCurrentIndex(static_cast<int>(0));
        ui->note6->setCurrentIndex(static_cast<int>(0));

        noteView[3]->setPixmap(notes[0]);
        noteView[4]->setPixmap(notes[5]);
        noteView[5]->setPixmap(notes[5]);

        ui->note4->setEnabled(true);
        ui->note5->setEnabled(false);
        ui->note6->setEnabled(false);

        ui->note4->setVisible(true);
        ui->note5->setVisible(false);
        ui->note6->setVisible(false);
    }
}

void MainWindow::on_note6Radio_toggled(bool checked)
{
    if (checked) {
        Song * curSong = view_model.GetCurrentSong();

        curSong->SetNoteCount(4);

        ui->note4->setCurrentIndex(static_cast<int>(0));
        ui->note5->setCurrentIndex(static_cast<int>(0));
        ui->note6->setCurrentIndex(static_cast<int>(0));

        noteView[3]->setPixmap(notes[0]);
        noteView[4]->setPixmap(notes[0]);
        noteView[5]->setPixmap(notes[0]);

        ui->note4->setEnabled(true);
        ui->note5->setEnabled(true);
        ui->note6->setEnabled(true);

        ui->note4->setVisible(true);
        ui->note5->setVisible(true);
        ui->note6->setVisible(true);
    }
}
