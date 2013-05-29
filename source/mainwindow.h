#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QColorDialog>
#include <QScrollBar>
#include <QBrush>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QEvent>
#include <QSettings>
#include <QtNetwork/QNetworkAccessManager>

#include <boost/dynamic_bitset.hpp>

#include "Volume.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool mouseEvent(QObject *object, QMouseEvent *mouseEvent);
    bool myKeyPressEvent(QObject *object, QKeyEvent *keyEvent);
    bool myMouseReleaseEvent (QObject *object, QMouseEvent * e);
    void myMousePressEvent (QObject *object, QMouseEvent * e);
    bool myMouseWheelEvent (QObject *object, QWheelEvent * e);
    void myMouseButtonDblClick(QObject *object, QMouseEvent *mouseEvent);
    void redo();
    void undo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void LoadLabel();
    void SaveLabel();
    void CreateLabel();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_toolButton_toggled(bool checked);

    void on_toolButton_2_toggled(bool checked);

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    // slice orientation indicates which slice to fill
    void FillHighlight(int which);

    void on_toolButton_6_clicked();

    void on_toolButton_6_toggled(bool checked);

    void about();

    void on_pushButton_5_clicked();

    void on_zoomToggle_toggled(bool checked);

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void finishedSlot(QNetworkReply* reply);

    void on_treeWidget_doubleClicked(const QModelIndex &index);

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

public slots:
    void LoadImage();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    double scaleFactor1;
    double scaleFactor23;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    void updateActions();
    void update();
    void updateImage1(int pos);
    void updateImage2(int pos);
    void updateImage3(int pos);

    QList<QTreeWidgetItem *> materials;

    void createActions();
    void setupDefaultMaterials();
    void getMaterialsFromLabel();

    std::vector<Volume *> volumes;
    std::vector<Volume *> labels;

    Volume *vol1;
    Volume *lab1;
    QLabel *Image1;
    QLabel *Image2;
    QLabel *Image3;

    std::vector<int> slicePosition;
    float windowLevel[2];
    float windowLevelOverlay[2];
    // each dataset has also a currentWindowLevel, if you change windowLevel change that one as well

    void normalSize();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void showHistogram(Volume *vol1, QGraphicsView *gv);
    int mousePressLocation[2];
    bool mouseIsDown;
    float windowLevelBefore[2];
    float scaleFactor1Before;
    float scaleFactor23Before;
    bool toolWindowLevel;
    bool toolSegmentation;

    unsigned char *fillBuffer1(int pos, Volume *vol1, float alpha=255);
    unsigned char *fillBuffer2(int pos, Volume *vol2, float alpha=255);
    unsigned char *fillBuffer3(int pos, Volume *vol3, float alpha=255);
    unsigned char *fillBuffer1AsColor(int pos, ScalarVolume *vol1, float alpha);
    unsigned char *fillBuffer2AsColor(int pos, ScalarVolume *vol1, float alpha);
    unsigned char *fillBuffer3AsColor(int pos, ScalarVolume *vol1, float alpha);

    unsigned char *fillBuffer1FromHBuffer(int pos, ScalarVolume *vol1, float alpha);
    unsigned char *fillBuffer2FromHBuffer(int pos, ScalarVolume *vol1, float alpha);
    unsigned char *fillBuffer3FromHBuffer(int pos, ScalarVolume *vol1, float alpha);

    // create storage for the highlight
    // add buffer add and remove to currently hightlighted material
    boost::dynamic_bitset<> hbuffer;

    void setHighlightBuffer(QObject *object, QMouseEvent *e);

    enum Tools {
      None,
      ContrastBrightness,
      BrushTool,
      MagicWandTool,
      ZoomTool
    };

    Tools currentTool;
    int BrushToolRadius;
    QDir currentPath;
    void regionGrowing(int posx, int posy, int slice);
    void regionGrowing2(int posx, int posy, int slice);
    void regionGrowing3(int posx, int posy, int slice);

    bool showHighlights;

    // get a list of strings from internet
    QNetworkAccessManager* nam;
    QStringList fetchModel(QString aString);

    bool firstUndoStepDone;
};

#endif // MAINWINDOW_H