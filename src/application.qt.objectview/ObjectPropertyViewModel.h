#pragma once


#include <core.h>
#include <QAbstractItemModel>
#include <core.logging/Log.h>
#include <sstream>
namespace nspace{
  class TreeItem;
  class ObjectPropertyViewModel : 
    public QAbstractItemModel, 
    public virtual PropertyChangingObject, 
    public virtual Log, 
    public virtual PropertyChangedListener
  {
      Q_OBJECT;
      REFLECTABLE_OBJECT(ObjectPropertyViewModel);
      SUBCLASSOF(Log);
  private:

    TreeItem* getItem(const QModelIndex& index )const;
  public:
    TreeItem * createItem(Object * object);
    PROPERTY(Object *, CurrentObject);
    PROPERTY(TreeItem*, RootItem);
  protected:
    void onPropertyChanged(Object * sender, const std::string & name);
  public:
    void onPropertyChanged(const std::string  & name);

    ObjectPropertyViewModel();

    QModelIndex parent( const QModelIndex& index ) const ;
    bool hasChildren(const QModelIndex& parent)const;
    const PropertyInfo*  getProperty(const QModelIndex & index)const;

    bool setData(const QModelIndex & index, const QVariant & value, int role=Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex & index)const;
    QModelIndex index(int row, int column, const QModelIndex & parent=QModelIndex())const;

    int rowCount(const QModelIndex &parent=QModelIndex())const;
    int columnCount(const QModelIndex &parent=QModelIndex())const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const;

    void itemChanged(TreeItem * treeItem);

  };
}
