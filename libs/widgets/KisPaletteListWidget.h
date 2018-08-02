#ifndef KISPALETTECHOOSER_H
#define KISPALETTECHOOSER_H

#include <QString>
#include <QWidget>
#include <ui_WdgPaletteListWidget.h>

#include "kritawidgets_export.h"

class KoResource;
class KoColorSet;

class KisPaletteListWidgetPrivate;

class KRITAWIDGETS_EXPORT KisPaletteListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KisPaletteListWidget(QWidget *parent = nullptr);
    virtual ~KisPaletteListWidget();

Q_SIGNALS:
    void sigPaletteSelected(KoColorSet*);
    void sigPaletteModified(KoColorSet*);
    void sigPaletteListChanged();

public Q_SLOTS:

private /* methods */:
    void setPaletteGlobal(KoColorSet *colorSet);
    void setPaletteNonGlobal(KoColorSet *colorSet);
    QString newPaletteFileName();

private Q_SLOTS:
    void slotPaletteResourceSelected(KoResource *);
    void slotAdd();
    void slotRemove();
    void slotModify();
    void slotImport();
    void slotExport();

private:
    QScopedPointer<Ui_WdgPaletteListWidget> m_ui;
    QScopedPointer<KisPaletteListWidgetPrivate> m_d;
};

#endif // KISPALETTECHOOSER_H
