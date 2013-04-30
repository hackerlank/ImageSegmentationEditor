#ifndef EVENTPROCESSING_H
#define EVENTPROCESSING_H


#include <iostream>
#include <QtGui>
#include <QMouseEvent>
#include <QEvent>
#include "mainwindow.h"

class EventProcessing:public QObject
{
  public:
  EventProcessing( MainWindow *w ):QObject() {
      this->w = w;
  };
  ~EventProcessing() {};

  bool eventFilter(QObject* object,QEvent* event) {
      if (event->type() == QEvent::KeyPress) {
          QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);

          // std::cerr << "You Pressed " << keyEvent->text().toStdString() << "\n";
          w->myKeyPressEvent(object, keyEvent);
          return false;
      } else if (event->type() == QEvent::MouseMove) {
          QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
          //fprintf(stderr, "Mouse event received at: %d %d\n", mouseEvent->pos().x(), mouseEvent->pos().y());
          w->mouseEvent(object, mouseEvent);
          return false;
          // statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
      } else if (event->type() == QEvent::MouseButtonPress) {
              QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
              //fprintf(stderr, "Mouse event received at: %d %d\n", mouseEvent->pos().x(), mouseEvent->pos().y());
              w->myMousePressEvent(object, mouseEvent);
              return false;
              // statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
      } else if (event->type() == QEvent::MouseButtonRelease) {
              QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
              //fprintf(stderr, "Mouse event received at: %d %d\n", mouseEvent->pos().x(), mouseEvent->pos().y());
              w->myMouseReleaseEvent(object, mouseEvent);
              return false;
              // statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
      } else if (event->type() == QEvent::Wheel) {
              QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
              w->myMouseWheelEvent(object, wheelEvent);
      } else {
          // standard event processing
          return QObject::eventFilter(object, event);
      }
      return false;
  }

private:
  MainWindow *w;
};

#endif // EVENTPROCESSING_H
