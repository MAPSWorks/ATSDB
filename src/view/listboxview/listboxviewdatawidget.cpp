/*
 * ListBoxViewDataWidget.cpp
 *
 *  Created on: Nov 11, 2012
 *      Author: sk
 */

#include <QTabWidget>
#include <QHBoxLayout>

#include "buffertablewidget.h"
#include "dbobject.h"
#include "dbobjectmanager.h"
#include "listboxviewdatawidget.h"
#include "listboxviewdatasource.h"
#include "buffer.h"
#include "logger.h"
#include "atsdb.h"

ListBoxViewDataWidget::ListBoxViewDataWidget(ListBoxViewDataSource *data_source, QWidget * parent, Qt::WindowFlags f)
    : QWidget (parent, f), data_source_ (data_source)
{
    assert (data_source_);

    QHBoxLayout *layout = new QHBoxLayout ();

    tab_widget_ = new QTabWidget();
    layout->addWidget (tab_widget_);

    for (auto object : ATSDB::instance().objectManager().objects())
    {
        if (object.second->hasData())
        {
            BufferTableWidget *buffer_table = new BufferTableWidget ();
            tab_widget_->addTab (buffer_table , object.first.c_str());
            buffer_tables_[object.first] = buffer_table;
        }
    }

    setLayout (layout);
}

ListBoxViewDataWidget::~ListBoxViewDataWidget()
{
    // TODO
    //buffer_tables_.clear();
}

void ListBoxViewDataWidget::clearTables ()
{
    logdbg  << "ListBoxViewDataWidget: updateTables: start";
    // TODO
    //  std::map <DB_OBJECT_TYPE, BufferTableWidget*>::iterator it;

    //  for (it = buffer_tables_.begin(); it != buffer_tables_.end(); it++)
    //  {
    //    it->second->show (0, 0, false);
    //  }

    logdbg  << "ListBoxViewDataWidget: updateTables: end";
}

void ListBoxViewDataWidget::updateData (DBObject &object, std::shared_ptr<Buffer> buffer)
{
    logdbg  << "ListBoxViewDataWidget: updateTables: start";
    assert (buffer_tables_.count (object.name()) > 0);
    buffer_tables_.at(object.name())->show(object, buffer); //, data_source_->getSet()->getFor(type), data_source_->getDatabaseView()

    logdbg  << "ListBoxViewDataWidget: updateTables: end";
}
