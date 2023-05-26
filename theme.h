#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QColor>

class ColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    ColorPickerWidget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        // Create sliders
        redSlider = createSlider();
        greenSlider = createSlider();
        blueSlider = createSlider();

        // Set layout
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->addWidget(redSlider);
        layout->addWidget(greenSlider);
        layout->addWidget(blueSlider);

        // Connect slider signals
        connect(redSlider, &QSlider::valueChanged, this, &ColorPickerWidget::onColorSliderChanged);
        connect(greenSlider, &QSlider::valueChanged, this, &ColorPickerWidget::onColorSliderChanged);
        connect(blueSlider, &QSlider::valueChanged, this, &ColorPickerWidget::onColorSliderChanged);
    }

    QColor getColor() const
    {
        int redValue = redSlider->value();
        int greenValue = greenSlider->value();
        int blueValue = blueSlider->value();

        return QColor(redValue, greenValue, blueValue);
    }

signals:
    void colorChanged(const QColor& color);

private slots:
    void onColorSliderChanged()
    {
        QColor color = getColor();
        emit colorChanged(color);
    }

private:
    QSlider* createSlider()
    {
        QSlider* slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(0);
        slider->setMaximum(255);
        return slider;
    }

    QSlider* redSlider;
    QSlider* greenSlider;
    QSlider* blueSlider;
};
