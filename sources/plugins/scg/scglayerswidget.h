#ifndef SCGLAYERSWIDGET_H
#define SCGLAYERSWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QToolBar>

class SCgScene;

class SCgLayersWidget: public QWidget
{
    Q_OBJECT
public:
    SCgLayersWidget(SCgScene *scene, QWidget *parent = 0);

    virtual ~SCgLayersWidget();
public slots:
    /*! Adds layer to layer's list
      * @param id Layer's id
      * @param name Layer's name
      */

    void addLayer(int id, QString const& name);

    /*! Removes layer from layer's list
      * @param id Layer's id
      */
    void removeLayer(int id);

    /*! Selects layer in layer's list
      * @param id Layer's id
      */
    void selectLayer(int id);

private slots:
    //! Create layer
    void createLayer();

    //! Delete layer
    void deleteLayer();

    //! Hide all layers
    void hideAll();

    //! Show all layers
    void showAll();

    //! Hide selected layers
    void hideSelected();

    //! Show selected layers
    void showSelected();

    //! Select objects on scene for selected layers
    void selectObjects();

    /*! Select objects for selected layer
      * @param item selected layer
      */
    void selectLayer(QListWidgetItem* item);

    //! Show context menu
    void customContextMenu(QPoint point);

private:
    //! list of layers
    QListWidget *mLayerListView;

    //! toolbar
    QToolBar *mToolBar;

    //! scene
    SCgScene* mScene;

    //! layers dictionary
    QMap<int, QString> mLayerDict;
};

#endif // SCGLAYERSWIDGET_H
