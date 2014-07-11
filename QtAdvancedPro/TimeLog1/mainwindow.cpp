#include "mainwindow.h"
#include "global.h"
#include "mainwindow.h"
#include "richtextdelegate.h"

#include "standarditem.h"
#include "standardtreemodel.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QHash>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QScopedPointer>

#include <QStatusBar>
#include <QStandardItem>
#include <QTimer>
#include <QToolBar>
#include <QTreeView>
#include <exception>
#include <QDebug>
const int StatusTimeout = 1000 * 10;
const QString FilenameSetting("Filename");
const QString GeometrySetting("Geometry");
const QString CurrentTaskPathSetting("CurrentTaskPath");
const int FirstFrame = 0;
const int LastFrame = 4;


namespace {
    QAction *createAction(const QString &icon, const QString &text,
            QObject *parent,
            const QKeySequence &shortcut=QKeySequence())
    {
        QAction *action = new QAction(QIcon(icon), text, parent);
        if (!shortcut.isEmpty())
            action->setShortcut(shortcut);
        return action;
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      ,
#ifndef CUSTOM_MODEL
      timedItem(0),
#endif
      currentIcon(0)
{
    createModelAndView();
    createActions();
    createMenusAndToolBar();
    createConnections();

    //peng.li
    //AQP::accelerateMenu(menuBar());

    setWindowTitle(tr("%1 (QStandardItemModel)[*]")
                   .arg(QApplication::applicationName()));

    statusBar()->showMessage(tr("Ready"), StatusTimeout);

    timer.setInterval(333);
    iconTimeLine.setDuration(5000);
    iconTimeLine.setFrameRange(FirstFrame, LastFrame + 1);
    iconTimeLine.setLoopCount(0);
    iconTimeLine.setCurveShape(QTimeLine::LinearCurve);
    QSettings settings;
    restoreGeometry(settings.value(GeometrySetting).toByteArray());
    QString filename = settings.value(FilenameSetting).toString();
    if (filename.isEmpty())
        QTimer::singleShot(0, this, SLOT(fileNew()));
    else
        QMetaObject::invokeMethod(this, "load", Qt::QueuedConnection,
                Q_ARG(QString, filename),
                Q_ARG(QStringList, settings.value(
                      CurrentTaskPathSetting).toStringList()));
}


void MainWindow::createModelAndView()
{
    treeView = new QTreeView;

    model = new StandardTreeModel(this);

    treeView->setAllColumnsShowFocus(true);
    treeView->setItemDelegateForColumn(0, new RichTextDelegate);
    treeView->setModel(model);
    setCentralWidget(treeView);
}


void MainWindow::createActions()
{
    fileNewAction = createAction(":/filenew.png", tr("New"),
            this, QKeySequence::New);
    fileOpenAction = createAction(":/fileopen.png", tr("Open..."),
            this, QKeySequence::Open);
    fileSaveAction = createAction(":/filesave.png", tr("Save"),
            this, QKeySequence::Save);
    fileSaveAsAction = createAction(":/filesave.png",
            tr("Save As..."), this
#if QT_VERSION >= 0x040500
            , QKeySequence::SaveAs
#endif
            );
    fileQuitAction = createAction(":/filequit.png", tr("Quit"), this);

    fileQuitAction->setShortcuts(QKeySequence::Quit);

    editAddAction = createAction(":/editadd.png", tr("Add..."),
            this, QKeySequence(tr("Ctrl+A")));
    editDeleteAction = createAction(":/editdelete.png",
            tr("Delete..."), this, QKeySequence::Delete);

    editStartOrStopAction = createAction(":/0.png", tr("S&tart"),
            this, QKeySequence(tr("Ctrl+T")));
    editStartOrStopAction->setCheckable(true);
    editStartOrStopAction->setChecked(false);
    editHideOrShowDoneTasksAction = new QAction(tr("Hide Done Tasks"),
            this);
    editHideOrShowDoneTasksAction->setCheckable(true);
    editHideOrShowDoneTasksAction->setChecked(false);
}


void MainWindow::createMenusAndToolBar()
{
    setUnifiedTitleAndToolBarOnMac(true);

    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    foreach (QAction *action, QList<QAction*>() << fileNewAction
            << fileOpenAction << fileSaveAction << fileSaveAsAction) {
        fileMenu->addAction(action);
        if (action != fileSaveAsAction)
            fileToolBar->addAction(action);
        if (action == fileSaveAction || action == fileSaveAsAction)
            action->setEnabled(false);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(fileQuitAction);

    QAction *emptyAction = 0;
    QMenu *editMenu = menuBar()->addMenu(tr("Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

    foreach (QAction *action, QList<QAction*>() << editAddAction
            << editDeleteAction << emptyAction
            << editStartOrStopAction << editHideOrShowDoneTasksAction)

    {
        if (action == emptyAction) {
            editMenu->addSeparator();
            editToolBar->addSeparator();
            continue;
        }
        if (action != editHideOrShowDoneTasksAction)
            editToolBar->addAction(action);
        else
            editMenu->addSeparator();
        editMenu->addAction(action);
    }
}


void MainWindow::createConnections()
{
    connect(treeView->selectionModel(),
            SIGNAL(currentChanged(const QModelIndex&,
                                  const QModelIndex&)),
            this, SLOT(updateUi()));

    connect(model, SIGNAL(itemChanged(QStandardItem*)),
            this, SLOT(setDirty()));

    connect(model, SIGNAL(rowsRemoved(const QModelIndex&,int,int)),
            this, SLOT(setDirty()));
    connect(model, SIGNAL(modelReset()), this, SLOT(setDirty()));

    QHash<QAction*, QString> slotForAction;
    slotForAction[fileNewAction] = SLOT(fileNew());
    slotForAction[fileOpenAction] = SLOT(fileOpen());
    slotForAction[fileSaveAction] = SLOT(fileSave());
    slotForAction[fileSaveAsAction] = SLOT(fileSaveAs());
    slotForAction[fileQuitAction] = SLOT(close());
    slotForAction[editAddAction] = SLOT(editAdd());
    slotForAction[editDeleteAction] = SLOT(editDelete());

    QHashIterator<QAction*, QString> i(slotForAction);
    while (i.hasNext()) {
        i.next();
        connect(i.key(), SIGNAL(triggered()),
                this, qPrintable(i.value()));
    }

    connect(editStartOrStopAction, SIGNAL(triggered(bool)),
            this, SLOT(editStartOrStop(bool)));
    connect(editHideOrShowDoneTasksAction, SIGNAL(triggered(bool)),
            this, SLOT(editHideOrShowDoneTasks(bool)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(&iconTimeLine, SIGNAL(frameChanged(int)),
            this, SLOT(updateIcon(int)));
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    stopTiming();
    if (okToClearData()) {
        QSettings settings;
        settings.setValue(GeometrySetting, saveGeometry());
        settings.setValue(FilenameSetting, model->filename());
        settings.setValue(CurrentTaskPathSetting,
                model->pathForIndex(treeView->currentIndex()));
        event->accept();
    }
    else
        event->ignore();
}


bool MainWindow::okToClearData()
{
    //peng.li
    /*if (isWindowModified())
        return AQP::okToClearData(&MainWindow::fileSave, this,
                tr("Unsaved changes"), tr("Save unsaved changes?"));
                */
    return true;
}


void MainWindow::fileNew()
{
    if (!okToClearData())
        return;
    model->clear();
    model->setFilename(QString());
    setDirty(false);
    setWindowTitle(tr("%1 - Unnamed[*]")
            .arg(QApplication::applicationName()));
    updateUi();
}


void MainWindow::updateUi()
{
    fileSaveAction->setEnabled(isWindowModified());
    int rows = model->rowCount();
    fileSaveAsAction->setEnabled(isWindowModified() || rows);
    editHideOrShowDoneTasksAction->setEnabled(rows);
    bool enable = treeView->currentIndex().isValid();

    foreach (QAction *action, QList<QAction*>() << editDeleteAction
            << editStartOrStopAction)
        action->setEnabled(enable);

}


void MainWindow::fileOpen()
{
    if (!okToClearData())
        return;
    QString filename = model->filename();
    QString dir(filename.isEmpty() ? QString(".")
                : QFileInfo(filename).canonicalPath());
    filename = QFileDialog::getOpenFileName(this,
            tr("%1 - Open").arg(QApplication::applicationName()),
            dir, tr("Timelogs (*.tlg)"));
    if (!filename.isEmpty())
        load(filename);
}


void MainWindow::load(const QString &filename,
                      const QStringList &taskPath)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    try {
        model->load(filename);
        if (!taskPath.isEmpty()) {
            if (QStandardItem *item = model->itemForPath(taskPath))
                setCurrentIndex(item->index());

        }
        for (int column = 0; column < model->columnCount(); ++column)
            treeView->resizeColumnToContents(column);
        setDirty(false);
        setWindowTitle(tr("%1 - %2[*]")
                .arg(QApplication::applicationName())
                .arg(QFileInfo(filename).fileName()));
        statusBar()->showMessage(tr("Loaded %1").arg(filename),
                                 StatusTimeout);
    } catch (std::exception &error) {
        qDebug()<<"try catch error"<<error.what();
    }
    updateUi();
    editHideOrShowDoneTasks(
            editHideOrShowDoneTasksAction->isChecked());
    treeView->setFocus();
    QApplication::restoreOverrideCursor();
}


void MainWindow::setCurrentIndex(const QModelIndex &index)
{
    if (index.isValid()) {
        treeView->scrollTo(index);
        treeView->setCurrentIndex(index);
    }
}


bool MainWindow::fileSave()
{
    bool saved = false;
    if (model->filename().isEmpty())
        saved = fileSaveAs();
    else {
        try {
            model->save();
            setDirty(false);
            setWindowTitle(tr("%1 - %2[*]")
                    .arg(QApplication::applicationName())
                    .arg(QFileInfo(model->filename()).fileName()));
            statusBar()->showMessage(tr("Saved %1")
                    .arg(model->filename()), StatusTimeout);
            saved = true;
        } catch (std::exception &error) {
            qDebug()<<"try 1 error "<<error.what();
        }
    }
    updateUi();
    return saved;
}


bool MainWindow::fileSaveAs()
{
    QString filename = model->filename();
    QString dir = filename.isEmpty() ? "."
                                     : QFileInfo(filename).path();
    filename = QFileDialog::getSaveFileName(this,
            tr("%1 - Save As").arg(QApplication::applicationName()),
            dir,
            tr("%1 (*.tlg)").arg(QApplication::applicationName()));
    if (filename.isEmpty())
        return false;
    if (!filename.toLower().endsWith(".tlg"))
        filename += ".tlg";
    model->setFilename(filename);
    return fileSave();
}



void MainWindow::editAdd()
{
    QModelIndex index = treeView->currentIndex();
    StandardTreeModel::Insert insert = StandardTreeModel::AtTopLevel;

    if (index.isValid()) {
        QStandardItem *item = model->itemFromIndex(index);

        QScopedPointer<QMessageBox> messageBox(new QMessageBox(this));

        messageBox->setWindowModality(Qt::WindowModal);
        messageBox->setIcon(QMessageBox::Question);
        messageBox->setWindowTitle(tr("%1 - Add Task")
                .arg(QApplication::applicationName()));
        messageBox->setText(tr("<p>Add at the top level or as a "
                    "sibling or child of\n'%1'?").arg(item->text()));
        messageBox->addButton(tr("&Top Level"),
                              QMessageBox::AcceptRole);
        QAbstractButton *siblingButton = messageBox->addButton(
                tr("&Sibling"), QMessageBox::AcceptRole);
        QAbstractButton *childButton = messageBox->addButton(
                tr("C&hild"), QMessageBox::AcceptRole);
        messageBox->setDefaultButton(
                qobject_cast<QPushButton*>(childButton));
        messageBox->addButton(QMessageBox::Cancel);
        messageBox->exec();
        if (messageBox->clickedButton() ==
            messageBox->button(QMessageBox::Cancel))
            return;
        if (messageBox->clickedButton() == childButton)
            insert = StandardTreeModel::AsChild;
        else if (messageBox->clickedButton() == siblingButton)
            insert = StandardTreeModel::AsSibling;
    }

    if (QStandardItem *item = model->insertNewTask(insert,
                tr("New Task"), index)) {
        QModelIndex index = item->index();
        setCurrentIndex(index);
        treeView->edit(index);
        setDirty();
        updateUi();
    }
}


void MainWindow::editDelete()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid())
        return;

    QStandardItem *item = model->itemFromIndex(index);
    if (item == timedItem)
        stopTiming();
    QString name = item->text();
    int rows = item->rowCount();

    QString message;
    if (rows == 0)
        message = tr("<p>Delete '%1'").arg(name);
    else if (rows == 1)
        message = tr("<p>Delete '%1' and its child (and "
                     "grandchildren etc.)").arg(name);
    else if (rows > 1)
        message = tr("<p>Delete '%1' and its %2 children (and "
                     "grandchildren etc.)").arg(name).arg(rows);
    //if (!AQP::okToDelete(this, tr("Delete"), message))
    //    return;
    model->removeRow(index.row(), index.parent());
    setDirty();
    updateUi();
}


void MainWindow::stopTiming()
{
    if (editStartOrStopAction->isChecked())
        editStartOrStopAction->trigger(); // stop the clock
}



void MainWindow::editStartOrStop(bool start)
{
    timer.stop();
    iconTimeLine.stop();
    if (start) { // start the clock iff there's a current task
        QModelIndex index = treeView->currentIndex();
        if (!index.isValid()) {
            editStartOrStopAction->setChecked(false);
            start = false;
        }
        else {
            QIcon icon(":/0.png");
            QDateTime now = QDateTime::currentDateTime();

            timedItem = static_cast<StandardItem*>(
                    model->itemFromIndex(index));
            Q_ASSERT(timedItem);
            timedItem->addDateTime(now, now);
            timedItem->todayItem()->setIcon(icon);

            editStartOrStopAction->setIcon(icon);

            setWindowIcon(icon);

            timedTime.restart();
            timer.start();
            iconTimeLine.start();
        }
    }
    else { // stop the clock
        timeout(); // update to now

        if (timedItem) {
            timedItem->todayItem()->setIcon(QIcon());
            timedItem = 0;
        }

        setWindowIcon(QIcon(":/icon.png"));

        editStartOrStopAction->setIcon(QIcon(":/0.png"));
    }
    editStartOrStopAction->setText(start ? tr("S&top")
                                         : tr("S&tart"));
    editStartOrStopAction->setIcon(QIcon(start ? tr(":/4.png")
                                               : tr(":/0.png")));
}


void MainWindow::timeout()
{

    Q_ASSERT(timedItem);
    timedItem->incrementLastEndTime(timedTime.elapsed());
    timedTime.restart();
    StandardItem *item = timedItem;
    while (item) {
        item->todayItem()->setText(item->todaysTime());
        item->totalItem()->setText(item->totalTime());
        item = static_cast<StandardItem*>(item->parent());
    }

}


void MainWindow::updateIcon(int frame)
{
    if (frame > LastFrame)
        return;
    QIcon icon(QString(":/%1.png").arg(frame));

    Q_ASSERT(timedItem);
    timedItem->todayItem()->setIcon(icon);

    editStartOrStopAction->setIcon(icon);

    setWindowIcon(icon);

}


void MainWindow::editHideOrShowDoneTasks(bool hide)
{
    hideOrShowDoneTask(hide, model->invisibleRootItem());

}


void MainWindow::hideOrShowDoneTask(bool hide, QStandardItem *item)
{
    QModelIndex index = item->parent() ? item->parent()->index()
                                       : QModelIndex();
    bool hideThisOne = hide && (item->checkState() == Qt::Checked);
    treeView->setRowHidden(item->row(), index, hideThisOne);
    if (!hideThisOne) {
        for (int row = 0; row < item->rowCount(); ++row)
            hideOrShowDoneTask(hide, item->child(row, 0));
    }
}
