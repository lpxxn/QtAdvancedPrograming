#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTime>
#include <QTimeLine>
#include <QTimer>


class QAction;
class QStandardItem;
class StandardItem;
class QModelIndex;
class QTreeView;

class StandardTreeModel;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);

public slots:
    void stopTiming();

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void editAdd();
    void editDelete();
    void editStartOrStop(bool start);
    void editHideOrShowDoneTasks(bool hide);
    void setDirty(bool dirty=true) { setWindowModified(dirty); }
    void load(const QString &filename,
              const QStringList &taskPath=QStringList());
    void timeout();
    void updateIcon(int frame);
    void updateUi();

private:
    void createModelAndView();
    void createActions();
    void createMenusAndToolBar();
    void createConnections();
    bool okToClearData();
    void setCurrentIndex(const QModelIndex &index);

    void hideOrShowDoneTask(bool hide, QStandardItem *item);

    QAction *fileNewAction;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *fileQuitAction;
    QAction *editAddAction;
    QAction *editDeleteAction;

    QAction *editStartOrStopAction;
    QAction *editHideOrShowDoneTasksAction;

    QTreeView *treeView;

    StandardTreeModel *model;
    StandardItem *timedItem;
    QTimer timer;
    QTimeLine iconTimeLine;
    QTime timedTime;
    int currentIcon;
};

#endif // MAINWINDOW_H
