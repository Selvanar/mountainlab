/******************************************************
** See the accompanying README and LICENSE files
** Author(s): Jeremy Magland
** Created: 5/27/2016
*******************************************************/

#ifndef MVTIMESERIESVIEW2_H
#define MVTIMESERIESVIEW2_H

#include <QWidget>
#include <diskreadmda.h>
#include "mvtimeseriesviewbase.h"

class MVTimeSeriesView2Private;
class MVTimeSeriesView2 : public MVTimeSeriesViewBase {
    Q_OBJECT
public:
    friend class MVTimeSeriesView2Private;
    MVTimeSeriesView2(MVViewAgent* view_agent);
    virtual ~MVTimeSeriesView2();

    void prepareCalculation() Q_DECL_OVERRIDE;
    void runCalculation() Q_DECL_OVERRIDE;
    void onCalculationFinished() Q_DECL_OVERRIDE;

    void paintContent(QPainter* painter);

    void setAmplitudeFactor(double factor); // display range will be between -1/factor and 1/factor, but not clipped (thus channel plots may overlap)
    void autoSetAmplitudeFactor();
    void autoSetAmplitudeFactorWithinTimeRange();

    double amplitudeFactor() const;

    void resizeEvent(QResizeEvent* evt);
    void keyPressEvent(QKeyEvent* evt);

private slots:
    void slot_vertical_zoom_in();
    void slot_vertical_zoom_out();

private:
    MVTimeSeriesView2Private* d;
};

#endif // MVTIMESERIESVIEW2_H