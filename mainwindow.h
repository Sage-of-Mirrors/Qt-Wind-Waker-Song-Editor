#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QMoveEvent>

#include "songmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_SongSelector_currentIndexChanged(int index);

public slots:
    void updateNoteGraphics(int noteType);
    void updateSongNote(int noteType);

private:
    Ui::MainWindow *ui;
    SongManager view_model;

    QPixmap notes[6];
    QGraphicsPixmapItem *noteView[6];
    QGraphicsScene scene;

    void ToggleCombos(bool state);
    void UpdateView();
};

#endif // MAINWINDOW_H
