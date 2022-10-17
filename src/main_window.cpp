#include "main_window.h"

#include <QCloseEvent>
#include <QComboBox>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMdiArea>

#include "shape_widget.h"


main_window::main_window(QWidget *parent)
  : QMainWindow(parent) {
  mdi_area_ = new QMdiArea(this);
  setCentralWidget(mdi_area_);
  mdi_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdi_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

  view_menu_ = menuBar()->addMenu("Меню");
  menuBar()->setFont(arial_13_);
  view_menu_->setFont(arial_13_);

  open_action_ = new QAction("Открыть виджет OpenGL", this);
  open_action_->setShortcut(QKeySequence::New);
  connect(open_action_, &QAction::triggered, this, &main_window::create_opengl_widget);
  view_menu_->addAction(open_action_);

  create_dockable_toolbar();
  create_mdi_child();

  setMinimumSize(800, 600);
}


void main_window::closeEvent(QCloseEvent* event) {
  mdi_area_->closeAllSubWindows();
  if (mdi_area_->currentSubWindow()) {
    event->ignore();
  } else {
    event->accept();
  }
}


void main_window::create_dockable_toolbar() {
  QDockWidget *dockable_panel = new QDockWidget("Настройки объекта", this);
  dockable_panel->setFixedSize(200, 200);
  dockable_panel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  QWidget* w = new QWidget(dockable_panel);
  auto* grid = new QGridLayout(w);
  w->setLayout(grid);
  w->setFont(arial_13_);

  auto* lb_shape_type = new QLabel ("Тип фигуры", w);
  grid->addWidget(lb_shape_type,    0, 0,   1, 1); // (obj, row, colmn,    rowSpan, colmnSpan)

  cb_shapes_ = new QComboBox(w);
  cb_shapes_->addItem("Пирамида");
  cb_shapes_->addItem("Куб");
  cb_shapes_->addItem("Шар");
  grid->addWidget(cb_shapes_,       1, 0,   1, 1);

  auto* lb_shape_size = new QLabel ("Размер фигуры", w);
  grid->addWidget(lb_shape_size,    2, 0,   1, 1);

  sb_shape_size_ = new QDoubleSpinBox(w);
  sb_shape_size_->setValue(default_shape_width_);
  sb_shape_size_->setSingleStep(0.1);
  grid->addWidget(sb_shape_size_,   3, 0,   1, 1);
  dockable_panel->setWidget(w);

  addDockWidget(Qt::RightDockWidgetArea, dockable_panel);
  view_menu_->addAction(dockable_panel->toggleViewAction());
}


mdi_child_temp* main_window::create_mdi_child() {
  auto* child = new mdi_child_temp();
  child->setAttribute(Qt::WA_DeleteOnClose);
  child->setMinimumSize(300, 400);
  mdi_area_->addSubWindow(child);

  return child;
}


void main_window::create_opengl_widget() {
  if (shape_widget_ == nullptr) {
    shape_widget_ = new shape_widget(shape_type::pyramid, sb_shape_size_->value());

    connect(cb_shapes_, &QComboBox::currentIndexChanged, [this](int index) {
      shape_widget_->change_shape(index);
      sb_shape_size_->setValue(default_shape_width_);
    });
    connect(sb_shape_size_, &QDoubleSpinBox::valueChanged,
            shape_widget_, &shape_widget::change_size);
    connect(shape_widget_, &shape_widget::closed, [this]() {
//      shape_widget_->deleteLater();
      shape_widget_ = nullptr;
    });

    shape_widget_->setAttribute(Qt::WA_DeleteOnClose);
    shape_widget_->setMinimumSize(400, 400);
    mdi_area_->addSubWindow(shape_widget_);
    shape_widget_->show();
  }
}


mdi_child_temp::mdi_child_temp() { // temp
//  setAttribute(Qt::WA_DeleteOnClose);
//  setMinimumSize(300, 400);
}

