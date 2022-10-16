#pragma once

#include <QMainWindow>


//class close_event_filter : public QObject {
//  Q_OBJECT

//public:
//  close_event_filter() = default;

//protected:
//  bool eventFilter(QObject *obj, QEvent *event) override;
//};


#include <QTextEdit>
class mdi_child_temp : public QTextEdit {
  Q_OBJECT

public:
  mdi_child_temp();
};


class QComboBox;
class QLineEdit;
class QMdiArea;
class QMdiSubWindow;
class QPushButton;
class QSpinBox;
class main_window : public QMainWindow {
  Q_OBJECT

public:
  main_window(QWidget *parent = nullptr);
  ~main_window();

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  void create_dockable_toolbar();

  QWidget* create_mdi_child(bool is_opengl_temp_fl); // change ret val type to void!
//  mdi_child_temp* activeMdiChild() const;
//  QMdiSubWindow* findMdiChild(const QString &file_name) const;

private:
  QComboBox*   cb_shapes_;
  QLineEdit*   le_shape_width_;
  QPushButton* pb_apply_width_;
  QSpinBox*    sb_shape_width2_;

  QMdiArea*    mdi_area_;
  QMenu*       view_menu_;
};
