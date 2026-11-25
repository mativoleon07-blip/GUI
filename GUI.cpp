#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Main window
    QWidget window;
    window.setWindowTitle("Hardware Cost Calculator");

    // Arrays for items and prices
    QString items[] = {"Hammer", "Screwdriver", "Pliers", "Drill"};
    double prices[] = {500.0, 300.0, 450.0, 3500.0};

    // GUI components
    QLabel *label = new QLabel("Select Hardware Item:");
    QComboBox *itemBox = new QComboBox();
    for (const QString &item : items) {
        itemBox->addItem(item);
    }

    QLabel *qtyLabel = new QLabel("Enter Quantity:");
    QLineEdit *qtyInput = new QLineEdit();

    QPushButton *calcButton = new QPushButton("Compute Cost");

    // Layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(itemBox);
    layout->addWidget(qtyLabel);
    layout->addWidget(qtyInput);
    layout->addWidget(calcButton);
    window.setLayout(layout);

    // Compute cost when button is clicked
    QObject::connect(calcButton, &QPushButton::clicked, [&]() {
        int index = itemBox->currentIndex();
        double price = prices[index];

        bool ok;
        int quantity = qtyInput->text().toInt(&ok);

        if (!ok || quantity <= 0) {
            QMessageBox::warning(&window, "Error", "Enter a valid quantity.");
            return;
        }

        double totalCost = price * quantity;

        QMessageBox::information(
            &window,
            "Total Cost",
            QStringLiteral("Item: %1\nUnit Price: %2\nQuantity: %3\nTotal Cost: %4")
                .arg(items[index])
                .arg(price)
                .arg(quantity)
                .arg(totalCost)
        );
    });

    window.show();
    return app.exec();
}