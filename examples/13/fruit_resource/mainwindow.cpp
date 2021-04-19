#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <vector>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    draw_fruit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_fruit()
{
    // Vector of fruits
    const std::vector<std::string>
            fruits = {"cherries", "strawberry", "orange", "pear", "apple",
                      "bananas", "tomato", "grapes", "eggplant"};

    // Defining where the images can be found and what kind of images they are
    const std::string PREFIX(":/");
    const std::string SUFFIX(".png");

    // Converting image (png) to a pixmap
    int i = 0; // try different values in 0 <= i < fruits.size()
    std::string filename = PREFIX + fruits.at(i) + SUFFIX;
    QPixmap image(QString::fromStdString(filename));

    // Scaling the pixmap
    image = image.scaled(FRUIT_SIZE, FRUIT_SIZE);

    // Setting the pixmap for a new label
    QLabel* label = new QLabel("test", this);
    label->setGeometry(MARGIN, MARGIN, FRUIT_SIZE, FRUIT_SIZE);
    label->setPixmap(image);

    // Setting the icon for a new push button
    QPushButton* button = new QPushButton(this);
    button->setGeometry(MARGIN + FRUIT_SIZE + MARGIN, MARGIN,
                        FRUIT_SIZE, FRUIT_SIZE);
    button->setIcon(image);
}

