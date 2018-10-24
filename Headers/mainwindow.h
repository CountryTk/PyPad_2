#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tabs.h>
#include <directory.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    bool modified;

    ~MainWindow();

private slots:
    void on_actionNew_file_triggered();

    void on_actionCustomize_triggered();

    void on_actionQuit_triggered();

    void close_current_tab();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionRun_triggered();

    void testFunction();

    void changeName();

    void on_actionSave_as_triggered();

    void open_file_from_menu(QModelIndex signal);

    void open_file_universal(QString file_name, bool is_image);

    bool open_project();

    //void create_project();

    void on_actionOpen_project_triggered();

    void tab_close_requested(int index);

private:
    Ui::MainWindow *ui;
    Tabs *tab_class;
};

#endif // MAINWINDOW_H
