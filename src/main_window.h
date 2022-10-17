#pragma once

#include <QMainWindow>


class QAction;
class QComboBox;
class QMdiArea;
class QDoubleSpinBox;
class shape_widget;

class main_window : public QMainWindow {
  Q_OBJECT

public:
  main_window(QWidget *parent = nullptr);

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  void create_dockable_toolbar();
  void create_opengl_widget();

private:
  QMdiArea*       mdi_area_;
  QMenu*          view_menu_;
  QAction*        open_action_;
  shape_widget*   shape_widget_        = nullptr;

  QComboBox*      cb_shapes_;
  QDoubleSpinBox* sb_shape_size_;

  const float     default_shape_width_ = 1.;
  QFont           arial_13_            = {"Arial", 13};
};
