#pragma once

#include <QListWidget>
#include "scgscene.h"
#include "scglayer.h"

class SCgLayerWidget : public QListWidget
{
    Q_OBJECT
public:
    SCgLayerWidget(SCgScene* scene);
    ~SCgLayerWidget();

    QString getSelectedLayerName();

public slots:

    void createLayer();
    void deleteLayer();

private slots:
    void customContextMenu(QPoint point);
    void setVisibleSelected();

private:
    void createStandartLayers();

    SCgScene* scene;
};
