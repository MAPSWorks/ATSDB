/*
 * This file is part of ATSDB.
 *
 * ATSDB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ATSDB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with ATSDB.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * DBObjectEditWidget.h
 *
 *  Created on: Aug 27, 2012
 *      Author: sk
 */

#ifndef DBOBJECTEDITWIDGET_H_
#define DBOBJECTEDITWIDGET_H_

#include <QWidget>
#include <map>

class DBObject;
class DBOVariable;
class QLineEdit;
class QComboBox;
class QCheckBox;
class QGridLayout;
class QPushButton;
class DBTableColumnComboBox;
class DBOTypeComboBox;
class DBOVariableDataTypeComboBox;
class StringRepresentationComboBox;

/**
 * @brief Edit widget for a DBObject
 */
class DBObjectEditWidget : public QWidget
{
    Q_OBJECT

signals:
    /// @brief Emitted if DBObject was changed
    void changedDBO();

public slots:
    /// @brief Adds a DBOVariable
    void addVariable();
    /// @brief Adds all DBOVariables
    void addAllVariables ();
    /// @brief Adds all new DBOVariables
    void addNewVariables ();
    /// @brief Adds a MetaDBTable
    void addMetaTable();
    /// @brief Changes loadable flag
    void changedLoadable ();

    /// @brief Updates data source schema selection
    void updateDSSchemaSelection();
    /// @brief Updates data source local key selection
    void updateDSLocalKeySelection();
    /// @brief Updates data source meta table name selection
    void updateDSMetaTableNameSelection ();
    /// @brief Updates data source foreign key selection
    void updateDSForeignKeySelection ();
    /// @brief Updates data source name column selection
    void updateDSNameColumnSelection ();
    /// @brief Updates data sources grid
    void updateDataSourcesGrid ();
    /// @brief Adds a data source
    void addDataSource ();
    /// @brief Changes data source schema
    void changedDSSchema();
    /// @brief Updates data sources meta table dependents
    void changedDSMetaTable();

    /// @brief Changes DBO type
    void changedType ();
    /// @brief Changes DBO name
    void editName ();
    /// @brief Changes DBO info
    void editInfo ();

    /// @brief Deletes a DBOVariable
    void deleteDBOVar();
    /// @brief Edits a DBOVariable name
    void editDBOVarName();
    /// @brief Edits a DBOVariable info
    void editDBOVarInfo();

    /// @brief Updates the DBOVariables grid
    void updateDBOVarsGrid ();
    /// @brief Updates the schema selection for meta table
    void updateMetaSchemaSelection ();
    /// @brief Updates the meta table selection
    void updateMetaTableSelection ();
    /// @brief Updates the schema selection for adding all variables
    void updateAllVarsSchemaSelection ();
    /// @brief Updates meta tables grid
    void updateMetaTablesGrid();

public:
    /// @brief Constructor
    DBObjectEditWidget(DBObject *object, QWidget * parent = 0, Qt::WindowFlags f = 0);
    /// @brief Destructor
    virtual ~DBObjectEditWidget();

private:
    /// @brief DBObject to be managed
    DBObject *object_;

    /// @brief DBO name
    QLineEdit *name_edit_;
    /// @brief DBO info
    QLineEdit *info_edit_;
    /// @brief DBO type
    DBOTypeComboBox *type_box_;
    /// @brief DBO loadable
    QCheckBox *loadable_check_;

    /// @brief Grid with all data sources
    QGridLayout *ds_grid_;

    /// @brief Add new data source schema selection
    QComboBox *ds_schema_box_;
    /// @brief Add new data source local key selection
    QComboBox *ds_local_key_box_;
    /// @brief Add new data source meta table selection
    QComboBox *ds_meta_name_box_;
    /// @brief Add new data source foreign key selection
    QComboBox *ds_foreign_key_box_;
    /// @brief Add new data source foreign name selection
    QComboBox *ds_foreign_name_box_;

    /// @brief grid with all meta tables per schema
    QGridLayout *meta_table_grid_;

    /// @brief Add meta table for schema schema selection
    QComboBox *new_meta_schema_box_;
    /// @brief Add meta table for schema meta table selection
    QComboBox *new_meta_box_;

    /// @brief Grid with all DBOVariables
    QGridLayout *dbovars_grid_;

    /// @brief Container with DBOVariable delete buttons
    std::map <QPushButton *, DBOVariable *> dbo_vars_grid_delete_buttons_;
    /// @brief Container with DBOVariable name edit fields
    std::map <QLineEdit *, DBOVariable *> dbo_vars_grid_name_edits_;
    /// @brief Container with DBOVariable info edit fields
    std::map <QLineEdit *, DBOVariable *> dbo_vars_grid_info_edits_;
    /// @brief Container with DBOVariable property data type selection fields
    std::map <DBOVariableDataTypeComboBox *, DBOVariable *> dbo_vars_grid_data_type_boxes_;
    /// @brief Container with DBOVariable string representation selection fields
    std::map <StringRepresentationComboBox *, DBOVariable *> dbo_vars_grid_representation_boxes_;

    /// @brief New DBOVariable name edit field
    QLineEdit *new_var_name_edit_;

    /// @brief Add all variables schema box
    QComboBox *all_schemas_box_;
    /// @brief Add all variables button
    QPushButton *add_all_button_;

    /// @brief Creates GUI elements
    void createElements ();

    /// @brief Updates a schema selection box
    void updateSchemaSelectionBox (QComboBox *box);
    /// @brief Updates a variable selection box
    void updateVariableSelectionBox (QComboBox *box, std::string schema_name, std::string meta_table_name);
};

#endif /* DBOBJECTEDITWIDGET_H_ */