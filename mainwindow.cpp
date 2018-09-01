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

    notes[0] = QPixmap(":/images/WWempty.png");
    notes[1] = QPixmap(":/images/WWMiddleNew.png");
    notes[2] = QPixmap(":/images/WWup.png");
    notes[3] = QPixmap(":/images/WWright.png");
    notes[4] = QPixmap(":/images/WWdown.png");
    notes[5] = QPixmap(":/images/WWleft.png");

    noteView[0] = new QGraphicsPixmapItem(notes[0]);
    noteView[1] = new QGraphicsPixmapItem(notes[0]);
    noteView[2] = new QGraphicsPixmapItem(notes[0]);
    noteView[3] = new QGraphicsPixmapItem(notes[0]);
    noteView[4] = new QGraphicsPixmapItem(notes[0]);
    noteView[5] = new QGraphicsPixmapItem(notes[0]);

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

    curSong->Notes[noteIndex] = static_cast<Note>(noteType - 1);
}

void MainWindow::on_actionOpen_triggered()
{
    view_model.OpenFile();
    ToggleCombos(true);
    UpdateView();
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
}

void MainWindow::UpdateView() {
    Song * curSong = view_model.GetCurrentSong();

    ui->note1->setCurrentIndex(static_cast<int>(curSong->Notes[0]) + 1);
    ui->note2->setCurrentIndex(static_cast<int>(curSong->Notes[1]) + 1);
    ui->note3->setCurrentIndex(static_cast<int>(curSong->Notes[2]) + 1);
    ui->note4->setCurrentIndex(static_cast<int>(curSong->Notes[3]) + 1);
    ui->note5->setCurrentIndex(static_cast<int>(curSong->Notes[4]) + 1);
    ui->note6->setCurrentIndex(static_cast<int>(curSong->Notes[5]) + 1);
}
