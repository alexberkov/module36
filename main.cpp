#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>


class CircleImage: public QWidget {
public:
    CircleImage() = default;
    explicit CircleImage(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    [[nodiscard]] QSize minimumSizeHint() const override;
public:
    void makeGreen();
    void makeYellow();
    void makeRed();
private:
    QPixmap greenCirclePixmap;
    QPixmap yellowCirclePixmap;
    QPixmap redCirclePixmap;
    QPixmap currentCirclePixmap;
};

CircleImage::CircleImage(QWidget *parent) {
  setParent(parent);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  greenCirclePixmap = QPixmap("../green-circle.png");
  yellowCirclePixmap = QPixmap("../yellow-circle.png");
  redCirclePixmap = QPixmap("../red-circle.png");
  currentCirclePixmap = greenCirclePixmap;
  setGeometry(currentCirclePixmap.rect());
}

void CircleImage::paintEvent(QPaintEvent *e) {
  QPainter p(this);
  p.drawPixmap(e->rect(), currentCirclePixmap);
}

void CircleImage::makeGreen() {
  currentCirclePixmap = greenCirclePixmap;
  update();
}

void CircleImage::makeYellow() {
  currentCirclePixmap = yellowCirclePixmap;
  update();
}

void CircleImage::makeRed() {
  currentCirclePixmap = redCirclePixmap;
  update();
}

QSize CircleImage::minimumSizeHint() const {
  return {100, 100};
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  auto *window = new QWidget;
  window->setFixedSize(200, 250);
  auto *circle = new CircleImage(window);
  auto *slider  = new QSlider(Qt::Horizontal, window);
  auto *layout = new QVBoxLayout(window);
  layout->addWidget(circle);
  layout->addWidget(slider);
  QObject::connect(slider, &QSlider::valueChanged, circle, [&slider, &circle](int value) {
    value = slider->value();
    if (value <= 33) circle->makeGreen();
    else if (value <= 66) circle->makeYellow();
    else circle->makeRed();
  });
  window->show();
  return QApplication::exec();
}
