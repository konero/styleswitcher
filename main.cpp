#include "theme.h"
#include <QApplication>
#include <QColor>
#include <QFile>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QSettings>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QMainWindow mainWindow;
  mainWindow.setWindowTitle("QSS Controller");

  // Create a ColorPickerWidget
  ColorPickerWidget *colorPicker = new ColorPickerWidget();

  // Create the text editor
  QTextEdit *customQssTextEdit = new QTextEdit();

  // Create the Apply button
  QPushButton *applyButton = new QPushButton("Apply");

  // Create QSettings
  QSettings settings("config.ini", QSettings::IniFormat);
  QColor savedColor = settings.value("sliderColor", QColor()).value<QColor>();
  colorPicker->setColor(savedColor);

  // Slot to apply stylesheet changes
  QObject::connect(applyButton, &QPushButton::clicked, [&]() {
    // Load the stylesheet from a .qss file
    QFile styleFile(":/styles/style.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QString styleSheet = QString::fromUtf8(styleFile.readAll());
      styleFile.close();

      // Replace placeholder var with slider value
      QColor color = colorPicker->getColor();
      QString colorValue = QString("rgb(%1, %2, %3)")
                               .arg(color.red())
                               .arg(color.green())
                               .arg(color.blue());
      styleSheet.replace("--var", colorValue);

      // Check if text edit box is not empty
      if (!customQssTextEdit->toPlainText().isEmpty()) {
        // Concatenate custom QSS style
        styleSheet += customQssTextEdit->toPlainText();
      }

      // Apply modified stylesheet
      app.setStyleSheet(styleSheet);

      // Save the color to QSettings
      settings.setValue("sliderColor", color);
    }
  });

  // Create the central widget and layout
  QWidget *centralWidget = new QWidget(&mainWindow);
  QVBoxLayout *layout = new QVBoxLayout(centralWidget);

  layout->addWidget(colorPicker);
  layout->addWidget(customQssTextEdit);
  layout->addWidget(applyButton);

  mainWindow.setCentralWidget(centralWidget);
  mainWindow.show();

  return app.exec();
}
