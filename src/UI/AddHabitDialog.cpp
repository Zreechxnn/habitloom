#include "AddHabitDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>

AddHabitDialog::AddHabitDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Tambah Kebiasaan Baru");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QFormLayout *formLayout = new QFormLayout();
    nameEdit = new QLineEdit();
    descEdit = new QLineEdit();

    formLayout->addRow("Nama Kebiasaan:", nameEdit);
    formLayout->addRow("Deskripsi:", descEdit);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);
}