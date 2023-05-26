#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QVBoxLayout>
#include "theme.h"

/**
 * Color Variables
 * 
 * primary (main background)
 * secondary (darker, eg. titlebars)
 * tertiary (borders)
 * 
 * highlight (main)
 * highlight-content (eg. text, icon)
*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("QSS Controller");

    // Create a ColorPickerWidget
    ColorPickerWidget* colorPicker = new ColorPickerWidget();

    QObject::connect(colorPicker, &ColorPickerWidget::colorChanged, [&](const QColor& color){
        // Load the stylesheet from a .qss file
        QFile styleFile(":/styles/style.qss");
        if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString styleSheet = QString::fromUtf8(styleFile.readAll());
            styleFile.close();

            /**
             * Eg. we can conditionally check the brightness value of color when it
             * is a dependency to make sure contents that go inside are visible. If
             * color is bright we'll move the inner color dark, and vice versa.
            */

            // Replace placeholder var with slider value
            QString colorValue = QString("rgb(%1, %2, %3)")
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue());
            styleSheet.replace("@@var@@", colorValue);

            // Apply modified stylesheet
            app.setStyleSheet(styleSheet);
        }
    });

    // Create the central widget and layout
    QWidget *centralWidget = new QWidget(&mainWindow);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Add the colorPicker to the layout
    layout->addWidget(colorPicker);

    // Set the central widget of the main window
    mainWindow.setCentralWidget(centralWidget);

    // Show the main window
    mainWindow.show();

    // Enter the event loop
    return app.exec();
}
