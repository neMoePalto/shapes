#include "main_window.h"

#include <QCloseEvent>
#include <QComboBox>
#include <QDockWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QMenuBar>
#include <QMdiArea>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit> // temp

#include "shape_widget.h"


main_window::main_window(QWidget *parent)
  : QMainWindow(parent) {
//  te_temp_ = new QTextEdit();

  mdi_area_ = new QMdiArea();
  // Проверить на большом объекте:
  mdi_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdi_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  setCentralWidget(mdi_area_);

//  connect(mdiArea, &QMdiArea::subWindowActivated,
//          this, &MainWindow::updateMenus);

  view_menu_ = menuBar()->addMenu("Вид");

  create_dockable_toolbar();

  create_mdi_child(true);
  create_mdi_child(false);

  setMinimumSize(800, 600);
}


main_window::~main_window() {
}


void main_window::closeEvent(QCloseEvent* event) {
  mdi_area_->closeAllSubWindows();
  if (mdi_area_->currentSubWindow()) {
      event->ignore();
  } else {
//      writeSettings();
      event->accept();
  }
}


void main_window::create_dockable_toolbar() {
  QDockWidget *dockable_panel = new QDockWidget("Настройки объекта", this);
  dockable_panel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  QFont arial_12("Arial", 12);
  QFont arial_14("Arial", 14);
  QFont monosp_12("Calibri", 12);

  QWidget* w = new QWidget(dockable_panel);
  w->setFont(arial_12);
  w->setFixedSize(250, 350);
  auto* grid = new QGridLayout(w);
  w->setLayout(grid);


  cb_shapes_ = new QComboBox(w);
  cb_shapes_->addItem("Куб");
  cb_shapes_->addItem("Шар");
  cb_shapes_->addItem("Пирамида");
//  shapes_->setMinimumHeight(90);
//  shapes_->setFont(arial_12);
  grid->addWidget(cb_shapes_,          0, 0,   1, 1);  // (obj, row, colmn,    rowSpan, colmnSpan)



  le_shape_width_ = new QLineEdit(w);
//  shape_width_->setFont(arial_12);
  le_shape_width_->setMinimumHeight(30);
  grid->addWidget(le_shape_width_,    1, 0,   1, 1);
  pb_apply_width_ = new QPushButton("Применить", w);
  pb_apply_width_->setMinimumSize(100, 30);
  grid->addWidget(pb_apply_width_,    1, 1,   1, 1);
  sb_shape_width2_ = new QSpinBox(w);
  grid->addWidget(sb_shape_width2_,   2, 0,   1, 1);
  dockable_panel->setWidget(w);


//  customerList = new QListWidget(dock);
//  customerList->addItems({"John Doe, Ambleton", "Jane Doe, Memorabilia"});
//  dock->setWidget(customerList);
  addDockWidget(Qt::RightDockWidgetArea, dockable_panel);
  view_menu_->addAction(dockable_panel->toggleViewAction());


//  connect(customerList, &QListWidget::currentTextChanged,
//          this, &MainWindow::insertCustomer);
//  connect(paragraphsList, &QListWidget::currentTextChanged,
  //          this, &MainWindow::addParagraph);
}


QWidget* main_window::create_mdi_child(bool is_opengl_temp_fl) {
  QWidget* child = nullptr;
  if (is_opengl_temp_fl) {
    child = new shape_widget();
    connect(cb_shapes_, &QComboBox::currentIndexChanged,
            static_cast<shape_widget*>(child), &shape_widget::change_shape);
  } else {
    child = new mdi_child_temp();
  }



  child->setAttribute(Qt::WA_DeleteOnClose);
  child->setMinimumSize(300, 400);
  mdi_area_->addSubWindow(child);
  return child;
}


//bool close_event_filter::eventFilter(QObject *obj, QEvent *event) {
//  if (event->type() == QEvent::Close || event->type() == QEvent::Quit) {
//    QKeyEvent *close_event = static_cast<QKeyEvent *>(event);
//    qDebug("Ignore event %d", close_event->type());
//    return true;
//  } else {
//    // standard event processing
//    qDebug() << event->type();
//    return QObject::eventFilter(obj, event);
//  }
//}


mdi_child_temp::mdi_child_temp() { // temp
//  setAttribute(Qt::WA_DeleteOnClose);

////  auto* close_ev_filter = new close_event_filter();
////  installEventFilter(close_ev_filter);
//  setMinimumSize(300, 400);
}

