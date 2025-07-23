#ifndef ADDHABITDIALOG_H
#define ADDHABITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>

class AddHabitDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddHabitDialog(QWidget *parent = nullptr);

    QString getName() const { return nameEdit->text(); }
    QString getDescription() const { return descEdit->text(); }

private:
    QLineEdit *nameEdit;
    QLineEdit *descEdit;
    QDialogButtonBox *buttonBox;
};

#endif // ADDHABITDIALOG_H