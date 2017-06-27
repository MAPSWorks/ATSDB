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
 * DBInterface.h
 *
 *  Created on: Feb 1, 2012
 *      Author: sk
 */

#ifndef DBINTERFACE_H_
#define DBINTERFACE_H_

#include <boost/thread/mutex.hpp>
#include <set>
#include <memory>
#include <qobject.h>

#include "configurable.h"
#include "propertylist.h"
#include "dbovariableset.h"
#include "sqlgenerator.h"

class ATSDB;
class Buffer;
class BufferWriter;
class DBConnection;
class DBOVariable;
class QProgressDialog;
class DBObject;
class DBResult;
class DBTableColumn;
class DBTableInfo;
class DBInterfaceWidget;
class DBInterfaceInfoWidget;

class SQLGenerator;
class QWidget;

/**
 * @brief Encapsulates all dedicated database functionality
 *
 * After instantiation, initConnection has to be called to create a database connection. After this step, a number of functions
 * provide read/write/other methods. Simply delete to close database connection.
 *
 * \todo Context reference point gets lost
 */
class DBInterface : public QObject, public Configurable
{
    Q_OBJECT
signals:
    void databaseOpenedSignal ();

public slots:
    //void updateDBObjectInformationSlot ();

public:
    /// @brief Constructor
    DBInterface(std::string class_id, std::string instance_id, ATSDB *atsdb);
    /// @brief Destructor
    virtual ~DBInterface();

    const std::map<std::string, DBConnection*> &connections () { return connections_; }

    /// @brief Initializes a database connection based on the supplied type
    void useConnection (const std::string &connection_type);
    void databaseOpened ();
    void closeConnection ();

    void updateTableInfo ();

    virtual void generateSubConfigurable (const std::string &class_id, const std::string &instance_id);

    std::vector <std::string> getDatabases ();

    DBInterfaceWidget *widget();
    DBInterfaceInfoWidget *infoWidget();

    QWidget *connectionWidget ();

    const std::map <std::string, DBTableInfo> &tableInfo () { return table_info_; }

    bool ready ();

    DBConnection &connection ();

    /// @brief Returns a buffer with all data sources for a DBO type
//    Buffer *getDataSourceDescription (const std::string &dbo_type);
//    bool hasActiveDataSourcesInfo (const std::string &dbo_type);
//    /// @brief Returns a set with all active data source ids for a DBO type
//    std::set<int> getActiveSensorNumbers (const std::string &dbo_type);

//    /// @brief Writes a buffer to the database, into a table defined by write_table_names_ and DBO type
//    void writeBuffer (Buffer *data);
//    void writeBuffer (Buffer *data, std::string table_name);
//    void updateBuffer (Buffer *data);

//    /// @brief Prepares incremental read of DBO type
    void prepareRead (const DBObject &dbobject, DBOVariableSet read_list, std::string custom_filter_clause="", DBOVariable *order=0);
    /// @brief Returns data chunk of DBO type
    std::shared_ptr <Buffer> readDataChunk (const DBObject &dbobject, bool activate_key_search);
    /// @brief Cleans up incremental read of DBO type
    void finalizeReadStatement (const DBObject &dbobject);
    /// @brief Sets reading_done_ flags
    //void clearResult ();

    /// @brief Returns number of rows for a database table
    size_t count (const std::string &table);
//    DBResult *count (const std::string &dbo_type, unsigned int sensor_number);

//    /// @brief Creates the properties table
//    void createPropertiesTable ();
//    /// @brief Inserts a property
//    void insertProperty (std::string id, std::string value);
//    /// @brief Returns a property
//    std::string getProperty (std::string id);
//    bool hasProperty (std::string id);

//    /// @brief Returns the minimum/maximum table
//    void createMinMaxTable ();
//    /// @brief Returns buffer with the minimum/maximum of a DBO variable
//    Buffer *getMinMaxString (DBOVariable *var);
//    /// (dbo type, id) -> (min, max)
//    std::map <std::pair<std::string, std::string>, std::pair<std::string, std::string> > getMinMaxInfo ();
//    /// @brief Inserts a minimum/maximum value pair
//    void insertMinMax (std::string id, const std::string &dbo_type, std::string min, std::string max);

//    /// @brief Returns if database was post processed
//    bool isPostProcessed ();
//    /// @brief Post-processes the database
//    //void postProcess ();

//    /// @brief Returns variable values for a number of DBO type elements
//    Buffer *getInfo (const std::string &dbo_type, std::vector<unsigned int> ids, DBOVariableSet read_list, bool use_filters,
//            std::string order_by_variable, bool ascending, unsigned int limit_min=0, unsigned int limit_max=0,
//            bool finalize=0);

//    /// @brief Sets the context reference point as property
//    void setContextReferencePoint (bool defined, float latitude, float longitude);
//    /// @brief Returns if context reference point is defined
//    bool getContextReferencePointDefined ();
//    /// @brief Returns the context reference point
//    std::pair<float, float> getContextReferencePoint ();

//    /// @brief Returns if minimum/maximum table exists
//    bool existsMinMaxTable ();
//    /// @brief Returns if properties table exists
//    bool existsPropertiesTable ();

//    /// @brief Deletes table content for given table name
//    void clearTableContent (std::string table_name);

//    /// @brief Returns minimum/maximum information for all columns in a table
//    DBResult *queryMinMaxNormalForTable (std::string table);
//    /// @brief Returns minimum/maximum information for a given column in a table
//    DBResult *queryMinMaxForColumn (DBTableColumn *column, std::string table);

//    DBResult *getDistinctStatistics (const std::string &dbo_type, DBOVariable *variable, unsigned int sensor_number);

//    /// @brief Executes query and returns numbers for all active sensors
//    std::set<int> queryActiveSensorNumbers (const std::string &dbo_type);

//    void deleteAllRowsWithVariableValue (DBOVariable *variable, std::string value, std::string filter);
//    void updateAllRowsWithVariableValue (DBOVariable *variable, std::string value, std::string new_value, std::string filter);

//    void getMinMaxOfVariable (DBOVariable *variable, std::string filter_condition, std::string &min, std::string &max);
////    void getDistinctValues (DBOVariable *variable, std::string filter_condition, std::vector<std::string> &values);

//    Buffer *getTrackMatches (bool has_mode_a, unsigned int mode_a, bool has_ta, unsigned int ta, bool has_ti, std::string ti,
//            bool has_tod, double tod_min, double tod_max);

protected:
    std::map <std::string, DBConnection*> connections_;

    /// Connection to database, created based on DBConnectionInfo
    DBConnection *current_connection_;

    /// Interface initialized (after opening database)
    bool initialized_;

    /// Protects the database
    boost::mutex connection_mutex_;

    /// Container with all table names, based on DBO type
    // TODO solve this
    //std::map <std::string, std::string> write_table_names_;
    /// Size of a read chunk in incremental reading process
    unsigned int read_chunk_size_;

    /// Generates SQL statements
    SQLGenerator sql_generator_;

    /// Writes buffer to the database
    //BufferWriter *buffer_writer_;

    DBInterfaceWidget *widget_;
    DBInterfaceInfoWidget *info_widget_;

    std::map <std::string, DBTableInfo> table_info_;

    virtual void checkSubConfigurables ();

//    /// @brief Returns buffer with min/max data from another Buffer with the string contents. Delete returned buffer yourself.
//    Buffer *createFromMinMaxStringBuffer (Buffer *string_buffer, PropertyDataType data_type);
};

#endif /* SQLITE3CONNECTION_H_ */
