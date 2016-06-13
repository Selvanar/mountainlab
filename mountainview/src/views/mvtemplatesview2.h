/******************************************************
** See the accompanying README and LICENSE files
** Author(s): Jeremy Magland
** Created: 7/29/2016
*******************************************************/

#ifndef MVTEMPLATESVIEW2_H
#define MVTEMPLATESVIEW2_H

#include "mvabstractview.h"

#include <mvabstractviewfactory.h>
#include <paintlayer.h>

class MVTemplatesView2Private;
class MVTemplatesView2 : public MVAbstractView {
    Q_OBJECT
public:
    friend class MVTemplatesView2Private;
    MVTemplatesView2(MVContext* mvcontext);
    virtual ~MVTemplatesView2();

    void prepareCalculation() Q_DECL_OVERRIDE;
    void runCalculation() Q_DECL_OVERRIDE;
    void onCalculationFinished() Q_DECL_OVERRIDE;

    void zoomAllTheWayOut();

private slots:
    void slot_update_panels();
    void slot_update_highlighting();
    void slot_panel_clicked(int index, Qt::KeyboardModifiers modifiers);
    void slot_vertical_zoom_in();
    void slot_vertical_zoom_out();
    void slot_horizontal_zoom_in();
    void slot_horizontal_zoom_out();

private:
    MVTemplatesView2Private* d;
};

class MVTemplatesView2Factory : public MVAbstractViewFactory {
    Q_OBJECT
public:
    MVTemplatesView2Factory(MVContext* context, QObject* parent = 0);
    QString id() const Q_DECL_OVERRIDE;
    QString name() const Q_DECL_OVERRIDE;
    QString title() const Q_DECL_OVERRIDE;
    MVAbstractView* createView(QWidget* parent) Q_DECL_OVERRIDE;
private slots:
    //void openClipsForTemplate();
};

#endif // MVTEMPLATESVIEW2_H